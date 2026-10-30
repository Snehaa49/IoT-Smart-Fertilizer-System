# Connections and setup

## Arduino UNO

| Component | UNO pin |
|---|---|
| Soil moisture sensor SIG | A0 |
| Red LED (through resistor) | D8 |
| Green LED (through resistor) | D9 |
| Buzzer signal | D10 |
| SoftwareSerial RX | D2 |
| SoftwareSerial TX | D3 |
| Sensor/LED/buzzer ground | GND |

## ESP8266 NodeMCU

| Component | NodeMCU pin |
|---|---|
| Water pump relay IN | D1 |
| Nitrogen solenoid relay IN | D2 |
| Phosphorus solenoid relay IN | D5 |
| Potassium solenoid relay IN | D7 |
| SoftwareSerial RX (from UNO D3) | D6 |
| SoftwareSerial TX (to UNO D2) | D4 |
| Ground | GND |

## UNO–ESP8266 serial wiring

- UNO D3 (TX) -> voltage divider / level shifter -> ESP8266 D6 (RX).
- ESP8266 D4 (TX) -> UNO D2 (RX).
- UNO GND <-> ESP8266 GND.

**Do not connect a 5V UNO TX signal directly to an ESP8266 input.** ESP8266 GPIO is 3.3V logic.

## Relay/load wiring

The sketch expects active-LOW relay inputs. Verify the relay module's trigger behavior before connecting loads. Use a suitable external supply for the pump and solenoids. Do not draw load current from the UNO or ESP8266 pins.

## Calibration

1. Upload the UNO sketch.
2. Open Serial Monitor and observe soil sensor readings in dry and wet conditions.
3. Set `DRY_THRESHOLD` in both sketches based on those readings.
4. Test relay outputs with the pump/solenoids disconnected first.
