![image](https://github.com/mikey506/LoRaNET_NB/assets/13043850/45336f45-cc63-4604-8cee-8c4802794673)

# ESP32S3 Mesh Network Project Overview

## Hardware

- **Development Board:** ESP32S3 with built-in SX1262 LoRa module and BLE
- **LoRa Module:** RFM95 or compatible module
- **Wi-Fi Module:** Integrated into ESP32S3
- **Power Supply:** USB or external power source

## Software

- **ESP-Mesh Library:** For creating a mesh network with ESP32S3 nodes.
- **RH_RF95 Library:** For LoRa communication using RFM95 module.
- **WiFi Library:** For Wi-Fi connectivity.
- **Arduino IDE:** For writing, compiling, and uploading code to ESP32S3.

| Functionality                  | Description                                                                                          |
| ------------------------------ | ---------------------------------------------------------------------------------------------------- |
| **Mesh Network**               | - Nodes form a mesh network using the ESP-Mesh library.                                              |
|                                | - Dynamic topology: Nodes can join and leave the mesh network seamlessly.                            |
| **LoRa Communication**         | - Utilizes the RFM95 module for long-range, low-power LoRa communication.                             |
|                                | - Nodes can send and receive data over LoRa.                                                         |
|                                | - Data relayed through the mesh network for better coverage.                                          |
| **Wi-Fi Communication**        | - Nodes connect to a Wi-Fi network for higher bandwidth communication.                               |
|                                | - Wi-Fi data sent to other nodes in the mesh network.                                                |
|                                | - Wi-Fi data relayed through the mesh network for extended coverage.                                  |
| **Node Interaction**           | - Nodes can interact with each other using both Wi-Fi and LoRa.                                       |
|                                | - Relay mechanism ensures data is transmitted to all nodes within the mesh.                           |
| **Web Dashboard (Optional)**   | - Built-in HTTP server for accessing a dashboard.                                                     |
|                                | - Dashboard displays statistics, CPU/Memory/Storage information, and LoRa traffic.                    |
|                                | - Accessed upon connection to the AP for debugging and development purposes.                          |
| **Bluetooth Debugging (Optional)** | - BLE functionality can be leveraged for Bluetooth debugging.                                        |
|                                   | - Provides general information about hardware and statistics.                                         |


## Conclusion

The ESP32S3 Mesh Network Project combines the capabilities of ESP32S3 development boards, LoRa RF communication, and Wi-Fi to create a versatile mesh network. The project's software utilizes the ESP-Mesh library for mesh networking, the RH_RF95 library for LoRa communication, and standard Wi-Fi libraries for Wi-Fi communication. The mesh network allows nodes to interact seamlessly, and data can be relayed over both Wi-Fi and LoRa for extended coverage. Additionally, optional features such as a web dashboard and Bluetooth debugging provide tools for development and monitoring. The project is suitable for applications requiring a combination of long-range, low-power communication (LoRa) and higher bandwidth communication (Wi-Fi) within a mesh network.
