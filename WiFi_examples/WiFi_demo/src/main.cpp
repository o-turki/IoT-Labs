#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "o-turki";      // "REPLACE_WITH_YOUR_SSID"
const char *password = "01234567"; // "REPLACE_WITH_YOUR_PASSWORD"

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }

  Serial.print("\nESP32 Local IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}