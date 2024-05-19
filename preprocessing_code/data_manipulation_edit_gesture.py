# Updating Gesture Labels in a CSV File
# This script loads a CSV file containing sensor data and modifies the last column
# to update the gesture labels. The modified data is then saved back to a new CSV file.

import numpy as np

# Step 1: Load the CSV file
data = np.loadtxt('../data/gesture_5/02-5-3_1.csv', delimiter=',')

# Step 2: Modify the last column
# Replace the gesture label 1 with the new label 2 (Change as needed)
data[data[:, -1] == 1, -1] = 2

# Step 3: Save the modified array to a new CSV file
np.savetxt('../data/gesture_2/01-2-1_1.csv', data, delimiter=',', fmt='%d')
