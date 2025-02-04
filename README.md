**Battery Protection System**
Overview
The Battery Protection System is designed to enhance battery life, prevent overheating, and reduce fire hazards by automatically controlling the supply to the connected vehicle based on real-time data. The system also supports remote monitoring and control via a mobile application, ensuring safe and efficient battery operation.

Features
Automatic Safety Mechanism: Monitors temperature, voltage, and current to prevent overheating, overvoltage, and undervoltage conditions.
Remote Monitoring and Control: Allows users to access real-time battery data and control power supply via a mobile application.
Cloud Integration: Uses Firebase for real-time data storage and retrieval.
User-Defined Control: Enables users to manually turn the battery supply on or off remotely.
Components Used
Arduino Mega: Core processing unit for sensor monitoring.
ESP8266 Wi-Fi Module: Handles wireless data transfer and relay control.
Voltage Sensor: Detects undervoltage and overvoltage conditions.
Current Sensor (ACS712): Measures the battery's current flow.
DHT11 Sensor: Monitors the ambient temperature of the battery system.
I2C Display: Provides a real-time display of monitored data.
Relay Module: Controls the power supply based on sensor data.
Firebase: Cloud platform for data storage and retrieval.
Mobile Application: Built with App Inventor for remote monitoring and control.
Working Process
Arduino Mega

Monitors battery temperature, voltage, and current using sensors.
Transmits data to the ESP8266 via serial communication (RX/TX).
ESP8266

Uploads sensor data to Firebase.
Controls the relay to manage battery power supply based on thresholds.
Receives control signals from Firebase for remote power management.
Firebase

Stores and retrieves real-time sensor data.
Facilitates seamless interaction between hardware and the mobile application.
Mobile Application

Displays real-time battery data (temperature, voltage, current).
Allows users to control the battery supply remotely.
Protocols and Communication
Serial Communication: Between Arduino Mega and ESP8266 for data transmission.
Wi-Fi Communication: Between ESP8266 and Firebase for real-time data exchange.
I2C Protocol: Between Arduino Mega and the I2C display for real-time data visualization.
Contributions
Designed and integrated hardware components (Arduino Mega, ESP8266, sensors, display, relay module).
Programmed the Arduino Mega for sensor monitoring and data transmission.
Configured ESP8266 for Wi-Fi setup, data handling, and relay control.
Developed a mobile application for remote monitoring and control using App Inventor.
Integrated Firebase for real-time data storage and control functionality.
Tested and calibrated the system to ensure reliable operation and safety protocols.
Project Highlights
Prevention of Hazards: Automatically disconnects the battery during unsafe conditions.
Real-Time Monitoring: Displays live data on a mobile application and I2C display.
User-Friendly Control: Enables manual or automatic power control through the app.
How to Use
Hardware Setup:

Connect the Arduino Mega, ESP8266, sensors, I2C display, and relay module as per the circuit diagram.
Ensure proper calibration of sensors.
Software Setup:

Upload the Arduino Mega code to monitor sensors and send data to ESP8266.
Flash the ESP8266 code for Wi-Fi setup, Firebase integration, and relay control.
Firebase Configuration:

Set up a Firebase database to store sensor data and control commands.
Mobile App:

Install the app (developed using App Inventor).
Configure it with your Firebase credentials to start monitoring and controlling the battery system.
Testing:

Test the system by varying temperature, voltage, and current conditions to verify the safety protocols.
Future Enhancements
Add predictive maintenance features using machine learning.
Integrate additional sensors for enhanced monitoring (e.g., humidity, pressure).
Extend support for other cloud platforms.
License
This project is licensed under the MIT License.
