// File: Wemos_D1_NRF905.ino
// GND (Wemos D1) to GND (NRF905)
// 3.3V (Wemos D1) to VCC (NRF905)
// D5 (Wemos D1) to SCK (NRF905)
// D6 (Wemos D1) to MISO (NRF905)
// D7 (Wemos D1) to MOSI (NRF905)
// D8 (Wemos D1) to CSN (NRF905)
// D2 (Wemos D1) to CE (NRF905)
// D1 (Wemos D1) to PWR (NRF905)
// D0 (Wemos D1) to DR (NRF905)

#include <ESP8266WiFi.h>
#include <RH_NRF905.h>
#include <SPI.h>

// NRF905 setup
#define CSN_PIN D8
#define CE_PIN D2
#define DR_PIN D0
#define PWR_PIN D1

RH_NRF905 nrf905(CSN_PIN, CE_PIN, PWR_PIN, DR_PIN);

void setup() {
    Serial.begin(9600);
    while (!Serial); // Wait for serial port to be available

    // Initialize the NRF905 module
    if (!nrf905.init()) {
        Serial.println("NRF905 init failed");
        while (1);
    }
    Serial.println("NRF905 init succeeded");

    // Set the network parameters
    nrf905.setFrequency(433.0); // Frequency in MHz
}

void loop() {
    // Sending data
    const char* msg = "Hello, World!";
    nrf905.send((uint8_t*)msg, strlen(msg));
    nrf905.waitPacketSent();
    Serial.println("Message sent: Hello, World!");

    // Receiving data
    if (nrf905.available()) {
        uint8_t buf[RH_NRF905_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (nrf905.recv(buf, &len)) {
            Serial.print("Received: ");
            Serial.println((char*)buf);
        } else {
            Serial.println("Receive failed");
        }
    }

    delay(1000);
}
