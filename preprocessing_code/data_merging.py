# Combining Multiple CSV Files into a Single Dataset
# This script combines multiple CSV files containing sensor data into a single CSV file.
# It excludes the first column from each file and appends the remaining data into a combined dataset.
# The combined dataset is then saved to a new CSV file.

import numpy as np
import glob

# List all CSV files you want to combine
file_list = glob.glob('../data/temp/*.csv')

# Load each file, excluding the first column, and stack them
combined_data = np.vstack([np.loadtxt(f, delimiter=',')[:, 1:] for f in file_list])

# Define your header
header = "Sensor1,Sensor2,Sensor3,Gesture"

# Save the combined array to a new CSV file
np.savetxt('../data_combined/XXXXX.csv', combined_data, delimiter=',', fmt='%d', header=header, comments='')
