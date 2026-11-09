# ESP32 Built-in LED Blink Test

This simple sketch tests whether an ESP32 board can run an Arduino program.
It turns the board's built-in LED on for one second and off for one second.

## Requirements

- ESP32 development board
- USB data cable
- Arduino IDE with the ESP32 board package installed

## Upload process

1. Open `Esp32_blink.ino` in Arduino IDE.
2. Select your ESP32 board from **Tools > Board**.
3. Connect the ESP32 with a USB data cable.
4. Select the board port from **Tools > Port**.
5. Click **Upload**.
6. If Arduino IDE asks you to press a boot button, press and hold **BOOT**
   while the upload starts, then release it.

## Test process

After uploading, the built-in LED should blink once per second. No Serial
Monitor is required for this test.

Some ESP32 boards do not have a usable built-in LED, or use a different LED
pin. In that case, connect an external LED with a 220-330 ohm resistor to a
known GPIO and replace `LED_BUILTIN` in the sketch with that GPIO number.

## Troubleshooting

- If no port appears, install the USB driver for the board and try another
  USB cable. Some cables provide power only.
- If upload fails, close other programs using the port and try the BOOT
  button again.
- If the board resets repeatedly, use a stable USB power source.
