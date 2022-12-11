#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "o-turki";      // "REPLACE_WITH_YOUR_SSID"
const char *password = "01234567"; // "REPLACE_WITH_YOUR_PASSWORD"
unsigned long previousMillis = 0;
unsigned long interval = 30000; // 30 seconds

void connect2Network();

void setup()
{
  Serial.begin(115200);

  // Connect to Network
  connect2Network();
}

void loop()
{
  unsigned long currentMillis = millis();

  // If WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval))
  {
    // Serial.println(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}

void connect2Network()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }

  Serial.println("");
  Serial.println("================================================================================");
  Serial.println("> Connected to WiFi network \"" + WiFi.SSID() + "\"");
  Serial.println("> IP Address: " + WiFi.localIP().toString());
  Serial.println("> MAC Address: " + WiFi.macAddress());
  Serial.println("================================================================================");
}