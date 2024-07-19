// VCC: Connect to 3.3V
// GND: Connect to Ground
// CS: Connect to a digital I/O pin (e.g., pin 10)
// MOSI: Connect to the MOSI pin on the microcontroller (usually pin D7 or similar)
// MISO: Connect to the MISO pin on the microcontroller (usually pin D6 or similar)
// SCK: Connect to the SCK pin on the microcontroller (usually pin D5 or similar)
// GDO0/GDO2: Connect to digital I/O pins if you need to use them for specific features (like interrupts or status reporting)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RadioLib.h>

// Define CC1101 pins
#define CC1101_CS_PIN 10
#define CC1101_GDO0_PIN 2
#define CC1101_GDO2_PIN 3

// Wi-Fi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Create a new CC1101 instance
CC1101 radio = new Module(CC1101_CS_PIN, CC1101_GDO0_PIN, RADIOLIB_NC, CC1101_GDO2_PIN);

// Create an instance of the ESP8266WebServer class
ESP8266WebServer server(80);

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
  state = radio.setFrequency(433.0);
  message += "<p>Set Frequency: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Set output power to 10 dBm
  state = radio.setOutputPower(10);
  message += "<p>Set Output Power: ";
  if (state == RADIOLIB_ERR_NONE) {
    message += "Success!</p>";
  } else {
    message += "Failed, code ";
    message += state;
    message += "</p>";
  }

  // Set data rate to 4.8 kbps
  state = radio.setBitRate(4.8);
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

  // Display CC1101 configuration
  message += "<h2>CC1101 Configuration</h2>";
  message += "<p>Frequency: 433.0 MHz</p>";
  message += "<p>Output Power: 10 dBm</p>";
  message += "<p>Bit Rate: 4.8 kbps</p>";

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
