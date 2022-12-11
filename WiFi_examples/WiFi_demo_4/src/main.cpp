#include <Arduino.h>
#include <WiFi.h>

// #define LED 2

const char *ssid = "o-turki";      // "REPLACE_WITH_YOUR_SSID"
const char *password = "01234567"; // "REPLACE_WITH_YOUR_PASSWORD"

unsigned long previousMillis = 0;
unsigned long interval = 30000; // 30 seconds

bool isConnected = false;

void connect2Network();

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to Network
  connect2Network();
}

void loop()
{
  unsigned long currentMillis = millis();

  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval))
  {
    Serial.println("> Reconnecting to WiFi..");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
    digitalWrite(LED_BUILTIN, LOW);
    isConnected = false;
  }

  if ((WiFi.status() == WL_CONNECTED) && !isConnected)
  {
    Serial.println("> Connected..");
    digitalWrite(LED_BUILTIN, HIGH);
    isConnected = true;
  }
}

void connect2Network()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("> Connecting to WiFi ..");
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
