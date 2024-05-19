# Real-time Gesture Recognition Using ESP32 and TensorFlow Lite
# This Python program sets up a serial connection to read data from an ESP32 device,
# processes the sensor data to extract features, and uses a TensorFlow Lite model to predict gestures.
# The predicted gestures are displayed on a GUI built with Tkinter.

import serial
import numpy as np
import tensorflow as tf
import pywt
from scipy.signal import iirnotch, butter, sosfiltfilt, tf2sos
import threading
from threading import Event
import time
from collections import deque
import statistics
import tkinter as tk

# Set up the serial connection and TensorFlow Lite interpreter
ser = serial.Serial('COM5', 1000000)  # Adjust COM port as needed
interpreter = tf.lite.Interpreter(model_path='../machine_learning_code/XXXX.tflite')
interpreter.allocate_tensors()
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Initialize the data buffer
data_buffer = np.empty((0, 3), dtype=float)
lock = threading.Lock()

# Event to signal that the GUI is ready
gui_ready = Event()

# Prediction smoothing
prediction_buffer = deque(maxlen=10)  # Adjust size based on desired responsiveness

# Constants for processing
fs = 1938
f0 = 50.0
quality_factor = 50.0
bandpass_lowcut = 20
bandpass_highcut = 350
bandpass_order = 4
window_size_samples = int(fs * 0.250)
overlap_samples = int(fs * 0.050)

# Create a Tkinter root object
root = tk.Tk()
root.geometry("1920x1080")  # Set the window size to X pixels

# Create labels to display the gesture and percentage
title_label = tk.Label(root, text="Predicted gesture:", font=("Helvetica", 100))
title_label.pack(pady=50)  # Add some vertical padding

gesture_label = tk.Label(root, text="", font=("Helvetica", 140))
gesture_label.pack(pady=50)  # Add some vertical padding

percentage_label = tk.Label(root, text="", font=("Helvetica", 70), fg="red")
percentage_label.pack(pady=50)  # Add some vertical padding


def safe_update_display(class_name, percentage):
    def update_gui():
        if root:  # Check if root exists to prevent errors during shutdown
            gesture_label.config(text=f"{class_name}")
            percentage_label.config(text=f"Accuracy: {percentage:.1f}%")
    root.after(0, update_gui)


# Define class names corresponding to model output indices
class_names = [
    "Resting",
    "Thumb up",
    "Fist",
    "Pointing",
    "Tripod Grasp",
    "Pinch Grasp"
]


def calculate_prediction_percentage(prediction_buffer, target_index):
    count = prediction_buffer.count(target_index)
    percentage = (count / len(prediction_buffer)) * 100 if prediction_buffer else 0
    return percentage


# Filter setup
def setup_filters():
    b_notch, a_notch = iirnotch(f0, quality_factor, fs)
    sos_notch = tf2sos(b_notch, a_notch)
    low, high = bandpass_lowcut / (0.5 * fs), bandpass_highcut / (0.5 * fs)
    sos_bandpass = butter(bandpass_order, [low, high], btype='band', output='sos')
    return sos_notch, sos_bandpass


sos_notch, sos_bandpass = setup_filters()


# Function to apply filters
def apply_filters(data):
    data = sosfiltfilt(sos_notch, data, axis=0)
    data = sosfiltfilt(sos_bandpass, data, axis=0)
    return data


# Normalize the signal
def normalize_signal(signal):
    return (signal - np.mean(signal)) / np.std(signal)


# Apply Discrete Wavelet Transform
def apply_dwt(signal, wavelet='db10', level=4):
    coeffs = pywt.wavedec(signal, wavelet, level=level)
    return coeffs


# Calculate statistical features
def calculate_iemg(signal):
    return np.sum(np.abs(signal))


def calculate_time_domain_features(signal):
    return np.array([np.mean(np.abs(signal))])


def calculate_dwt_features(coeff):
    return np.array([np.sum(np.abs(coeff)), np.sqrt(np.mean(np.square(coeff))), np.mean(np.abs(coeff))])


# Process each sensor window
def process_window(signal):
    notched_signal = apply_filters(signal)
    iemg = calculate_iemg(notched_signal)
    normalized_signal = normalize_signal(notched_signal)
    normalized_features = calculate_time_domain_features(normalized_signal)
    dwt_coeffs = apply_dwt(normalized_signal)
    dwt_features = np.concatenate([calculate_dwt_features(coeff) for coeff in dwt_coeffs])
    return np.concatenate(([iemg], normalized_features, dwt_features))


# Thread for reading and buffering data
def read_data():
    global data_buffer
    try:
        while True:
            if (ser.in_waiting > 0):
                line = ser.readline().decode('ascii').strip()
                if line:
                    try:
                        data_parts = line.split(',')
                        if len(data_parts) == 3:
                            data = np.array([float(x) for x in data_parts])
                            with lock:
                                data_buffer = np.vstack([data_buffer, data])
                    except ValueError as e:
                        print(f"Data conversion error: {e}")
    except KeyboardInterrupt:
        print("Serial read stopped by user")


# Thread for processing data and making predictions
def process_data():
    global data_buffer
    try:
        while True:
            with lock:
                if len(data_buffer) >= window_size_samples:

                    window_data = data_buffer[:window_size_samples]
                    data_buffer = data_buffer[overlap_samples:]  # Handle overlap
                    # Mark the start time
                    start_time = time.time()
                    # Process each sensor channel and predict
                    features = np.array([process_window(window_data[:, i]) for i in range(window_data.shape[1])])
                    features = features.T.reshape(1, 17, 3)  # Ensure the features are in the correct shape

                    # Mark the end time right before invoking the TensorFlow Lite model
                    end_time = time.time()
                    processing_duration = end_time - start_time
                    print(f"Time taken to process window: {processing_duration:.5f} s")

                    # Set the input tensor for the TensorFlow Lite model
                    interpreter.set_tensor(input_details[0]['index'], features.astype(np.float32))

                    # Run the model prediction
                    interpreter.invoke()

                    # Get the output data from the model
                    output_data = interpreter.get_tensor(output_details[0]['index'])
                    predicted_index = np.argmax(output_data)
                    # Update prediction buffer
                    prediction_buffer.append(predicted_index)

                    # Calculate the most frequent prediction in the buffer
                    if len(prediction_buffer) == prediction_buffer.maxlen:
                        gui_ready.wait()
                        most_common = statistics.mode(prediction_buffer)
                        stable_prediction = class_names[most_common]

                        # Dynamically calculate the percentage for the current stable prediction
                        stable_prediction_index = class_names.index(stable_prediction)
                        stable_prediction_percentage = calculate_prediction_percentage(prediction_buffer,
                                                                                       stable_prediction_index)
                        print(f"Stable Prediction: {stable_prediction}, Percentage: {stable_prediction_percentage}%")

                        safe_update_display(stable_prediction, stable_prediction_percentage)
                    else:
                        current_prediction = class_names[predicted_index]
                        print(f"Current Prediction: {current_prediction}")

            time.sleep(0.000001)
    except KeyboardInterrupt:
        print("Data processing stopped by user")


if __name__ == "__main__":
    root.after(100, lambda: gui_ready.set())  # Ensure GUI is up before setting the event
    thread_read = threading.Thread(target=read_data)
    thread_process = threading.Thread(target=process_data)
    thread_read.start()
    thread_process.start()
    root.mainloop()
