#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL = 2;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNowinit failed");
    ESP.restart();
  }
}