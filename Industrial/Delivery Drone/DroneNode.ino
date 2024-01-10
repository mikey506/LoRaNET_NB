#include <Wire.h>
#include <SparkFun_Serial_Controlled_Motor_Driver_Arduino_Library.h>
#include <LoRa.h>
#include <Ultrasonic.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>

#define LORA_CS_PIN 18
#define LORA_RST_PIN 14
#define LORA_IRQ_PIN 26

#define ULTRASONIC_TRIG_PIN 2
#define ULTRASONIC_ECHO_PIN 4

#define BMP280_SDA_PIN 21
#define BMP280_SCL_PIN 22

#define GPS_SERIAL_RX 16
#define GPS_SERIAL_TX 17

#define NODE_ID 1  // Unique ID for each drone node

Ultrasonic ultrasonic(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN);
Adafruit_BMP280 bmp280;

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_IRQ_PIN);

  if (!bmp280.begin(BMP280_SDA_PIN, BMP280_SCL_PIN)) {
    Serial.println("BMP280 initialization failed. Check your connections.");
    while (1);
  }

  GPSSerial.begin(9600, SERIAL_8N1, GPS_SERIAL_RX, GPS_SERIAL_TX);

  Serial.println("Drone Node Initialized");
}

void loop() {
  float distance = ultrasonic.read();
  float altitude = bmp280.readAltitude();

  // Read GPS data
  while (GPSSerial.available()) {
    gps.encode(GPSSerial.read());
  }

  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    
    // Create payload
    String payload = "NODE_ID:" + String(NODE_ID) +
                     "|DISTANCE:" + String(distance) +
                     "|ALTITUDE:" + String(altitude) +
                     "|LATITUDE:" + String(latitude, 6) +
                     "|LONGITUDE:" + String(longitude, 6);

    // Send payload via LoRa
    LoRa.beginPacket();
    LoRa.print(payload);
    LoRa.endPacket();

    Serial.println("Data sent: " + payload);
  }

  delay(1000);  // Adjust delay as needed
}
