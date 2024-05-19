# Signal Processing and Visualization for EMG Data
# This script applies notch and bandpass filters to EMG sensor data, normalizes the data,
# and visualizes the frequency spectrum and time series data, highlighting gesture events.
# Mainly used for testing and verifying of signal

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import iirnotch, filtfilt, butter, sosfiltfilt, tf2sos
import time

# Configuration variables
fs = 1938  # Sampling rate in Hz
f0 = 50.0  # Target frequency to filter out in Hz
quality_factor = 50.0  # Quality factor for the notch filter
bandpass_lowcut = 20
bandpass_highcut = 350
bandpass_order = 4

def plot_frequency_spectrum(signal1, signal2, fs):
    """
    Plots the frequency spectrum of two signals using FFT on the same plot for comparison.

    Parameters:
    - signal1: 1D array-like, the first signal to be transformed.
    - signal2: 1D array-like, the second signal to be transformed.
    - fs: float, the sampling rate of the signal in Hz.
    """
    n1 = len(signal1)
    yf1 = np.fft.fft(signal1)
    xf1 = np.fft.fftfreq(n1, 1 / fs)[:n1//2]

    n2 = len(signal2)
    yf2 = np.fft.fft(signal2)
    xf2 = np.fft.fftfreq(n2, 1 / fs)[:n2//2]

    plt.figure(figsize=(12, 6))
    plt.plot(xf1, 2.0/n1 * np.abs(yf1[0:n1//2]), label='Raw Signal')
    plt.plot(xf2, 2.0/n2 * np.abs(yf2[0:n2//2]), label='Filtered Signal')
    plt.title('Frequency Spectrum Comparison')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.legend()
    plt.show()

def notch_filter(data, cutoff, fs, quality_factor):
    """
    Apply a notch (band-stop) filter to a signal using second-order sections.

    Parameters:
    - data: 1D array-like, the signal to be filtered.
    - cutoff: float, the center frequency to be filtered out in Hz.
    - fs: float, the sampling rate of the signal in Hz.
    - quality_factor: float, the quality factor of the notch filter.

    Returns:
    - filtered_data: array, the filtered signal.
    """
    b, a = iirnotch(cutoff, quality_factor, fs)
    sos = tf2sos(b, a)
    filtered_data = sosfiltfilt(sos, data)
    return filtered_data

def normalize_signal(signal):
    """
    Normalize the signal to have zero mean and unit variance.
    """
    mean = np.mean(signal)
    std = np.std(signal)
    normalized_signal = (signal - mean) / std
    return normalized_signal

def butter_lowpass_filter(data, cutoff=2, fs=1938, order=4):
    """
    Apply a Butterworth low-pass filter to a signal.

    Parameters:
    - data: 1D array-like, the signal to be filtered.
    - cutoff: float, the cutoff frequency of the filter in Hz.
    - fs: float, the sampling rate of the signal in Hz.
    - order: int, the order of the filter.

    Returns:
    - filtered_data: array, the filtered signal.
    """
    nyq = 0.5 * fs
    normal_cutoff = cutoff / nyq
    b, a = butter(order, normal_cutoff, btype='low', analog=False)
    filtered_data = filtfilt(b, a, data)
    return filtered_data

def butter_bandpass_filter(data, lowcut, highcut, fs, order):
    """
    Apply a Butterworth bandpass filter to a signal.

    Parameters:
    - data: 1D array-like, the signal to be filtered.
    - lowcut: float, the lower cutoff frequency of the filter in Hz.
    - highcut: float, the upper cutoff frequency of the filter in Hz.
    - fs: float, the sampling rate of the signal in Hz.
    - order: int, the order of the filter.

    Returns:
    - filtered_bandpass_data: array, the filtered signal.
    """
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    sos = butter(order, [low, high], btype='band', analog=False, output='sos')
    filtered_bandpass_data = sosfiltfilt(sos, data)
    return filtered_bandpass_data

# Load data from CSV
filename = '../data/gesture_1/01-1-1_1.csv'
data = np.loadtxt(filename, delimiter=',')

timestamps_microseconds = data[:, 0]
sensor_values1 = data[:, 1]  # Data from Sensor 1
sensor_values2 = data[:, 2]  # Data from Sensor 2
sensor_values3 = data[:, 3]  # Data from Sensor 3
gesture_state = data[:, 4]  # Gesture state

# Start time
start_time_normalize = time.time()
# Normalize the sensor values
sensor_values1_normalized = normalize_signal(sensor_values1)
sensor_values2_normalized = normalize_signal(sensor_values2)
sensor_values3_normalized = normalize_signal(sensor_values3)
# End time
end_time_normalize = time.time()
print(f"Time taken to normalize: {end_time_normalize - start_time_normalize} seconds")

start_time_notch = time.time()
# Apply the notch filter to the normalized sensor values
sensor_values1_notched = notch_filter(sensor_values1_normalized, f0, fs, quality_factor)
sensor_values2_notched = notch_filter(sensor_values2_normalized, f0, fs, quality_factor)
sensor_values3_notched = notch_filter(sensor_values3_normalized, f0, fs, quality_factor)
end_time_notch = time.time()
print(f"Time taken to notch filter: {end_time_notch - start_time_notch} seconds")

start_time_bandpass = time.time()
# Apply Butterworth bandpass filter
sensor_values1_bandpass_filtered = butter_bandpass_filter(sensor_values1_notched, bandpass_lowcut, bandpass_highcut, fs, bandpass_order)
sensor_values2_bandpass_filtered = butter_bandpass_filter(sensor_values2_notched, bandpass_lowcut, bandpass_highcut, fs, bandpass_order)
sensor_values3_bandpass_filtered = butter_bandpass_filter(sensor_values3_notched, bandpass_lowcut, bandpass_highcut, fs, bandpass_order)
end_time_bandpass = time.time()
print(f"Time taken to bandpass filter: {end_time_bandpass - start_time_bandpass} seconds")
print(f"Time for total filtering: {end_time_bandpass - start_time_normalize} seconds")

# Plot frequency spectrum comparison
plot_frequency_spectrum(sensor_values1_normalized, sensor_values1_bandpass_filtered, fs)

# Convert timestamps from microseconds to seconds
timestamps_seconds = timestamps_microseconds / 1_000_000

# Plotting with gesture indicators
fig, axs = plt.subplots(2, 1, figsize=(12, 9))

# Original Signal
axs[0].plot(timestamps_seconds, sensor_values1, label='Sensor 1', color='blue')
axs[0].plot(timestamps_seconds, sensor_values2, label='Sensor 2', color='orange')
axs[0].plot(timestamps_seconds, sensor_values3, label='Sensor 3', color='grey')

# Normalized and Rectified Signal
axs[1].plot(timestamps_seconds, np.abs(sensor_values1_normalized), label='Sensor 1', color='blue')
axs[1].plot(timestamps_seconds, np.abs(sensor_values2_normalized), label='Sensor 2', color='orange')
axs[1].plot(timestamps_seconds, np.abs(sensor_values3_normalized), label='Sensor 3', color='grey')

# Adding vertical lines for gesture start and end based on actual timestamps
for i in range(1, len(gesture_state)):
    if gesture_state[i] == 3 and gesture_state[i-1] == 0:
        gesture_start_time = timestamps_seconds[i]
        for ax in axs:
            ax.axvline(x=gesture_start_time, color='green', linestyle='-', label='Gesture Start' if i == 1 else "")

        gesture_plus_500ms = gesture_start_time + 0.5
        for ax in axs:
            ax.axvline(x=gesture_plus_500ms, color='green', linestyle='--', label='500ms after start' if i == 1 else "")

        gesture_plus_4s = gesture_plus_500ms + 4.0
        for ax in axs:
            ax.axvline(x=gesture_plus_4s, color='red', linestyle='--', label='4s after 500ms' if i == 1 else "")

    elif gesture_state[i] == 0 and gesture_state[i-1] == 3:
        for ax in axs:
            ax.axvline(x=timestamps_seconds[i], color='red', linestyle='-', label='Gesture End' if i == 1 else "")

# Setting up labels and titles
for ax in axs:
    ax.set_xlabel('Time (seconds)')
    ax.set_ylabel('Sensor Value')
    ax.grid(False)
    ax.legend()

plt.tight_layout()
plt.show()
