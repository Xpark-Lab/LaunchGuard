# ESP32 MPU6050 Sensor Test

This example tests an MPU6050 motion sensor with an ESP32. It reads
acceleration, rotation, and the sensor's internal temperature using I2C.
The sketch uses the ESP32 Arduino `Wire` library, so no extra library
installation is required.

## Wiring

| MPU6050 pin | ESP32 pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

Use **3.3V** with an ESP32. Do not connect a bare sensor directly to 5V.
Most breakout boards already include the required I2C pull-up resistors.

## Upload and test

1. Open `MPU6050_ESP32_Test.ino` in Arduino IDE.
2. Select your ESP32 board under **Tools > Board**.
3. Select the correct ESP32 port under **Tools > Port**.
4. Upload the sketch.
5. Open **Tools > Serial Monitor**.
6. Set the baud rate to **115200**.
7. Leave the sensor still, then move or rotate it.

You should see acceleration in `g`, rotation in degrees per second, and
temperature in degrees Celsius.

## Understanding the readings

- When the sensor is still, the accelerometer usually measures about `1 g`
  on the axis pointing upward because of gravity.
- Rotating the sensor changes the gyroscope values.
- Small non-zero gyroscope values while still are normal sensor drift.
- The raw sensor values are converted using the MPU6050's default `+/-2 g`
  and `+/-250 degrees/second` ranges.

## Troubleshooting

### `MPU6050 not found`

- Check that VCC and GND are connected correctly.
- Check that SDA is GPIO 21 and SCL is GPIO 22.
- Confirm that the sensor's power LED is on, if it has one.
- The normal I2C address is `0x68`. If the AD0 pin is connected to 3V3,
  change `MPU6050_ADDRESS` in the sketch from `0x68` to `0x69`.
- Keep wires short and make sure all devices share the same GND.

### Values do not change

Make sure the sensor is firmly connected and rotate it in different
directions. A stationary sensor should still show gravity on one axis.
