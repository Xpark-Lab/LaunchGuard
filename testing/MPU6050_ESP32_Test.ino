/*
  ESP32 + MPU6050 Sensor Test

  This example reads:
    - Accelerometer: X, Y, and Z movement in g
    - Gyroscope: X, Y, and Z rotation in degrees per second
    - Temperature inside the MPU6050 in degrees Celsius

  Wiring for a common MPU6050 breakout board:
    MPU6050 VCC -> ESP32 3V3
    MPU6050 GND -> ESP32 GND
    MPU6050 SDA -> ESP32 GPIO 21
    MPU6050 SCL -> ESP32 GPIO 22

  The sensor normally uses I2C address 0x68. If its AD0 pin is HIGH,
  change MPU6050_ADDRESS to 0x69 below.
*/

#include <Wire.h>

const uint8_t MPU6050_ADDRESS = 0x68;
const uint8_t MPU6050_WHO_AM_I = 0x75;
const uint8_t MPU6050_PWR_MGMT_1 = 0x6B;
const uint8_t MPU6050_ACCEL_XOUT_H = 0x3B;

// These variables store the sensor readings.
int16_t accelerationX;
int16_t accelerationY;
int16_t accelerationZ;
int16_t temperatureRaw;
int16_t rotationX;
int16_t rotationY;
int16_t rotationZ;

// Write one byte to an MPU6050 register.
void writeRegister(uint8_t registerAddress, uint8_t value) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(registerAddress);
  Wire.write(value);
  Wire.endTransmission();
}

// Read several bytes starting at an MPU6050 register.
bool readRegisters(uint8_t registerAddress, uint8_t* buffer, uint8_t count) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(registerAddress);

  if (Wire.endTransmission(false) != 0) {
    return false;
  }

  uint8_t received = Wire.requestFrom(MPU6050_ADDRESS, count, true);
  if (received != count) {
    return false;
  }

  for (uint8_t index = 0; index < count; index++) {
    buffer[index] = Wire.read();
  }

  return true;
}

// Read the MPU6050 identification register to check the connection.
bool sensorIsConnected() {
  uint8_t whoAmI = 0;
  if (!readRegisters(MPU6050_WHO_AM_I, &whoAmI, 1)) {
    return false;
  }

  // A normal MPU6050 returns 0x68. Some compatible boards return 0x69.
  return whoAmI == 0x68 || whoAmI == 0x69;
}

// Convert two bytes into one signed 16-bit sensor value.
int16_t combineBytes(uint8_t highByte, uint8_t lowByte) {
  return (int16_t)((highByte << 8) | lowByte);
}

// Read all six accelerometer, temperature, and gyroscope values.
bool readSensorData() {
  uint8_t data[14];

  if (!readRegisters(MPU6050_ACCEL_XOUT_H, data, sizeof(data))) {
    return false;
  }

  accelerationX = combineBytes(data[0], data[1]);
  accelerationY = combineBytes(data[2], data[3]);
  accelerationZ = combineBytes(data[4], data[5]);
  temperatureRaw = combineBytes(data[6], data[7]);
  rotationX = combineBytes(data[8], data[9]);
  rotationY = combineBytes(data[10], data[11]);
  rotationZ = combineBytes(data[12], data[13]);

  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start I2C using the ESP32 default pins: SDA = GPIO 21, SCL = GPIO 22.
  Wire.begin();

  // Wake the MPU6050. It starts in sleep mode after power-up.
  writeRegister(MPU6050_PWR_MGMT_1, 0x00);
  delay(100);

  if (!sensorIsConnected()) {
    Serial.println("MPU6050 not found.");
    Serial.println("Check VCC, GND, SDA, SCL, and the I2C address.");
    Serial.println("If AD0 is HIGH, change MPU6050_ADDRESS to 0x69.");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("MPU6050 connected successfully.");
  Serial.println("Keep the sensor still, then move it to test the readings.");
}

void loop() {
  if (!readSensorData()) {
    Serial.println("Could not read sensor data. Check the wiring.");
    delay(1000);
    return;
  }

  // Default ranges are +/-2g and +/-250 degrees/second.
  float accelerationXInG = accelerationX / 16384.0;
  float accelerationYInG = accelerationY / 16384.0;
  float accelerationZInG = accelerationZ / 16384.0;
  float rotationXInDegrees = rotationX / 131.0;
  float rotationYInDegrees = rotationY / 131.0;
  float rotationZInDegrees = rotationZ / 131.0;

  // MPU6050 temperature formula from the datasheet.
  float temperatureCelsius = (temperatureRaw / 340.0) + 36.53;

  Serial.print("Accelerometer (g): X=");
  Serial.print(accelerationXInG, 2);
  Serial.print(" Y=");
  Serial.print(accelerationYInG, 2);
  Serial.print(" Z=");
  Serial.print(accelerationZInG, 2);

  Serial.print(" | Gyroscope (deg/s): X=");
  Serial.print(rotationXInDegrees, 2);
  Serial.print(" Y=");
  Serial.print(rotationYInDegrees, 2);
  Serial.print(" Z=");
  Serial.print(rotationZInDegrees, 2);

  Serial.print(" | Temperature: ");
  Serial.print(temperatureCelsius, 2);
  Serial.println(" C");

  delay(500);
}
