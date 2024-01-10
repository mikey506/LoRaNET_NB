# LoRa RF Delivery Drone System

## Objective
Design and implement an advanced drone delivery system utilizing LoRa RF communication for long-range connectivity. The system integrates a variety of sensors, including ultrasonic sensors for collision detection, a GY-NEO6MV2 GPS module for accurate location tracking, an 8-channel relay board for component control, and a BMP280 Altitude Sensor Module for monitoring altitude and height. The ESP32S3+SX1262 development board serves as the central processing unit.

## Components

### Hardware
| Component                              | Description                                              |
| --------------------------------------| -------------------------------------------------------- |
| ESP32S3+SX1262 Development Board      | Powerful MCU with LoRa RF capability for efficient communication. |
| BMP280 Altitude Sensor Module          | Measures altitude and provides height information.       |
| SIM800L GPRS GSM Module                | Enables 3G communication for use in areas with poor LoRa signal. |
| 8 Channel Relay Board                   | Controls drone components and provides a relay for power management. |
| Power Bank Shell for 10x 18650 Batteries| Provides a digital display and powers the drone.          |
| GY-NEO6MV2 GPS Module                  | Accurate GPS tracking for location-based operations.     |
| Ultrasonic Sensors (6)                 | Front, back, left, right, top, and bottom sensors for collision detection. |

### Pinout Instructions
| Component                            | Pinout Instructions                                  |
| -------------------------------------| ----------------------------------------------------- |
| ESP32S3+SX1262 Development Board   | - SX1262 CS: 18<br>- SX1262 RST: 14<br>- SX1262 IRQ: 26 |
| BMP280 Altitude Sensor Module       | - SDA: Connect to ESP32S3 I2C SDA<br>- SCL: Connect to ESP32S3 I2C SCL |
| SIM800L GPRS GSM Module             | - TX: Connect to ESP32S3 RX (e.g., GPIO 16)<br>- RX: Connect to ESP32S3 TX (e.g., GPIO 17) |
| 8 Channel Relay Board               | No specific pinout for this table. Refer to the relay board datasheet or documentation. |
| Power Bank Shell                    | No specific pinout for this table. Refer to the power bank shell datasheet or documentation. |
| GY-NEO6MV2 GPS Module               | - TX: Connect to ESP32S3 RX (e.g., GPIO 16)<br>- RX: Connect to ESP32S3 TX (e.g., GPIO 17) |
| Ultrasonic Sensors (6)              | Connect to appropriate GPIO pins on ESP32S3 for each sensor. |

### Software
| Software Component                   | Description                                              |
| -------------------------------------| -------------------------------------------------------- |
| Drone Movement                       | Implements stabilizing, forward, backward, left and right rotation functionalities. |
| Power Management                     | Monitors battery levels and implements low-power consumption strategies. |
| GPS Tracking                         | Utilizes the GPS module to track the drone's precise location. |
| LoRa RF Communication                | Establishes communication with the server using LoRa RF for normal conditions. |
| 3G Communication                     | Utilizes the SIM800L module for communication during poor LoRa signal conditions. |
| Altitude Monitoring                  | Monitors and reports altitude using the BMP280 sensor.   |
| Mapping                              | Stores detailed maps in memory for locating delivery spots. |
| Server Communication                 | Handles coordination of drones and deliveries on the server. |

## Script Overview

1. **Connections:**
   - Connect the ESP32S3+SX1262 development board to the specified pins for the LoRa module (CS, RST, IRQ), BMP280 Altitude Sensor Module (SDA, SCL), SIM800L GPRS GSM Module (TX, RX), GY-NEO6MV2 GPS Module (TX, RX), and Ultrasonic Sensors.

2. **Power Supply:**
   - Connect the power bank shell to the drone for supplying power to the ESP32S3+SX1262 development board. Ensure the correct connection to the digital display on the power bank.

3. **Configure Ultrasonic Sensors:**
   - Configure the GPIO pins for the six ultrasonic sensors. Adjust the pinout in the drone script to match the connected GPIO pins.

4. **Configure LoRa Settings:**
   - Adjust LoRa settings in the drone script based on your specific LoRa module configuration, such as frequency (e.g., 915E6).

5. **Configure GPS Module:**
   - Connect the GY-NEO6MV2 GPS Module and configure the serial communication settings in the drone script.

6. **Load Drone Script:**
   - Upload the drone script to the ESP32S3+SX1262 development board using the Arduino IDE or your preferred development environment.

7. **Monitor Serial Output:**
   - Open the serial monitor to view debugging information and ensure proper initialization. Fix any issues if errors are encountered.

8. **Test Drone Functionality:**
   - Verify that the drone is sending sensor data, including distance, altitude, and GPS coordinates, via LoRa.

9. **Adjust Delay and LoRa Frequency:**
   - Fine-tune the delay in the drone script and LoRa frequency to suit the specific requirements of your drone application.

10. **Calibration and Testing:**
    - Calibrate sensors if needed and perform extensive testing to ensure accurate sensor readings and reliable communication.

Remember to handle the drone components with care during the setup process, and adhere to safety guidelines for drone operation. Adjustments may be required based on your specific hardware and requirements.

**Loop:**
Reads sensor data, including ultrasonic sensor readings, GPS location, and altitude.
Creates a payload with the sensor data and unique drone ID.
Communicates with the server using LoRa RF or switches to 3G communication if necessary.
Controls drone movement based on sensor inputs.

## Conclusion
This **LoRa RF Delivery Drone system** integrates innovative components and functionalities to enhance its delivery capabilities. The combination of LoRa RF and 3G communication ensures reliable connectivity in various conditions. The drone's advanced sensor suite provides comprehensive data for efficient and safe navigation, making it a robust solution for delivery operations. The integration of mapping and server communication further enhances the system's overall coordination and control.
