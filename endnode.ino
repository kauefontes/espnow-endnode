#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 2

void setup()
{
  initialSetup();
}

void initialSetup()
{
  Serial.begin(115200);
  Serial.println("Starting endnode...");
  WiFi.mode(WIFI_AP);
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