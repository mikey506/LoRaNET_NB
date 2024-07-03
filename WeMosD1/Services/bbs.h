#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <vector>
#include <algorithm> // For std::sort

const char* ssid = "SSID";
const char* password = "Password";
const int telnetPort = 23;

WiFiServer server(telnetPort);
WiFiClient clients[5];
String messageBoard[10];
int currentMessageIndex = 0;

struct WiFiNetwork {
  String ssid;
  int32_t rssi;
  String encryptionType;
  int32_t channel;
  String macAddress;
  bool isHidden;
};

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.begin();
  for (int i = 0; i < 5; i++) {
    clients[i] = WiFiClient();
  }
  Serial.println("Server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  for (int i = 0; i < 5; i++) {
    if (!clients[i] || !clients[i].connected()) {
      clients[i] = server.available();
      if (clients[i]) {
        clients[i].print("\033[2J"); // Clear screen
        printAsciiArt(clients[i]);
        clients[i].println("Welcome to the Pocket / BBS!");
        clients[i].println("Type 'help' for a list of commands.");
      }
    } else {
      if (clients[i].available()) {
        String command = readCommand(clients[i]);
        processCommand(command, clients[i]);
      }
    }
  }
}

void printAsciiArt(WiFiClient client) {
  client.println("\033[1;32m");
  client.println("Pocket / BBS");
  client.println("\033[0m");
}

String readCommand(WiFiClient client) {
  String command;
  while (client.available()) {
    char c = client.read();
    command += c;
    if (c == '\n') {
      break;
    }
  }
  command.trim();
  return command;
}

void processCommand(String command, WiFiClient client) {
  if (command.startsWith("post")) {
    handlePostCommand(command, client);
  } else if (command.startsWith("read")) {
    handleReadCommand(client);
  } else if (command.startsWith("delete")) {
    handleDeleteCommand(command, client);
  } else if (command.startsWith("clear")) {
    handleClearCommand(client);
  } else if (command.startsWith("help")) {
    handleHelpCommand(client);
  } else if (command.startsWith("scanwifi")) {
    scanWifi(client);
  } else {
    client.println("Unknown command. Type 'help' for a list of commands.");
  }
}

void handlePostCommand(String command, WiFiClient client) {
  command.remove(0, 5); // Remove "post " from the command
  command.trim(); // Remove leading/trailing whitespace
  if (command.length() < 1) {
    client.println("Usage: post [message]");
    return;
  }
  if (currentMessageIndex >= 10) {
    client.println("Message board is full. Please delete some messages.");
    return;
  }
  messageBoard[currentMessageIndex] = command;
  currentMessageIndex++;
  client.println("Message posted successfully.");
}

void handleReadCommand(WiFiClient client) {
  client.print("\033[2J"); // Clear screen
  printAsciiArt(client);
  client.println("=== Message Board ===");
  for (int i = 0; i < currentMessageIndex; i++) {
    client.print(i + 1);
    client.print(". ");
    client.println(messageBoard[i]);
  }
}

void handleDeleteCommand(String command, WiFiClient client) {
  command.remove(0, 7); // Remove "delete " from the command
  command.trim(); // Remove leading/trailing whitespace
  if (command.length() < 1) {
    client.println("Usage: delete [message number]");
    return;
  }
  int messageNumber = command.toInt();
  if (messageNumber < 1 || messageNumber > currentMessageIndex) {
    client.println("Invalid message number.");
    return;
  }
  for (int i = messageNumber - 1; i < currentMessageIndex - 1; i++) {
    messageBoard[i] = messageBoard[i + 1];
  }
  currentMessageIndex--;
  client.println("Message deleted successfully.");
}

void handleClearCommand(WiFiClient client) {
  client.print("\033[2J"); // Clear screen
  printAsciiArt(client);
  client.println("Message board cleared.");
  for (int i = 0; i < currentMessageIndex; i++) {
    messageBoard[i] = "";
  }
  currentMessageIndex = 0;
}

void handleHelpCommand(WiFiClient client) {
  client.print("\033[2J"); // Clear screen
  printAsciiArt(client);
  client.println("Available commands:");
  client.println("post [message] - Post a new message");
  client.println("read - Read all messages");
  client.println("delete [message number] - Delete a message");
  client.println("clear - Clear the message board");
  client.println("help - Display this help message");
  client.println("scanwifi - Scan for available WiFi networks");
}

bool compareBySignalStrength(const WiFiNetwork &a, const WiFiNetwork &b) {
  return a.rssi > b.rssi; // Sort in descending order of signal strength
}

void scanWifi(WiFiClient client) {
  client.println("Scanning WiFi networks, please wait...");

  int networkCount = WiFi.scanNetworks();

  if (networkCount == 0) {
    client.println("No WiFi networks found.");
    return;
  }

  std::vector<WiFiNetwork> networks;
  for (int i = 0; i < networkCount; ++i) {
    WiFiNetwork network;
    network.ssid = WiFi.SSID(i);
    network.rssi = WiFi.RSSI(i);
    network.channel = WiFi.channel(i);
    network.macAddress = WiFi.BSSIDstr(i);
    network.isHidden = WiFi.isHidden(i);
    switch (WiFi.encryptionType(i)) {
      case ENC_TYPE_WEP: network.encryptionType = "WEP"; break;
      case ENC_TYPE_TKIP: network.encryptionType = "WPA/TKIP"; break;
      case ENC_TYPE_CCMP: network.encryptionType = "WPA2/CCMP"; break;
      case ENC_TYPE_NONE: network.encryptionType = "None"; break;
      case ENC_TYPE_AUTO: network.encryptionType = "Auto"; break;
      default: network.encryptionType = "Unknown"; break;
    }
    networks.push_back(network);
  }

  std::sort(networks.begin(), networks.end(), compareBySignalStrength);

  client.println("Sorted networks by signal strength:");
  client.println("ID | SSID              | RSSI  | Security    | Channel | MAC Address       | Hidden");
  client.println("------------------------------------------------------------------------------------------");

  for (size_t i = 0; i < networks.size(); ++i) {
    const auto& net = networks[i];
    client.printf("%2d | %-17s | %4d dBm | %-11s | %7d | %17s | %s\n",
                  i + 1, net.ssid.c_str(), net.rssi, net.encryptionType.c_str(), net.channel, net.macAddress.c_str(), net.isHidden ? "Yes" : "No");
    client.println();
  }

  WiFi.scanDelete();
}
