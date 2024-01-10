# Automated Microgreen Cultivation System

## Overview:

This project aims to create an efficient and automated microgreen cultivation system using innovative technologies and practices. The system integrates sensors, relays, and the ESP32S3 + SX1262 development board for optimal control and monitoring. The cultivation process is soilless, focusing on water-based growth with an emphasis on low power, space efficiency, and remote management through a web dashboard.

## System Components:

| Component                           | Description                                                               |
| ----------------------------------- | ------------------------------------------------------------------------- |
| ESP32S3 + SX1262 Development Board  | Processing, control, and long-range communication capabilities.           |
| Water Level Sensor                  | Monitors water levels in the reservoir for continuous water supply.       |
| Soilless Medium (e.g., hydroponics) | Provides a medium for seed germination and microgreen growth.              |
| Water Pump Relay                    | Activates water pump based on water level readings.                        |
| LED Grow Lights                     | Illuminates the microgreens for optimal growth (adjustable intensity).    |
| Seed Hopper with Automated Dispenser | Dispenses seeds onto the soilless medium for germination.                  |
| Temperature and Humidity Sensor      | Controls the internal environment for microgreen cultivation.             |
| Netted Strainer                     | Filters and collects mature microgreens for harvesting.                   |

## Pinout and Setup:

### ESP32S3 Pinout:

| Pin     | Function            |
| ------- | ------------------- |
| D1      | Water Pump Relay    |
| D2      | LED Grow Lights     |
| D3      | Seed Dispenser Motor|
| A1      | Water Level Sensor  |
| A2      | Temp & Humidity Sensor|

### System Setup:

1. **Connect the Water Pump Relay:**
   - Connect the water pump relay to GPIO pin D1 on the ESP32S3.

2. **Connect the LED Grow Lights:**
   - Connect the LED grow lights to GPIO pin D2 on the ESP32S3.

3. **Connect the Seed Dispenser Motor:**
   - Connect the seed dispenser motor to GPIO pin D3 on the ESP32S3.

4. **Connect the Water Level Sensor:**
   - Connect the water level sensor to analog pin A1 on the ESP32S3.

5. **Connect the Temperature and Humidity Sensor:**
   - Connect the temperature and humidity sensor to analog pin A2 on the ESP32S3.

## Innovative Ideas:

1. **Low Power Mode:**
   - Utilize deep sleep mode for ESP32S3 between sensor readings to conserve energy.
   - Implement solar panels for partial or full off-grid power supply.

2. **Adaptive Lighting:**
   - Utilize machine learning algorithms to adjust LED light intensity based on microgreen growth stages.
   - Optimize energy consumption by providing the necessary light for growth.

3. **Vertical Hydroponic System:**
   - Design a vertical hydroponic system to maximize space efficiency.
   - Incorporate automated nutrient delivery for optimal plant nutrition.

4. **Wireless Remote Monitoring:**
   - Use the SX1262 for long-range communication to enable remote monitoring and control.
   - Implement a web dashboard accessible via the internet for real-time monitoring.

5. **Water Recycling System:**
   - Integrate a water recycling system to minimize water wastage.
   - Collect and filter runoff water, then redistribute it to the hydroponic system.

6. **Microgreens Filtering Process:**
   - Implement a netted strainer that automatically filters and collects mature microgreens.
   - Design a stage for dumping harvested microgreens into a collection area.

## System Workflow:

1. **Initialization:**
   - ESP32S3 initializes and establishes a connection with the SX1262 module.

2. **Seed Dispensing:**
   - Seeds are dispensed from the hopper onto the hydroponic medium using an automated dispenser.

3. **Sensor Readings:**
   - Water level, temperature, and humidity readings are periodically collected.

4. **Germination Stage:**
   - Control LED grow lights and watering cycles for the germination stage.

5. **Mature Microgreens Filtering:**
   - Netted strainer activates to filter and collect mature microgreens when ready for harvesting.

6. **Harvesting Stage:**
   - Dump harvested microgreens into the collection area.

7. **Communication:**
   - Transmit data to a remote server for storage and analysis.
   - Web dashboard allows users to monitor system status, receive alerts, and adjust settings.

8. **Low Power Mode:**
   - Enter low-power sleep mode between readings to conserve energy.
