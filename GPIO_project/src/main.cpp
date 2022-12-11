#include <Arduino.h>

// set pin numbers
#define BUTTON_PIN 4 // the number of the pushbutton pin
#define LED_PIN 2    // the number of the LED pin
#define BUZZER_PIN 5 // the number of the buzzer pin

// variable for storing the pushbutton status
int buttonState = 0;

void setup()
{
    Serial.begin(115200);

    // initialize the pushbutton pin as an input
    // pinMode(BUTTON_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);
    // initialize the LED and the buzzer pins as an output
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    // read the state of the pushbutton value
    buttonState = digitalRead(BUTTON_PIN);

    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH
    if (buttonState == HIGH)
    {
        Serial.print("The button is pressed: ");
        Serial.println(buttonState);

        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        Serial.print("The button is released: ");
        Serial.println(buttonState);

        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }
}