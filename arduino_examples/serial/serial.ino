#include <Servo.h>

Servo myservo;
String received;
void setup() {
  Serial.begin(9600);
  myservo.attach(3); // attaches the servo on pin 3 to the servo object
}

void loop() {
  Serial.flush();
  if ( Serial.available() > 0 ){
    received = Serial.readString();
    Serial.print("Moving Servo to ");
    Serial.print(received.toInt());
    Serial.println(" degress.");
    myservo.write(received.toInt());
    delay(150);
  }
}