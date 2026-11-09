# ESP32 Water Level Sensor Test

This sketch tests a common resistive water-level sensor. It reads the sensor's
analog output and prints a raw ADC value plus an approximate percentage.

## Wiring

| Water sensor pin | ESP32 connection |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SIG or S | GPIO 34 |

Power the sensor from **3.3V** so the signal stays safe for the ESP32 ADC.
GPIO 34 is input-only and is used here only for measuring voltage.

## Upload and test process

1. Open `Water_Level_Sensor.ino` in Arduino IDE.
2. Select the correct ESP32 board and port.
3. Connect the sensor using the wiring above.
4. Upload the sketch.
5. Open **Tools > Serial Monitor**.
6. Set the baud rate to **115200**.
7. First keep the sensing strip dry and note the reading.
8. Place the sensor into water gradually and watch the reading change.

The sketch prints a new reading every 500 milliseconds:

```text
Raw value: 1234  |  Approximate level: 30%
```

## Understanding the result

The ESP32 ADC normally returns a value from 0 to 4095. More of the sensing
strip covered by water usually produces a higher value. The percentage is
only a simple comparison from 0 to 4095; it is not a calibrated tank height.
For accurate water height, measure your own dry and full values and calibrate
the program for your sensor and container.

## Safety and care

- Keep water below the sensor module's marked sensing area.
- Do not immerse the electronics or expose the USB connector to water.
- Disconnect power before changing the wiring.
- Resistive sensors can corrode when powered continuously. For a permanent
  project, power the sensor only while taking a measurement.

## Troubleshooting

- A value near zero: check VCC, GND, SIG, and the selected GPIO.
- A value that never changes: confirm the sensing strip is actually wet.
- Random values: keep wires short and share a common ground.
- If your ESP32 board does not expose GPIO 34, change
  `WATER_SENSOR_PIN` to another ADC-capable input pin.
