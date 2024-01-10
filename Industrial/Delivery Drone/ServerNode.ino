#include <Wire.h>
#include <LoRa.h>

#define LORA_CS_PIN 18
#define LORA_RST_PIN 14
#define LORA_IRQ_PIN 26

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_IRQ_PIN);

  Serial.println("Server Node Initialized");
}

void loop() {
  // Receive data via LoRa
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";

    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    Serial.println("Received Data: " + receivedData);
    // Add your server logic here
  }

  delay(1000);  // Adjust delay as needed
}
