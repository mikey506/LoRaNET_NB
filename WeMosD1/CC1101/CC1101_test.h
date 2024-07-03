#include <ELECHOUSE_CC1101_SRC_DRV.h>

// Define CC1101 pins
#define CC1101_CS_PIN D8
#define CC1101_MOSI_PIN D7
#define CC1101_MISO_PIN D6
#define CC1101_SCLK_PIN D5
#define CC1101_GDO0_PIN D2
#define CC1101_GDO2_PIN D1

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
    // Wait for serial port to connect
  }

  // Initialize CC1101 module
  ELECHOUSE_cc1101.setCSN(CC1101_CS_PIN);
  ELECHOUSE_cc1101.setMOSI(CC1101_MOSI_PIN);
  ELECHOUSE_cc1101.setMISO(CC1101_MISO_PIN);
  ELECHOUSE_cc1101.setSCK(CC1101_SCLK_PIN);
  ELECHOUSE_cc1101.setGDO0(CC1101_GDO0_PIN);
  ELECHOUSE_cc1101.setGDO2(CC1101_GDO2_PIN);

  if (ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("CC1101 Module initialized successfully.");
  } else {
    Serial.println("CC1101 Module initialization failed.");
    while (1);
  }

  // Configure CC1101 settings
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setMHZ(433); // Set frequency to 433 MHz

  // Set transmission power
  ELECHOUSE_cc1101.setPA(10); // 0-10, 0 is min power, 10 is max power

  // Set data rate
  ELECHOUSE_cc1101.setDRate(4.8); // Data rate in kbps

  // Print configuration
  Serial.print("Frequency: ");
  Serial.print(ELECHOUSE_cc1101.getMHZ());
  Serial.println(" MHz");
  Serial.print("Data Rate: ");
  Serial.print(ELECHOUSE_cc1101.getDRate());
  Serial.println(" kbps");
  Serial.print("Transmit Power: ");
  Serial.print(ELECHOUSE_cc1101.getPA());
  Serial.println();

  // Enter receive mode
  ELECHOUSE_cc1101.SetReceive();
}

void loop() {
  // Check for incoming data
  if (ELECHOUSE_cc1101.CheckReceiveFlag()) {
    Serial.println("Data received!");
    byte buffer[64];
    byte length = ELECHOUSE_cc1101.ReceiveData(buffer);

    Serial.print("Data length: ");
    Serial.println(length);
    Serial.print("Data: ");
    for (byte i = 0; i < length; i++) {
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Clear receive flag
    ELECHOUSE_cc1101.ClearReceiveFlag();
  }
}
