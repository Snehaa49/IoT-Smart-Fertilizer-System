/*
  Smart Farm Controller - ESP8266 / NodeMCU
  Connects the device to Blynk and controls:
    D1 -> water pump relay
    D2 -> nitrogen solenoid relay
    D5 -> phosphorus solenoid relay
    D7 -> potassium solenoid relay

  UNO <-> ESP8266 serial:
    UNO D3 (TX) -> ESP D6 (RX) through voltage divider
    UNO D2 (RX) <- ESP D4 (TX)
    GND         <-> GND

  Blynk datastreams:
    V0 = soil moisture display (UNO reading, or simulated value)
    V1 = pump control
    V2 = automatic mode switch/status
    V3 = nitrogen valve control
    V4 = phosphorus valve control
    V5 = potassium valve control
    V6 = red LED status
    V7 = green LED status
    V8 = buzzer status

  IMPORTANT:
  - Replace YOUR_BLYNK_AUTH_TOKEN and YOUR_HOTSPOT_PASSWORD.
  - Relay modules in this project are configured as active-LOW.
  - Test with loads disconnected before connecting pumps/solenoids.
*/

#define BLYNK_TEMPLATE_ID "TMPL30qLuNruO"
#define BLYNK_TEMPLATE_NAME "Smart Watering And NPK Fertilizer System"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "Ayush";
char pass[] = "YOUR_HOTSPOT_PASSWORD";

BlynkTimer timer;

// ESP8266 SoftwareSerial: RX, TX
// D4 receives UNO TX; D6 sends to UNO RX.
SoftwareSerial unoSerial(D4, D6);

const uint8_t PUMP_RELAY_PIN = D1;
const uint8_t N_RELAY_PIN = D2;
const uint8_t P_RELAY_PIN = D5;
const uint8_t K_RELAY_PIN = D7;

const uint8_t RELAY_ON = LOW;
const uint8_t RELAY_OFF = HIGH;

bool pumpOn = false;
bool nitrogenOn = false;
bool phosphorusOn = false;
bool potassiumOn = false;
bool automaticMode = false;

int soilMoisture = 0;
int redStatus = 0;
int greenStatus = 0;
int buzzerStatus = 0;

// Set true only when you want a changing demo value on V0.
// Set false to display the actual UNO soil sensor reading.
const bool SIMULATE_MOISTURE_FOR_DEMO = false;
const int DRY_THRESHOLD = 600; // Calibrate to your sensor.

String serialLine;

void setRelay(uint8_t pin, bool on) {
  digitalWrite(pin, on ? RELAY_ON : RELAY_OFF);
}

void publishStates() {
  Blynk.virtualWrite(V1, pumpOn);
  Blynk.virtualWrite(V2, automaticMode);
  Blynk.virtualWrite(V3, nitrogenOn);
  Blynk.virtualWrite(V4, phosphorusOn);
  Blynk.virtualWrite(V5, potassiumOn);
  Blynk.virtualWrite(V6, redStatus);
  Blynk.virtualWrite(V7, greenStatus);
  Blynk.virtualWrite(V8, buzzerStatus);
}

void readUnoSerial() {
  while (unoSerial.available()) {
    char c = (char)unoSerial.read();

    if (c == '\n') {
      serialLine.trim();

      if (serialLine.startsWith("DATA,")) {
        int values[4];
        int parsed = sscanf(serialLine.c_str(), "DATA,%d,%d,%d,%d",
                            &values[0], &values[1], &values[2], &values[3]);

        if (parsed == 4) {
          soilMoisture = values[0];
          redStatus = values[1];
          greenStatus = values[2];
          buzzerStatus = values[3];
        }
      }

      serialLine = "";
    } else if (c != '\r') {
      if (serialLine.length() < 60) serialLine += c;
      else serialLine = "";
    }
  }
}

void sendDashboardData() {
  readUnoSerial();

  int displayedMoisture = soilMoisture;
  if (SIMULATE_MOISTURE_FOR_DEMO) {
    displayedMoisture = random(300, 901);
  }

  Blynk.virtualWrite(V0, displayedMoisture);
  publishStates();

  // Simple automatic demonstration logic.
  // When enabled, low raw soil reading is treated as sufficiently moist.
  // Adjust DRY_THRESHOLD after testing your sensor.
  if (automaticMode && !SIMULATE_MOISTURE_FOR_DEMO) {
    bool soilIsDry = (soilMoisture >= DRY_THRESHOLD);
    pumpOn = soilIsDry;
    setRelay(PUMP_RELAY_PIN, pumpOn);
    Blynk.virtualWrite(V1, pumpOn);
  }
}

// Blynk button/switch handlers
BLYNK_WRITE(V1) {
  if (!automaticMode) {
    pumpOn = param.asInt();
    setRelay(PUMP_RELAY_PIN, pumpOn);
  }
}

BLYNK_WRITE(V2) {
  automaticMode = param.asInt();
  if (!automaticMode) {
    pumpOn = false;
    setRelay(PUMP_RELAY_PIN, false);
  }
  Blynk.virtualWrite(V2, automaticMode);
}

BLYNK_WRITE(V3) {
  nitrogenOn = param.asInt();
  setRelay(N_RELAY_PIN, nitrogenOn);
}

BLYNK_WRITE(V4) {
  phosphorusOn = param.asInt();
  setRelay(P_RELAY_PIN, phosphorusOn);
}

BLYNK_WRITE(V5) {
  potassiumOn = param.asInt();
  setRelay(K_RELAY_PIN, potassiumOn);
}

BLYNK_CONNECTED() {
  publishStates();
}

void setup() {
  Serial.begin(115200);
  unoSerial.begin(9600);

  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(N_RELAY_PIN, OUTPUT);
  pinMode(P_RELAY_PIN, OUTPUT);
  pinMode(K_RELAY_PIN, OUTPUT);

  // Keep all active-LOW relays OFF during startup.
  setRelay(PUMP_RELAY_PIN, false);
  setRelay(N_RELAY_PIN, false);
  setRelay(P_RELAY_PIN, false);
  setRelay(K_RELAY_PIN, false);

  randomSeed(analogRead(A0));

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendDashboardData);
}

void loop() {
  Blynk.run();
  timer.run();
  readUnoSerial();
}
