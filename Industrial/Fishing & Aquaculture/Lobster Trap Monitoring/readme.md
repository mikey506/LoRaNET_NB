# Lobster Trap Monitoring and Tracking System

## Objective
Develop an underwater node system for monitoring and tracking lobster traps. The system utilizes an ESP32S3 development board, an SX1262 LoRa RF module for long-range communication, and integrates sensors including a Digital Barometric Pressure Sensor (BMP280), DS18B20 Temperature Sensor, MPU-6050 6DOF Accelerometer Gyroscope Sensor, and a GPS Module NEO-6M for precise GPS location tracking. The nodes are designed to broadcast sensory data via LoRa RF communication, forming a mesh network for extended range and efficient data relay to nearby nodes or a central receiving node (server).

## Components

### Hardware
| Component                              | Description                                                    |
| -------------------------------------- | -------------------------------------------------------------- |
| ESP32S3 Development Board              | Low power consumption, Arduino IDE compatibility.              |
| SX1262 LoRa Module                     | Long-range communication for underwater applications.          |
| Digital Barometric Pressure Sensor     | Measures water depth with high accuracy (BMP280).               |
| DS18B20 Temperature Sensor             | Monitors water temperature for environmental analysis.          |
| MPU-6050 6DOF Accelerometer Gyroscope  | Measures water currents and detects movements (MPU-6050).       |
| GPS Module NEO-6M                      | Adds GPS functionality for precise location tracking.          |
| Power Supply                           | Low-power, rechargeable battery suitable for underwater use.    |

# Pinout Instructions

| Component                              | Pinout Instructions                                         |
| -------------------------------------- | ------------------------------------------------------------ |
| ESP32S3 Development Board              | No specific pinout for this table. Refer to ESP32S3 datasheet and reference documentation. |
| SX1262 LoRa Module                     | - CS: 18<br>- RST: 14<br>- IRQ: 26                           |
| Digital Barometric Pressure Sensor     | - SDA: Connect to ESP32S3 I2C SDA<br>- SCL: Connect to ESP32S3 I2C SCL |
| DS18B20 Temperature Sensor             | - One wire: Connect to a digital pin on ESP32S3 (e.g., GPIO 4) |
| MPU-6050 6DOF Accelerometer Gyroscope  | - SDA: Connect to ESP32S3 I2C SDA<br>- SCL: Connect to ESP32S3 I2C SCL |
| GPS Module NEO-6M                      | - TX: Connect to ESP32S3 RX (e.g., GPIO 16)<br>- RX: Connect to ESP32S3 TX (e.g., GPIO 17) |
| Power Supply                           | No specific pinout for this table. Refer to the power supply datasheet or documentation. |

## ESP32S3 GPIO Configuration

- Configure ESP32S3 GPIO pins in the script based on the provided pinout instructions for each module/sensor.

// Example GPIO Configuration
#define ONE_WIRE_BUS 4        // DS18B20 Temperature Sensor
#define GPS_SERIAL_RX 16      // GPS Module NEO-6M RX
#define GPS_SERIAL_TX 17      // GPS Module NEO-6M TX
// Additional GPIO configurations for other modules/sensors

### Software
| Component                     | Description                                                |
| ----------------------------- | ---------------------------------------------------------- |
| LoRa Communication Library    | RadioHead library for LoRa communication via SX1262 module. |
| Sensor Libraries              | Adafruit_BMP280, OneWire, DallasTemperature, MPU6050, TinyGPS++ for interfacing with sensors. |
| Mesh Networking Library        | ESP-MESH library for creating a mesh network among underwater nodes. |
| Arduino IDE                   | Platform for programming and uploading code to the ESP32S3.  |



## Script Overview
- **Setup:**
  - Initializes serial communication, LoRa, GPS, and sensor configurations.
- **Loop:**
  - Reads sensor data including pressure, temperature, accelerometer, gyroscope, and GPS location.
  - Creates a payload with the sensor data and the unique node ID.
  - Broadcasts the payload via LoRa RF communication.
- **LoRa Communication:**
  - Configures the LoRa module for communication and sends sensor data as LoRa packets.
- **Sensor Readings:**
  - Utilizes specific libraries to read data from the BMP280, DS18B20, MPU-6050, and NEO-6M sensors.
- **Mesh Networking (To be expanded):**
  - Placeholder for implementing mesh networking logic based on ESP-MESH or other suitable libraries.

## Conclusion
This lobster trap monitoring and tracking system integrates cutting-edge sensor technologies, including precise GPS location tracking, to ensure comprehensive and accurate data collection in challenging underwater environments. The mesh network architecture enhances the system's reliability and extends its range, making it an effective solution for real-time monitoring and management of lobster traps. The system's adaptability allows for further expansion and integration into a centralized monitoring server for comprehensive analysis and control.
