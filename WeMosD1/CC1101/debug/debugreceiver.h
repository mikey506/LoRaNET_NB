// WeMos / CC1101 Pinout
// ---------------------
// D1 / GDO0
// D2 / GD02
// D5 / SCK
// 3V3 / VCC
// D7 / MOSI
// D6 / MISO
// D8 / CSN
// GND / GND

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RadioLib.h>

// Define CC1101 pins
#define CC1101_CS_PIN 15  // D8
#define CC1101_GDO0_PIN 5 // D1
#define CC1101_GDO2_PIN 4 // D2

const char* ssid = "WIFI_SSID";
const char* password = "WIFIPASSWORD";

// Create a new CC1101 instance
CC1101 radio = new Module(CC1101_CS_PIN, CC1101_GDO0_PIN, RADIOLIB_NC, CC1101_GDO2_PIN);

// Create an instance of the ESP8266WebServer class
ESP8266WebServer server(80);

// Variables to store configuration settings
float frequency = 915.0;
int8_t power = 10;
float bitRate = 4.8;

// Function to handle HTTP requests for the root URL "/"
void handleRoot() {
  String message = "<html><body><h1>CC1101 Debug Information</h1>";

  message += "<p>[CC1101] Initialization: ";
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Set frequency to 433 MHz
  state = radio.setFrequency(frequency);
  message += "<p>Set Frequency: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Set output power to 10 dBm
  state = radio.setOutputPower(power);
  message += "<p>Set Output Power: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Set data rate to 4.8 kbps
  state = radio.setBitRate(bitRate);
  message += "<p>Set Bit Rate: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Enter receive mode
  state = radio.startReceive();
  message += "<p>Enter Receive Mode: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Display CC1101 configuration
  message += "<h2>CC1101 Configuration</h2>";
  message += "<p>Frequency: ";
  message += frequency;
  message += " MHz</p>";
  message += "<p>Output Power: ";
  message += power;
  message += " dBm</p>";
  message += "<p>Bit Rate: ";
  message += bitRate;
  message += " kbps</p>";

  // Check for incoming data
  if (radio.available()) {
    message += "<p>Data received!</p>";
    byte buffer[64];
    int length = radio.readData(buffer, sizeof(buffer));
    message += "<p>Data length: ";
    message += length;
    message += "</p><p>Data: ";
    for (int i = 0; i < length; i++) {
      message += String(buffer[i], HEX);
      message += " ";
    }
    message += "</p>";

    // Get RSSI (signal strength)
    float rssi = radio.getRSSI();
    message += "<p>RSSI: ";
    message += rssi;
    message += " dBm</p>";

    // Get SNR (signal-to-noise ratio)
    float snr = radio.getSNR();
    message += "<p>SNR: ";
    message += snr;
    message += " dB</p>";
  }

  message += "</body></html>";
  server.send(200, "text/html", message);
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);  // Ensure baud rate matches Serial Monitor

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming HTTP requests
  server.handleClient();
}
