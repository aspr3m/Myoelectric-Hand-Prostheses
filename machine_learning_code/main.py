# TensorFlow CNN Training for Gesture Recognition
# This script defines, trains, and evaluates a CNN model using TensorFlow for gesture recognition.
# It supports loading preprocessed data, splits data into training/validation/test sets,
# and visualizes training results. The trained model is also converted to TensorFlow Lite format.

import tensorflow as tf
from sklearn.model_selection import train_test_split
from data import get_processed_data
import numpy as np
import matplotlib.pyplot as plt

# Global configuration variables
kernel_size_lvl1 = 2
filters_lvl1 = 64
kernel_size_lvl2 = 2
filters_lvl2 = 128
kernel_size_lvl3 = 2
filters_lvl3 = 128
dense_units_lvl1 = 128
dense_units_lvl2 = 6
start_learning_rate = 0.001
batch_size = 64
dropout_rate = 0.4
epochs = 100
file_path = '../data_combined/preprocessed/XXXX.npz'
test_size = 0.2
validation_size = 0.25
l2_reg = 0.005


# Define the CNN model architecture
def cnn_model():
    model = tf.keras.models.Sequential([
        # Input layer specification
        tf.keras.layers.InputLayer(input_shape=(17, 3)),

        # First convolutional block
        tf.keras.layers.Conv1D(filters_lvl1, kernel_size=kernel_size_lvl1, activation='relu', padding='same',
                               kernel_regularizer=tf.keras.regularizers.l2(l2_reg)),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.MaxPooling1D(2, strides=2, padding='same'),

        # Second convolutional block
        tf.keras.layers.Conv1D(filters_lvl2, kernel_size=kernel_size_lvl2, activation='relu', padding='same',
                               kernel_regularizer=tf.keras.regularizers.l2(l2_reg)),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.MaxPooling1D(2, strides=2, padding='same'),

        # Third convolutional block
        tf.keras.layers.Conv1D(filters_lvl3, kernel_size=kernel_size_lvl3, activation='relu', padding='same',
                               kernel_regularizer=tf.keras.regularizers.l2(l2_reg)),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.MaxPooling1D(2, strides=2, padding='same'),

        # Flattening the convolved data to feed into dense layers
        tf.keras.layers.Flatten(),

        # First dense block
        tf.keras.layers.Dense(dense_units_lvl1, activation='relu'),
        tf.keras.layers.Dropout(dropout_rate),

        # Output layer for classification
        tf.keras.layers.Dense(6, activation='softmax')
    ])
    return model


# Function to compile and train the model
def compile_and_train_model(model, x_train, y_train, x_val, y_val, epochs):
    adam_optimizer = tf.keras.optimizers.Adam(learning_rate=start_learning_rate)
    model.compile(optimizer=adam_optimizer, loss='sparse_categorical_crossentropy', metrics=['accuracy'])

    # Define callbacks for early stopping and learning rate reduction
    termination = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=10, restore_best_weights=True)
    checkpoint_cb = tf.keras.callbacks.ModelCheckpoint("best_model", save_best_only=True)
    reduce_lr = tf.keras.callbacks.ReduceLROnPlateau(monitor='val_loss', factor=0.25, patience=3, min_lr=0.0000001)

    # Fit the model
    history = model.fit(
        x_train, y_train, epochs=epochs, validation_data=(x_val, y_val),
        batch_size=batch_size, verbose=1, callbacks=[termination, checkpoint_cb, reduce_lr]
    )
    return history


def load_data():
    # Ask the user for input
    choice = input("Enter 1 to preprocess new data, or 2 to load preprocessed data: ")

    if choice == '1':
        # Load and preprocess new data
        filepath = '../data_combined/XXXXX.csv'
        features, labels = get_processed_data(filepath)
        print("Data preprocessed from CSV file.")
    elif choice == '2':
        # Load preprocessed data from NPZ file
        filepath = file_path
        with np.load(filepath) as data:
            features = data['features']
            labels = data['labels']
        print("Data loaded from preprocessed NPZ file.")
    else:
        raise ValueError("Invalid input! Enter 1 or 2.")

    return features, labels


# Main script to load data, create model, train, and plot results
if __name__ == "__main__":
    features, labels = load_data()

    # Split data into training, validation, and test sets
    x_train_val, x_test, y_train_val, y_test = train_test_split(features, labels,
                                                                test_size=test_size, random_state=42)
    np.savez('test_data.npz', x_test=x_test, y_test=y_test)
    x_train, x_val, y_train, y_val = train_test_split(x_train_val, y_train_val,
                                                      test_size=validation_size, random_state=42)

    # Model setup and training
    model = cnn_model()
    history = compile_and_train_model(model, x_train, y_train, x_val, y_val, epochs)
    model.summary()

    # Convert to TensorFlow Lite model
    converter = tf.lite.TFLiteConverter.from_keras_model(model)
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS, tf.lite.OpsSet.SELECT_TF_OPS]
    tfliteModel = converter.convert()
    with open('XXXX.tflite', 'wb') as f:
        f.write(tfliteModel)
    print("Model converted and saved successfully.")

    # Plot details
    config_details = (f"Filters: {filters_lvl1}-{filters_lvl2}-{filters_lvl3}, "
                      f"Kernel Sizes: {kernel_size_lvl1}-{kernel_size_lvl2}-{kernel_size_lvl3}, "
                      f"Dense Units: {dense_units_lvl1}-{dense_units_lvl2}, "
                      f"Start LR: {start_learning_rate}, "
                      f"Dropout: {dropout_rate}, "
                      f"Batch Size: {batch_size}, "
                      f"L2 Reg: {l2_reg}, "
                      f"Max epochs: {epochs}, "
                      f"Test Size: {test_size}, "
                      f"Validation Size: {validation_size*(1-test_size)}")
    filename_details = file_path.split('/')[-1].split('.')[0]

    # Visualization of training and validation metrics
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    plt.plot(history.history['accuracy'], label='Training Accuracy')
    plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
    plt.title('Model Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(history.history['loss'], label='Training Loss')
    plt.plot(history.history['val_loss'], label='Validation Loss')
    plt.title('Model Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()

    # Adding configuration details and filename details using figtext
    plt.figtext(0.5, 0.08, config_details, ha="center", fontsize=10, bbox={"facecolor": "orange", "alpha": 0.5, "pad": 5})
    plt.figtext(0.5, 0.02, f"Data file: {filename_details}", ha="center", fontsize=10,
                bbox={"facecolor": "orange", "alpha": 0.5, "pad": 5})

    plt.tight_layout(rect=(0, 0.1, 1, 1))  # Adjust layout to make room for figtext
    plt.show()
