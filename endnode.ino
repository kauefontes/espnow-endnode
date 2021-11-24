#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 2

void setup()
{
  initialSetup();
  setupAccessPoint();
  startEspnow();
}

void initialSetup()
{
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Starting endnode...");
  WiFi.mode(WIFI_AP);
}

void setupAccessPoint()
{
  String prefix = "endnode: ";
  String macAddress = WiFi.macAddress();
  String ssid = prefix + macAddress;
  String password = "9876543210";
  bool result = WiFi.softAP(ssid.c_str(), password.c_str(), CHANNEL, 0);
  if (!result)
  {
    Serial.println("AP setup failed");
  }
  else
  {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(ssid));
  }
}

void startEspnow()
{
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK)
  {
    Serial.println("ESPNow Init Success");
  }
  else
  {
    Serial.println("ESPNow init failed, rebooting now...");
    ESP.restart();
  }
  esp_now_register_recv_cb(onDataRecv);
}

void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  char macAdrStr[18];
  snprintf(macAdrStr, sizeof(macAdrStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  handleCommand();
  Serial.print("Last Packet Received from: ");
  Serial.println(macAdrStr);
  Serial.print("Last Packet Received Data: ");
  Serial.println(*data);
  Serial.println("");
}

void handleCommand()
{
  bool isRead = false;
  if (isRead)
  {
    isRead = false;
    startReader();
  }
  else
  {
    isRead = true;
    startActuator();
  }
}

void startActuator()
{
  Serial.println("Watering the garden...");
}

void startReader()
{
  Serial.println("Gathering information...");
}

void loop() {}