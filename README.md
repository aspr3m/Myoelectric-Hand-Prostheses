# Myoelectric Hand Prostheses

![CAD model of the prothesis](/images/prosthesis_split_after_pcb-LQ.png)

## Abstract:
This thesis presents the design, development and assessment of a multi-articulated myoelectric prosthesis customized for the Norwegian market. Prosthetics are essential for restoring function and improving the quality of life for individuals who have lost limbs, but today's advanced multi-articulated prostheses are prohibitively expensive for many who need them. This study include a detailed literature review, theoretical background, methods of development and assessments of results. The methodology covers the approaches and solutions of all hardware and software components, resulting in a fully functional, real-time sEMG driven prosthesis. By employing structured data collection, advanced signal processing and a one dimensional convolutional neural network, a real-time pattern recognition software was developed, delivering a 86\% accurate gesture classification with a 350 ms delay. Another framework was the successful approximation of the human hand joint DOFs, grip functionality and other factors of anthropomorphism. The mechanical aspects, such as tendon driven actuation and design, proves effective in activities of daily living and anthropomorphic properties and cost. The results of this research demonstrates critical functionality of a low cost multi-articulated myoelectric prosthesis that can fill a gap in the Norwegian market. 

## Contents
- **/data**: Contains an outline and an example file of the different raw gesture data sorted as explained in the thesis.
- **/data_combined**: Contains the different datasets used for training and testing the neural network.
- **/emg_signal_processing**: Contains scripts for processing EMG signals, including filtering, normalization, and feature extraction.
- **/esp32_code**: Contains the code for the ESP32 microcontroller used to read sensor data and transfer to PC. Used in conjuction with Arduino IDE
- **/machine_learning_code**: Contains scripts for defining, training, and evaluating machine learning models for gesture recognition.
- **/preprocessing_code**: Contains scripts for preprocessing raw data: combining CSV files and updating gesture labels.
- **/realtime_code**: Contains scripts for real-time gesture recognition, including serial data reading, real-time processing, and GUI display.

## Disclaimer
This repository contains work by students studying Automation and Intelligent Systems at NTNU Ålesund for a BSc thesis on a low-cost 3D-printed Myoelectric Hand Prosthesis for the Norwegian market. 
The goal was to explore feasibility within certain constraints as described more in the full thesis. This repo includes the essential codes and data used in the thesis. The complete thesis is available on the "NTNU Open" platform.
The code and data is not complete but gives a valuable insight in how to continue the work.
