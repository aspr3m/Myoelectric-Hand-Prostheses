// ESP32 Sensor Reading with Hardware Timer
// This program sets up an ESP32 to read sensor values from three ADC pins at precise intervals
// using a hardware timer. The sensor values are printed to the serial monitor at the specified interval.
// Used for transfer realtime data directly to a PC connected with USB in conjunction with the realtime.py

#include "esp32-hal-timer.h" // Include necessary library for hardware timer
#include "WiFi.h"
#include "esp_bt.h"

// Configuration Constants
const int SENSOR_PIN1 = 34;             // Sensor 1 - ADC1
const int SENSOR_PIN2 = 35;             // Sensor 2 - ADC1
const int SENSOR_PIN3 = 14;             // Sensor 3 - ADC2
const int SAMPLE_INTERVAL_MICROS = 516; // Interval in microseconds between each serial print

// Hardware timer variable
hw_timer_t *timer = NULL;
volatile bool timerFlag = false;

// Timer interrupt routine
void IRAM_ATTR onTimer() {
    timerFlag = true; // Set the flag to indicate that it's time to read sensors
}

void setup() {
    // Prepare the ESP32 for max speed, resolution and power usage
    esp_bt_controller_disable();          // Disable Bluetooth to save power
    setCpuFrequencyMhz(240);              // Set CPU frequency to 240 MHz
    WiFi.mode(WIFI_OFF);                  // Disable WiFi to save power
    analogReadResolution(12);             // Set ADC resolution to 12 bits

    // Use a high baud rate for high-speed serial print
    Serial.begin(1000000);

    // Initialize hardware timer
    timer = timerBegin(0, 80, true);       // Timer 0, prescaler 80 (1 MHz), count up
    timerAttachInterrupt(timer, &onTimer, true); // Attach onTimer function
    timerAlarmWrite(timer, SAMPLE_INTERVAL_MICROS, true); // Fire timer every SAMPLE_INTERVAL_MICROS
    timerAlarmEnable(timer);               // Enable the timer
}

void loop() {
    if (timerFlag) {
        timerFlag = false; // Reset the flag

        // Read sensors and send data
        int sensorValue1 = analogRead(SENSOR_PIN1);
        int sensorValue2 = analogRead(SENSOR_PIN2);
        int sensorValue3 = analogRead(SENSOR_PIN3);

        // Print the micros timestamp and sensor values
        Serial.print(sensorValue1);
        Serial.print(",");
        Serial.print(sensorValue2);
        Serial.print(",");
        Serial.println(sensorValue3);
    }
}
