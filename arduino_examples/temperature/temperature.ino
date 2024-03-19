#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0; // variable to store the servo position

// Define the analog pin to which the LM35 is connected
const int lm35Pin = A4;
char val; // data from serial

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  delay(5);
  digitalWrite(13, LOW);
}

void loop() {

  if (Serial.available()) {
    val = Serial.read();
    digitalWrite(13, HIGH);
  }

  if (val == 'T') {

    // Read the raw analog value from the LM35 sensor
    int rawValue = analogRead(lm35Pin);

    // Convert the raw value to voltage (in millivolts)
    float voltage = rawValue * (5.0 / 1023.0) * 1000.0;

    // Convert the voltage to temperature (in Celsius)
    float temperatureC = voltage / 10.0;
    Serial.println(temperatureC);
    int modifiedRange = map(temperatureC, 15, 30, 0, 180);
  }
  delay(20);
}

