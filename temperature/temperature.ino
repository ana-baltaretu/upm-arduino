#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0; // variable to store the servo position

// Define the analog pin to which the LM35 is connected
const int lm35Pin = A7;

void setup() {
  Serial.begin(9600);
  myservo.attach(3); // attaches the servo on pin 3 to the servo object

  myservo.write(pos);
  delay(5);

  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(5); // waits 15ms to reach position
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(5); // waits 15ms to reach position
  }
}

void loop() {
  // Read the raw analog value from the LM35 sensor
  int rawValue = analogRead(lm35Pin);

  // Convert the raw value to voltage (in millivolts)
  float voltage = rawValue * (5.0 / 1023.0) * 1000.0;

  // Convert the voltage to temperature (in Celsius)
  float temperatureC = voltage / 10.0;

  // Print the temperature to the Serial Monitor
  Serial.print("RAW: ");
  Serial.println(rawValue);

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  int modifiedRange = map(temperatureC, 15, 30, 0, 180);


  // int servoTemp = map(rawValue, 0, 1023, 0, 180);
  Serial.print("servoAngle: ");
  Serial.println(modifiedRange);
  myservo.write(modifiedRange);

  delay(1000); // Wait for a second before taking another reading
}





// void loop() {
//   for (pos = 0; pos <= 180; pos += 1) {
//     myservo.write(pos);
//     delay(5); // waits 15ms to reach position
//   }
//   for (pos = 180; pos >= 0; pos -= 1) {
//     myservo.write(pos);
//     delay(5);
//   }
// }