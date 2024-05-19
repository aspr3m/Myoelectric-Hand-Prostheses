// This program is designed to run on an ESP32 microcontroller to monitor sensor readings, manage a state machine with
// hold and rest states, and control LEDs and a button for starting and stopping the monitoring process.
// The program uses a hardware timer for precise sensor reading intervals and manages state transitions based on a countdown timer.
// This program connects to section 3.3 Data Acquisition and Preparation in the thesis

#include "esp_bt.h"
#include "esp_pm.h"
#include "esp32-hal-cpu.h"
#include "esp32-hal-timer.h"
#include "WiFi.h"
#include <ezButton.h>  // Include the eZButton library

// Configuration Constants
const int SENSOR_PIN1 = 34;             // Sensor 1 - ADC1
const int SENSOR_PIN2 = 35;             // Sensor 2 - ADC1
const int SENSOR_PIN3 = 14;             // Sensor 3 - ADC2
const int LED1_PIN = 32;                // LED for indicating program status
const int LED2_PIN = 33;                // LED for indicating program status
const int STATUS_LED_PIN = 25;          // LED for indicating program hold/pause
const int BUTTON_PIN = 13;              // Button for starting/stopping the program
const int SAMPLE_INTERVAL_MICROS = 516; // Interval in microseconds between each serial print (516 = +/-1938Hz (500 = 2kHz))
const long COUNTDOWN_DURATION = 5000;   // 5 seconds for both hold and rest
const long DELAYED_LOG_END = 300;       // Lets the program run for 300ms after last hold_gesture
const int MAX_TRANSITIONS = 20;         // For adjusting the countdown repetition

// State Enumeration
enum State {
    REST,
    HOLD_GESTURE
};

// Global Variables
unsigned long previousMicros = 0;        // To track the last micros() call
unsigned long stateChangeMillis = 0;     // To track the last state change in millis
int gestureActive = 0;                   // Flag to indicate if gesture is active
int transitionCount = 0;                 // Count of state transitions
bool countdownActive = false;            // Flag to indicate if countdown is active
unsigned long lastHoldEndTime = 0;       // Track when the last HOLD_GESTURE ended
bool isAwaitingFinalRest = false;        // Indicates waiting for the final rest period
State currentState = REST;               // Current state of the program
ezButton button(BUTTON_PIN);             // Button to control countdown

hw_timer_t *timer = NULL;                // Hardware timer
volatile bool timerFlag = false;         // Timer flag for interrupt

// Timer interrupt service routine
void IRAM_ATTR onTimer() {
    timerFlag = true; // Set the flag to indicate that it's time to read sensors
}

void setup() {
    // Prepare the ESP32 for max speed, resolution, and power usage
    esp_bt_controller_disable();          // Disable Bluetooth to save power
    setCpuFrequencyMhz(240);              // Set CPU frequency to 240 MHz
    WiFi.mode(WIFI_OFF);                  // Disable WiFi to save power
    analogReadResolution(12);             // Set ADC resolution to 12 bits

    // Use a high baud rate for high-speed serial print
    Serial.begin(1000000);

    // Initialize LED pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, HIGH);   // Turn on the status LED at startup

    // Initialize the Button with debounce
    button.setDebounceTime(50);

    // Initialize hardware timer
    timer = timerBegin(0, 80, true);       // Timer 0, prescaler 80 (1 MHz), count up
    timerAttachInterrupt(timer, &onTimer, true); // Attach onTimer function
    timerAlarmWrite(timer, SAMPLE_INTERVAL_MICROS, true); // Fire timer every X microseconds
    timerAlarmEnable(timer);               // Enable the timer

    stateChangeMillis = millis();          // Initialize state change time
}

void updateLEDs(long timeLeft) {
    // Both LEDs on during hold gesture
    if (currentState == HOLD_GESTURE) {
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
    }

    // Transitioning to rest
    if (currentState == HOLD_GESTURE && timeLeft < 1000) {
        digitalWrite(LED1_PIN, LOW);         // LED1 off, LED2 remains on
    }

    // Both LEDs off during rest
    if (currentState == REST && timeLeft > 0) {
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
    }

    // Transitioning to hold gesture
    if (currentState == REST && timeLeft < 1000) {
        digitalWrite(LED1_PIN, HIGH);        // LED1 on, LED2 remains off
    }
}

void loop() {
    button.loop(); // Must call the loop() function for button debounce

    unsigned long currentMillis = millis();

    if(button.isPressed()) {
        if (countdownActive) {
            // Cancel the current run and reset the state for a fresh start
            countdownActive = false;
            transitionCount = 0;
            currentState = REST;
            gestureActive = 0;
            isAwaitingFinalRest = false;
            digitalWrite(LED1_PIN, LOW);
            digitalWrite(LED2_PIN, LOW);
            digitalWrite(STATUS_LED_PIN, HIGH); // Turn on the status LED indicating program is stopped
        } else {
            // Start or restart the program
            countdownActive = true;
            transitionCount = 0;
            currentState = REST;
            stateChangeMillis = millis();
            digitalWrite(STATUS_LED_PIN, LOW); // Turn off the status LED when the program starts
        }
    }

    if (countdownActive || isAwaitingFinalRest) {
        if (timerFlag) {
            timerFlag = false; // Reset the flag

            // Read sensors and send data
            int sensorValue1 = analogRead(SENSOR_PIN1);
            int sensorValue2 = analogRead(SENSOR_PIN2);
            int sensorValue3 = analogRead(SENSOR_PIN3);

            Serial.print(micros());
            Serial.print(",");
            Serial.print(sensorValue1);
            Serial.print(",");
            Serial.print(sensorValue2);
            Serial.print(",");
            Serial.print(sensorValue3);
            Serial.print(",");
            Serial.println(gestureActive);
        }

        long timeLeft = COUNTDOWN_DURATION - (currentMillis - stateChangeMillis);
        if (timeLeft <= 0) {
            if (currentState == REST) {
                currentState = HOLD_GESTURE;
                gestureActive = 1;
                if (transitionCount < MAX_TRANSITIONS) transitionCount++; // Increment transition count
            } else {
                currentState = REST;
                gestureActive = 0;
                lastHoldEndTime = currentMillis; // Update last HOLD_GESTURE end time
                if (transitionCount >= MAX_TRANSITIONS) {
                    countdownActive = false; // Stop counting after max transitions
                    isAwaitingFinalRest = true; // Begin the final rest period
                }
            }
            stateChangeMillis = currentMillis;
            timeLeft = COUNTDOWN_DURATION;
        }
        updateLEDs(timeLeft);
    }

    // Final check to halt the program after the additional rest period
    if (isAwaitingFinalRest && (currentMillis - lastHoldEndTime >= DELAYED_LOG_END)) {
        isAwaitingFinalRest = false; // Reset to avoid repeating this block
        digitalWrite(STATUS_LED_PIN, HIGH);   // Turn on the status LED indicating program is stopped
    }
}
