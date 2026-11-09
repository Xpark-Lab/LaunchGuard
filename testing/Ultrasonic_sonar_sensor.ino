/*
  ESP32 + HC-SR04 Ultrasonic Sensor

  Wiring used by this example:
    HC-SR04 VCC  -> ESP32 VIN/5V
    HC-SR04 GND  -> ESP32 GND
    HC-SR04 TRIG -> ESP32 GPIO 5
    HC-SR04 ECHO -> ESP32 GPIO 18 through a voltage divider

  IMPORTANT:
  The HC-SR04 ECHO pin can output 5V, but ESP32 GPIO pins accept
  approximately 3.3V only. Use a voltage divider before connecting
  ECHO to the ESP32 (for example, 1k ohm from ECHO to GPIO 18 and
  2k ohm from GPIO 18 to GND).
*/

const uint8_t TRIG_PIN = 5;
const uint8_t ECHO_PIN = 18;

void setup() {
  // Start the Serial Monitor so we can see the measured distance.
  Serial.begin(115200);

  // TRIG sends the ultrasonic signal.
  pinMode(TRIG_PIN, OUTPUT);

  // ECHO receives the signal reflected by an object.
  pinMode(ECHO_PIN, INPUT);

  // Keep the trigger pin LOW before the first measurement.
  digitalWrite(TRIG_PIN, LOW);
  delay(500);
}

void loop() {
  // Make sure the trigger pulse starts from LOW.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a short 10-microsecond ultrasonic trigger pulse.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure how long the ECHO pin stays HIGH.
  // The timeout prevents the program from waiting forever.
  unsigned long echoTime = pulseIn(ECHO_PIN, HIGH, 30000);

  if (echoTime == 0) {
    // No echo was received within the timeout.
    Serial.println("No echo received - check wiring or distance.");
  } else {
    // Sound travels to the object and back, so divide by 2.
    // Speed of sound is approximately 0.0343 cm per microsecond.
    float distanceCm = (echoTime * 0.0343) / 2.0;

    Serial.print("Distance: ");
    Serial.print(distanceCm, 2);
    Serial.println(" cm");
  }

  // Wait before taking the next reading.
  delay(500);
}