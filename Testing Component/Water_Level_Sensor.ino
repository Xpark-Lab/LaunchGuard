/*
  ESP32 + Water Level Sensor Test

  This common water-level sensor gives an ANALOG voltage. The voltage
  increases when more of the sensor is covered by water.

  Wiring:
    Sensor VCC -> ESP32 3V3
    Sensor GND -> ESP32 GND
    Sensor SIG/S -> ESP32 GPIO 34

  Use 3.3V to power the sensor so its output never exceeds the
  ESP32 ADC input voltage. GPIO 34 is input-only, which is suitable
  for reading an analog sensor.

  Important:
    - Do not put the sensor module in water above its marked sensing area.
    - Do not use this reading as a calibrated water height in centimeters.
      The value depends on the sensor, water quality, and tank shape.
*/

// GPIO 34 is an ADC (analog input) pin on a classic ESP32.
const uint8_t WATER_SENSOR_PIN = 34;

void setup() {
  // Start the Serial Monitor at 115200 baud.
  Serial.begin(115200);

  // Configure the pin as an input.
  pinMode(WATER_SENSOR_PIN, INPUT);

  // On the ESP32, analogRead() normally returns a value from 0 to 4095.
  analogReadResolution(12);

  Serial.println("Water level sensor test started.");
  Serial.println("Place the sensor in water and watch the value change.");
}

void loop() {
  // Read the sensor's analog voltage.
  int sensorValue = analogRead(WATER_SENSOR_PIN);

  // Convert the 0-4095 reading into an easy-to-read percentage.
  int levelPercent = map(sensorValue, 0, 4095, 0, 100);
  levelPercent = constrain(levelPercent, 0, 100);

  Serial.print("Raw value: ");
  Serial.print(sensorValue);
  Serial.print("  |  Approximate level: ");
  Serial.print(levelPercent);
  Serial.println("%");

  // Take a new reading twice every second.
  delay(500);
}