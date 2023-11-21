#include <LoRa.h>

#define LORA_CS 5      // Choose a suitable pin for Chip Select (CS)
#define LORA_RST 14     // Choose a suitable pin for Reset (RST)
#define LORA_IRQ 2      // Choose a suitable pin for Interrupt Request (IRQ)

void setup() {
  Serial.begin(115200);

  // Initialize LoRa
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }
  Serial.println("LoRa initialized");

  // Start listening for incoming packets
  LoRa.receive();
}

void loop() {
  // Check if a packet has been received
  if (LoRa.parsePacket()) {
    Serial.println("Received a packet!");

    // Read the payload
    String payload = "";
    while (LoRa.available()) {
      payload += (char)LoRa.read();
    }

    // Print the received data
    Serial.println("Payload: " + payload);
  }
}
