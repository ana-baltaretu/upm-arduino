import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int ledPin = 13;

void setup()
{
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}
void draw()
{
  println("On");
  arduino.digitalWrite(ledPin, Arduino.HIGH);
  delay(1000);
  println("Off");
  arduino.digitalWrite(ledPin, Arduino.LOW);
  delay(1000);
 
}
