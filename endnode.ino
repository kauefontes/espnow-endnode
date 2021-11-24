#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 2

void setup()
{
  initialSetup();
  setupAP();
}

void initialSetup()
{
  Serial.begin(115200);
  Serial.println("Starting endnode...");
  WiFi.mode(WIFI_AP);
}

void setupAP()
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
    Serial.println("ESPNowinit failed, rebooting now...");
    ESP.restart();
  }
}

void loop() {}