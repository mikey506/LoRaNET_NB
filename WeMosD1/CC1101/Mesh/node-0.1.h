#include <SPI.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <BluetoothSerial.h>
#include <AESLib.h>

BluetoothSerial SerialBT;

// Define encryption key
const char *aes_key = "your-128bit-key"; // Must be 16 characters
AESLib aesLib;

// Buffer for AES encryption/decryption
char cleartext[128];
char ciphertext[128];
char decryptedtext[128];

// Function to encrypt data
void encryptData(char *data, char *encryptedData) {
    aesLib.encrypt64(data, aes_key, encryptedData);
}

// Function to decrypt data
void decryptData(char *encryptedData, char *data) {
    aesLib.decrypt64(encryptedData, aes_key, data);
}

void setup() {
    Serial.begin(115200);
    SerialBT.begin("WeModD1Mini");

    // Initialize CC1101
    if (ELECHOUSE_cc1101.getCC1101()) {
        Serial.println("CC1101 found.");
    } else {
        Serial.println("CC1101 not found.");
        while (1);
    }

    ELECHOUSE_cc1101.Init();       // Initialize CC1101
    ELECHOUSE_cc1101.setMHZ(433);  // Set frequency

    // Bluetooth callback
    SerialBT.register_callback(btCallback);
}

void loop() {
    // Check for incoming Bluetooth data
    if (SerialBT.available()) {
        String btData = SerialBT.readString();
        btData.toCharArray(cleartext, 128);

        // Encrypt the data
        encryptData(cleartext, ciphertext);

        // Send the encrypted data over LoRa
        ELECHOUSE_cc1101.SendData((byte *)ciphertext, strlen(ciphertext));
        Serial.println("Data sent over LoRa.");
    }

    // Check for incoming LoRa data
    if (ELECHOUSE_cc1101.CheckReceiveFlag()) {
        byte rxData[128] = {0};
        ELECHOUSE_cc1101.ReceiveData(rxData);
        decryptData((char *)rxData, decryptedtext);
        SerialBT.println(decryptedtext);
        Serial.print("Received and decrypted data: ");
        Serial.println(decryptedtext);
    }
}

void btCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    if (event == ESP_SPP_SRV_OPEN_EVT) {
        Serial.println("Bluetooth connected.");
    }
}
