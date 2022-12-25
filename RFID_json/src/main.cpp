#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>

#define SCK 18
#define MOSI 23
#define MISO 19
#define SS_PIN 2
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

const int buzzer = 5;

const char *ssid = "o-turki";      // "REPLACE_WITH_YOUR_SSID"
const char *password = "01234567"; // "REPLACE_WITH_YOUR_PASSWORD"
const char *apiServer = "http://192.168.199.61/iot_lab/";

void connect2Network();
String httpGETRequest(String endPoint);
String httpPOSTRequest(String endPoint, String data);

String tagRFID = "";
String endPoint = "";
String studentJSON = "";
String presenceData = "";
String presenceDataJson = "";

void setup()
{
    Serial.begin(115200);
    pinMode(buzzer, OUTPUT);

    SPI.begin();
    delay(100);
    mfrc522.PCD_Init();

    connect2Network();
}

void loop()
{
    if (mfrc522.PICC_IsNewCardPresent())
    {
        if (mfrc522.PICC_ReadCardSerial())
        {
            digitalWrite(buzzer, HIGH);
            delay(100);
            digitalWrite(buzzer, LOW);
            delay(100);
            digitalWrite(buzzer, HIGH);
            delay(100);
            digitalWrite(buzzer, LOW);

            tagRFID = "";
            for (byte i = 0; i < mfrc522.uid.size; i++)
            {
                tagRFID += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "") + String(mfrc522.uid.uidByte[i], HEX);
            }
            Serial.println("> tagRFID: " + tagRFID);

            endPoint = apiServer + String("?rfid=" + tagRFID);
            Serial.println("> endPoint: " + endPoint);

            studentJSON = httpGETRequest(endPoint);
            Serial.println("> studentJSON: " + studentJSON);

            if (studentJSON.length() > 4)
            {
                StaticJsonDocument<128> studentDoc;
                DeserializationError error = deserializeJson(studentDoc, studentJSON);

                if (error)
                {
                    Serial.print("deserializeJson() failed: ");
                    Serial.println(error.c_str());
                    return;
                }

                int id = studentDoc["id"];                         // 1
                const char *rfid = studentDoc["rfid"];             // "539fac19"
                const char *first_name = studentDoc["first_name"]; // "John"
                const char *last_name = studentDoc["last_name"];   // "Doe"

                Serial.println("================================================================================");
                Serial.println("> Hello,");
                Serial.println("> " + String(first_name) + " " + String(last_name));
                Serial.println("================================================================================");

                // SERIALIZE DATA (Convert to JSON)
                StaticJsonDocument<128> presenceDoc;
                presenceDoc["first_name"] = String(first_name);
                presenceDoc["last_name"] = String(last_name);
                presenceData = "";
                serializeJson(presenceDoc, presenceData);
                Serial.println("> presenceData: " + presenceData);

                // SEND A POST REQUEST WITH DATA
                endPoint = apiServer;
                presenceDataJson = httpPOSTRequest(endPoint, presenceData);
                Serial.println("> presenceDataJson: " + presenceDataJson);
            }

            Serial.println(); // print an empty line
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
        }
    }
}

void connect2Network()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("\nConnecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }

    Serial.println("\n================================================================================");
    Serial.println("> Connected to WiFi network \"" + WiFi.SSID() + "\"");
    Serial.println("> IP Address: " + WiFi.localIP().toString());
    Serial.println("> MAC Address: " + WiFi.macAddress());
    Serial.println("================================================================================\n");
}

String httpGETRequest(String endPoint)
{
    HTTPClient http;
    http.begin(endPoint);
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode > 0)
    {
        // Serial.print("HTTP Response code: ");
        // Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
    return payload;
}

String httpPOSTRequest(String endPoint, String data)
{
    HTTPClient http;
    http.begin(endPoint);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(data);

    String payload = "{}";

    if (httpResponseCode > 0)
    {
        // Serial.print("HTTP Response code: ");
        // Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
    return payload;
}
