# Signal Processing and Feature Extraction for EMG Data
# This script processes EMG sensor data, applies filters, and extracts features.
# It visualizes the raw and processed signals along with extracted features.

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import pywt
from scipy.signal import iirnotch, butter, sosfiltfilt, tf2sos

# Define global variables for signal processing parameters
fs = 1938  # Sampling rate (Hz)
f0 = 50.0  # Notch filter frequency (Hz)
quality_factor = 50.0  # Notch filter quality factor
bandpass_lowcut = 20  # Bandpass filter low cutoff frequency (Hz)
bandpass_highcut = 350  # Bandpass filter high cutoff frequency (Hz)
bandpass_order = 4  # Bandpass filter order
window_size_ms = 300
data_end = int(fs * (window_size_ms / 1000))


def notch_filter(data):
    b, a = iirnotch(f0, quality_factor, fs)
    sos = tf2sos(b, a)
    return sosfiltfilt(sos, data)


def bandpass_filter(data):
    nyq = 0.5 * fs
    low = bandpass_lowcut / nyq
    high = bandpass_highcut / nyq
    sos = butter(bandpass_order, [low, high], btype='band', output='sos')
    return sosfiltfilt(sos, data)


def apply_dwt(signal):
    coeffs = pywt.wavedec(signal, 'db4', level=4)
    return coeffs  # Returns a list of arrays [cA4, cD4, cD3, cD2, cD1]


# Helper function to normalize the signal
def normalize_signal(signal):
    return (signal - np.mean(signal)) / np.std(signal)


# Calculate different statistical features from different signal window:
def calculate_iemg(signal):
    return np.sum(np.abs(signal))  # IEMG


def calculate_time_domain_features(signal):
    return np.array([
        np.mean(np.abs(signal)),    # MAV
        np.sum(np.abs(signal))      # IEMG
    ])


def calculate_dwt_features(coeff):
    return np.array([
        np.sum(np.abs(coeff)),              # IEMG
        np.sqrt(np.mean(np.square(coeff))), # RMS
        np.mean(np.abs(coeff))              # MAV
    ])


def plot_signal_and_features(sensor_name, signals, titles, feature_texts):
    num_plots = len(signals)
    fig, axs = plt.subplots(num_plots, 1, figsize=(10, num_plots * 3), constrained_layout=True)

    for ax, signal, title, features in zip(axs, signals, titles, feature_texts):
        ax.plot(signal)
        ax.set_title(f'{sensor_name} - {title}')
        ax.set_ylabel('Amplitude')
        ax.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)

        text_box_props = dict(boxstyle='round', facecolor='yellow', edgecolor='black', linewidth=1)
        ax.text(0.5, -0.05, features, transform=ax.transAxes, fontsize=9,
                horizontalalignment='center', verticalalignment='top', bbox=text_box_props)

    plt.subplots_adjust(hspace=0.5)  # Adjust the spacing
    plt.show()


def process_and_plot(file_path, start_index, end_index):
    data = pd.read_csv(file_path)
    for sensor in ['Sensor1', 'Sensor2', 'Sensor3']:
        sensor_data = data[sensor].values[start_index:end_index]

        notched_data = notch_filter(sensor_data)
        filtered_data = bandpass_filter(notched_data)
        iemg = calculate_iemg(filtered_data)  # Calculate IEMG on raw bandpass-filtered signal

        normalized_data = normalize_signal(filtered_data)  # Normalize the signal
        normalized_features = calculate_time_domain_features(normalized_data)  # Calculate time-domain features

        dwt_coeffs = apply_dwt(normalized_data)  # Apply DWT
        dwt_features = [calculate_dwt_features(coeff) for coeff in dwt_coeffs]  # Extract DWT features

        # Prepare plots and feature texts
        signals = [filtered_data, normalized_data] + dwt_coeffs
        titles = ['Filtered Data', 'Normalized Data'] + [f'DWT Level {i+1}' for i in range(len(dwt_coeffs))]
        feature_texts = [
                            f"IEMG: {iemg:.4f}",
                            f"MAV: {normalized_features[0]:.4f}, IEMG: {normalized_features[1]:.4f}",
                        ] + [f"IEMG: {feat[0]:.4f}, RMS: {feat[1]:.4f}, MAV: {feat[2]:.4f}" for feat in dwt_features]

        plot_signal_and_features(sensor, signals, titles, feature_texts)


if __name__ == '__main__':
    file_path = '../data_combined/XXXXX.csv'
    start_index = 13000
    end_index = start_index + data_end
    process_and_plot(file_path, start_index, end_index)
