# Evaluating a TensorFlow Lite Model for Gesture Recognition
# This script loads test data, evaluates a TensorFlow Lite model on the test data,
# and calculates performance metrics including accuracy, precision, recall, F1 score, and inference time.
# It also generates and displays a normalized confusion matrix.

import numpy as np
import tensorflow as tf
from sklearn.metrics import confusion_matrix, precision_recall_fscore_support
import seaborn as sns
import matplotlib.pyplot as plt
import time

# Load the test data
test_data = np.load('test_data.npz')
x_test = test_data['x_test']
y_test = test_data['y_test']
test_data.close()

# Load the TFLite model and allocate tensors
interpreter = tf.lite.Interpreter(model_path="XXXXX.tflite")
interpreter.allocate_tensors()

# Get input and output tensor details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Variables to store predictions and actual labels
predictions = []
actual_labels = []
inference_times = []

# Iterate over each test sample and predict
for i in range(len(x_test)):
    test_sample = x_test[i:i + 1]
    actual_label = y_test[i]

    # Start timing inference
    start_time = time.time()
    interpreter.set_tensor(input_details[0]['index'], test_sample.astype(np.float32))
    interpreter.invoke()
    output_data = interpreter.get_tensor(output_details[0]['index'])

    # End timing inference
    end_time = time.time()

    # Calculate inference time
    inference_time = end_time - start_time
    inference_times.append(inference_time)

    predicted_class = np.argmax(output_data)
    predictions.append(predicted_class)
    actual_labels.append(actual_label)

# Calculate overall accuracy
accuracy = np.mean(np.array(predictions) == np.array(actual_labels))
print(f"Overall accuracy: {accuracy:.2%}")

# Calculate precision, recall, and F1 score
precision, recall, f1, _ = precision_recall_fscore_support(actual_labels, predictions, average='weighted')
print(f"Precision: {precision:.2f}, Recall: {recall:.2f}, F1 Score: {f1:.2f}")

# Calculate and display confusion matrix
conf_matrix = confusion_matrix(actual_labels, predictions)
conf_matrix_normalized = conf_matrix.astype('float') / conf_matrix.sum(axis=1)[:, np.newaxis]  # Normalize the matrix

plt.figure(figsize=(10, 7))
sns.heatmap(conf_matrix_normalized, annot=True, fmt=".2f", cmap="Blues", annot_kws={"size": 15})
plt.title('Normalized Confusion Matrix')
plt.ylabel('Actual Label')
plt.xlabel('Predicted Label')

# Annotate overall accuracy and F1 score on the plot
plt.text(0.5, -0.1, f'Overall Accuracy: {accuracy:.2%}\nF1 Score: {f1:.2f}', size=12, ha='center', va='bottom', transform=plt.gca().transAxes)

plt.show()

# Print average inference time
average_inference_time = sum(inference_times) / len(inference_times)
print(f"Average inference time per sample: {average_inference_time:.7f} seconds")
