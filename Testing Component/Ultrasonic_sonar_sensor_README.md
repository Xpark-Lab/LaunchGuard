# ESP32 HC-SR04 Ultrasonic Sensor Test

This sketch measures the distance to an object using an HC-SR04 ultrasonic
sensor and prints the result in centimeters.

## Wiring

| HC-SR04 pin | ESP32 connection |
|---|---|
| VCC | VIN/5V |
| GND | GND |
| TRIG | GPIO 5 |
| ECHO | GPIO 18 through a voltage divider |

### Important ECHO safety

The HC-SR04 ECHO output can be 5V, while ESP32 GPIO pins are designed for
about 3.3V. Do not connect ECHO directly to the ESP32. Use a voltage divider,
for example:

- 1k ohm resistor from ECHO to GPIO 18
- 2k ohm resistor from GPIO 18 to GND

The sensor ground and ESP32 ground must be connected together.

## Upload and test process

1. Open `Ultrasonic_sonar_sensor.ino` in Arduino IDE.
2. Select the correct ESP32 board and port.
3. Connect the sensor using the wiring above.
4. Upload the sketch.
5. Open **Tools > Serial Monitor**.
6. Set the baud rate to **115200**.
7. Place a flat object in front of the sensor and move it closer or farther
   away.

The monitor should show a distance in centimeters every 500 milliseconds.
The sensor works best when the object is directly in front of both round
transducers and is reasonably flat.

## Understanding the result

The ESP32 sends a short trigger pulse. The sensor sends ultrasonic sound and
holds ECHO high while the sound travels to the object and back. The sketch
converts that time into distance and divides by two because the sound makes a
round trip.

## Troubleshooting

- `No echo received`: check VCC, GND, TRIG, ECHO, and the voltage divider.
- Unstable readings: use short wires and a larger, flat target.
- Very close readings may be unreliable; keep the object outside the sensor's
  minimum distance.
- Check that the selected pins match `TRIG_PIN` and `ECHO_PIN` in the sketch.
