/*
  Smart Farm Controller - Arduino UNO
  Reads the soil-moisture sensor and controls local indicators.
  Sends status to the ESP8266 over SoftwareSerial.

  UNO connections:
    Soil moisture SIG -> A0
    Red LED           -> D8 (through resistor)
    Green LED         -> D9 (through resistor)
    Buzzer            -> D10
    SoftwareSerial RX -> D2 (from ESP8266 TX D4)
    SoftwareSerial TX -> D3 (to ESP8266 RX D6 through a voltage divider)
    GND               -> common GND with ESP8266

  IMPORTANT:
  ESP8266 GPIO pins are 3.3V only. Do not connect UNO D3 directly
  to ESP8266 RX. Use a voltage divider / level shifter.
*/

#include <SoftwareSerial.h>

const byte SOIL_PIN = A0;
const byte RED_LED_PIN = 8;
const byte GREEN_LED_PIN = 9;
const byte BUZZER_PIN = 10;

// UNO RX, TX
SoftwareSerial espSerial(2, 3);

const int DRY_THRESHOLD = 600;  // Calibrate for your sensor and soil.

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL_MS = 1000;

int soilValue = 0;
int redState = 0;
int greenState = 0;
int buzzerState = 0;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  espSerial.begin(9600);

  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Smart Farm Controller - UNO ready");
}

void loop() {
  soilValue = analogRead(SOIL_PIN);

  // Basic indication: high raw reading is treated as dry.
  // Calibrate DRY_THRESHOLD for the particular sensor.
  if (soilValue >= DRY_THRESHOLD) {
    redState = 1;
    greenState = 0;
    buzzerState = 1;
  } else {
    redState = 0;
    greenState = 1;
    buzzerState = 0;
  }

  digitalWrite(RED_LED_PIN, redState ? HIGH : LOW);
  digitalWrite(GREEN_LED_PIN, greenState ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);

  if (millis() - lastSend >= SEND_INTERVAL_MS) {
    lastSend = millis();

    // CSV protocol: DATA,soil,red,green,buzzer
    espSerial.print("DATA,");
    espSerial.print(soilValue);
    espSerial.print(",");
    espSerial.print(redState);
    espSerial.print(",");
    espSerial.print(greenState);
    espSerial.print(",");
    espSerial.println(buzzerState);

    Serial.print("Soil=");
    Serial.print(soilValue);
    Serial.print(" Red=");
    Serial.print(redState);
    Serial.print(" Green=");
    Serial.print(greenState);
    Serial.print(" Buzzer=");
    Serial.println(buzzerState);
  }
}
