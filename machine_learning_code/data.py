# Data Preprocessing for Gesture Recognition Using Signal Processing and Feature Extraction
# This script preprocesses sensor data, applies filters, extracts features, and balances the dataset.
# It saves the processed data to a NPZ file for later use in model training.

import os
import pandas as pd
import numpy as np
import pywt
from scipy.signal import iirnotch, butter, sosfiltfilt, tf2sos

# Define global variables for the signal processing parameters
fs = 1938  # Sampling rate of the signal in Hz
f0 = 50.0  # Frequency to remove with notch filter, common for powerline noise
quality_factor = 50.0  # Quality factor for the notch filter; higher values mean a narrower filter
bandpass_lowcut = 20  # Lower bound of the bandpass filter in Hz
bandpass_highcut = 350  # Upper bound of the bandpass filter in Hz
bandpass_order = 4  # Order of the bandpass filter
window_size_ms = 300  # Duration of each window in milliseconds for feature extraction
window_size = int(fs * window_size_ms / 1000)  # Convert window duration from ms to number of samples
step_size_ms = 50  # Step size in milliseconds for sliding window approach
step_size = int(fs * step_size_ms / 1000)  # Convert step size from ms to number of samples
window_duration_seconds = 4  # Duration in seconds to capture after each gesture onset
total_samples = fs * window_duration_seconds  # Total number of samples to extract for each gesture window
num_windows = (total_samples - window_size) // step_size + 1  # Calculate number of sliding windows
delay_ms = 500  # Delay in milliseconds before starting processing after gesture onset
delay_samples = int(fs * delay_ms / 1000)  # Convert delay from ms to number of samples


# Apply a notch filter to remove 50Hz powerline noise using a second-order section (SOS) implementation
def notch_filter(data, cutoff, fs, quality_factor):
    b, a = iirnotch(cutoff, quality_factor, fs)
    sos = tf2sos(b, a)
    filtered_notch_data = sosfiltfilt(sos, data)
    return filtered_notch_data


# Apply a bandpass filter to allow signals between lowcut and highcut frequencies, removing other frequencies
def butter_bandpass_filter(data, lowcut, highcut, fs, order):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    sos = butter(order, [low, high], btype='band', output='sos')
    filtered_bandpass_data = sosfiltfilt(sos, data)
    return filtered_bandpass_data


# Normalize the signal to have zero mean and unit variance
def normalize_signal(signal):
    return (signal - np.mean(signal)) / np.std(signal)


# Apply Discrete Wavelet Transform to the signal and return the coefficients
def apply_dwt(signal, wavelet='db10', level=4):
    coeffs = pywt.wavedec(signal, wavelet, level=level)
    return coeffs


# Calculate different statistical features from different signal window
def calculate_iemg(signal):
    return np.sum(np.abs(signal))  # IEMG


def calculate_time_domain_features(signal):
    return np.array([
        np.mean(np.abs(signal))                # MAV
        # Uncomment the following lines to include more features
        # skew(signal),                         # Skewness
        # kurtosis(signal)                      # Kurtosis
    ])


def calculate_dwt_features(coeff):
    return np.array([
        # Uncomment the following lines to include more features
        # np.sum(np.square(coeff)),  # Energy
        # skew(coeff),               # Skewness
        # kurtosis(coeff),           # Kurtosis
        np.sum(np.abs(coeff)),              # IEMG
        np.sqrt(np.mean(np.square(coeff))), # RMS
        np.mean(np.abs(coeff))              # MAV
    ])


# Process and extract features for each window of sensor data
def process_windows(window_data):
    processed_features = []
    for sensor in ['Sensor1', 'Sensor2', 'Sensor3']:
        sensor_data = window_data[sensor].values
        processed_features.append(process_window(sensor_data))
    return np.stack(processed_features, axis=-1)


# Process a single window of sensor data
def process_window(signal):
    # Apply notch and bandpass filters
    notched_signal = notch_filter(signal, f0, fs, quality_factor)
    bandpass_signal = butter_bandpass_filter(notched_signal, bandpass_lowcut, bandpass_highcut, fs, bandpass_order)

    # Calculate IEMG on the raw bandpass-filtered signal
    iemg = calculate_iemg(bandpass_signal)

    # Normalize the bandpass-filtered signal
    normalized_signal = normalize_signal(bandpass_signal)

    # Calculate time-domain features for the raw and normalized signal
    normalized_features = calculate_time_domain_features(normalized_signal)

    # Apply DWT on the normalized signal
    dwt_coeffs = apply_dwt(normalized_signal)

    # Collect features from the DWT coefficients
    dwt_features = np.array([calculate_dwt_features(coeff) for coeff in dwt_coeffs]).flatten()

    # Combine all features
    combined_features = np.concatenate(([iemg], normalized_features, dwt_features))
    return combined_features


def get_processed_data(file):
    # Load the dataset
    data = pd.read_csv(file, delimiter=',')
    data.columns = ['Sensor1', 'Sensor2', 'Sensor3', 'Gesture']

    print("Initial dataset statistics:")
    print(data['Gesture'].value_counts())

    # Initialize lists to store features and labels
    all_features = []
    all_labels = []
    gesture_counts = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0}
    previous_gesture = -1  # Variable to keep track of the previous gesture

    # Iterate through each row of the data
    for index, row in data.iterrows():
        current_gesture = row['Gesture']

        # Check if we have a change in gesture
        if current_gesture != previous_gesture:
            # print(f"\nGesture change detected from {previous_gesture} to {current_gesture} at index {index}.")
            # Process if it's a non-resting gesture or if we are in the resting phase after an active gesture
            if current_gesture != 0 or (current_gesture == 0 and previous_gesture != 0):
                # Process this gesture
                adjusted_start_index = index + delay_samples  # Start processing X ms after the gesture change
                for i in range(num_windows):
                    start = adjusted_start_index + i * step_size
                    end = start + window_size
                    if end <= len(data):
                        window_data = data.iloc[start:end]
                        window_features = process_windows(window_data)
                        all_features.append(window_features)
                        all_labels.append(current_gesture)
                        # print(f"Window {i+1}/{num_windows} for Gesture {current_gesture}: start {start} end {end}")
                    else:
                        print(f"Insufficient data at index {adjusted_start_index} for window {i+1}. Breaking loop.")
                        break
                gesture_counts[current_gesture] += 1
                previous_gesture = current_gesture  # Update the previous gesture

    # Convert the lists to numpy arrays
    features = np.array(all_features)
    labels = np.array(all_labels)

    # Calculate the number of windows for the least frequent non-zero gesture to balance the dataset
    min_non_zero_gesture_count = min(gesture_counts[1], gesture_counts[2], gesture_counts[3], gesture_counts[4],
                                     gesture_counts[5])
    num_windows_to_keep_for_gesture_0 = min_non_zero_gesture_count * num_windows

    # Balance gesture 0 windows to match the total windows of the least frequent non-zero gesture
    gesture_0_indices = np.where(labels == 0)[0]
    np.random.shuffle(gesture_0_indices)
    gesture_0_indices_to_keep = gesture_0_indices[:num_windows_to_keep_for_gesture_0]

    # Create a boolean mask for filtering
    keep_indices = np.zeros_like(labels, dtype=bool)
    keep_indices[gesture_0_indices_to_keep] = True
    for gesture in [1, 2, 3, 4, 5]:
        keep_indices[labels == gesture] = True

    # Filter the arrays
    features = features[keep_indices]
    labels = labels[keep_indices]

    # Save balanced preprocessed data to NPZ
    output_file = os.path.join(os.path.dirname(file), '../data_combined/preprocessed/XXXXX.npz')
    np.savez(output_file, features=features, labels=labels)
    print(f"Balanced preprocessed data saved to {output_file}")

    # Final processing statistics
    print("Number of windows extracted for each gesture after balancing:")
    for gesture in range(6):  # Includes gesture 0
        print(f"Gesture {gesture}: {np.sum(labels == gesture)} windows")

    print(f"Final Features Shape: {features.shape}, Labels Shape: {labels.shape}")

    return features, labels
