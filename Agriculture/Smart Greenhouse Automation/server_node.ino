// Dashboard Template Repo: https://github.com/PanJiaChen/vue-element-admin

#include <LoRa.h>

const int LORA_CS = 5;   // LoRa radio chip select
const int LORA_RST = 14;  // LoRa radio reset
const int LORA_IRQ = 2;   // LoRa radio irq
const char *encryptionKey = "YourEncryptionKey";

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Set up LoRa
  LoRa.begin(868E6);
  LoRa.setSpreadingFactor(12);

  Serial.println("LoRa Server Node Started");
}

void loop() {
  if (LoRa.parsePacket()) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    // Decrypt message if encrypted
    // Example: message = decryptMessage(message, encryptionKey);

    // Process the received message
    processMessage(message);
  }
}

void processMessage(String message) {
  // Implement logic to process messages from relay or sensor node
  // Example: check if the message is a request for relay status, a command to change relay status, or other sensor data

  if (message.equals("REQUEST_RELAY_STATUS")) {
    // Respond with the current relay status
    sendResponse(getRelayStatus());
  } else if (message.startsWith("RELAY_STATUS_UPDATE")) {
    // Update relay status based on the received message
    updateRelayStatus(message);
    Serial.println("Relay status updated by relay node.");
  } else {
    Serial.println("Unknown message received.");
  }
}

void sendResponse(String response) {
  // Encrypt response if necessary
  // Example: response = encryptMessage(response, encryptionKey);

  // Send response to relay or sensor node
  LoRa.beginPacket();
  LoRa.print(response);
  LoRa.endPacket();
}

String getRelayStatus() {
  // Implement logic to get the current relay status
  // Example: Assuming relayStatus is a global variable
  return "{\"relayStatus\":" + String(digitalRead(relayPin)) + "}";
}

void updateRelayStatus(String message) {
  // Extract the relay status from the message
  int relayStatus = message.substring(message.indexOf(':') + 1).toInt();

  // Update the relay status (assuming relayStatus is a global variable)
  relayStatus = relayStatus;

  // Set the relay pin based on the updated status
  digitalWrite(relayPin, relayStatus);

  // Print a message indicating the update
  Serial.println("Relay status updated: " + String(relayStatus));
}
