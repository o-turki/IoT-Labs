#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SCK 18
#define MOSI 23
#define MISO 19
#define SS_PIN 2
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

const int buzzer = 5;

String tagRFID = "";

void setup()
{
    Serial.begin(115200);
    pinMode(buzzer, OUTPUT);

    // RFID
    SPI.begin(); // Init SPI bus
    delay(100);
    mfrc522.PCD_Init();
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

            Serial.println("> TAG RFID: " + tagRFID);

            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
        }
    }
}