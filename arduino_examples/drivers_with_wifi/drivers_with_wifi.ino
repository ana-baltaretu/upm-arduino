#include <Stepper.h>
#include <WiFiNINA.h>

char ssid[] = "Coldspotttt";
char pass[] = "password1234";
WiFiServer server(80); // Port 80 (same as in Python)

const int speed = 300;
const int steps = 200;
int stepsPerCommand = 100;  // starts moving a bit at start, 
// counter of how much movement it still has to do based on received commands
int rotationSteps = 0;
char val;

// initialize the stepper library on pins 8 through 11:
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper1(stepsPerCommand, 5, 3, 4, 2);
Stepper myStepper2(stepsPerCommand, 9, 7, 8, 6);

void setup() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // set the speed at 60 rpm:
  myStepper1.setSpeed(speed);
  myStepper2.setSpeed(speed);

  // initialize the serial port:
  Serial.begin(9600);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    if (stepsPerCommand == 0 && client.available()) {
      val = client.read(); // Read input commands and process them
      if (val == 'F') {
        digitalWrite(13, HIGH);
        stepsPerCommand = -steps;
      } else if (val == 'B') {
        digitalWrite(13, HIGH);
        stepsPerCommand = steps;
      } else if (val == 'L') {
        digitalWrite(13, HIGH);
        rotationSteps = -steps;
      } else if (val == 'R') {
        digitalWrite(13, HIGH);
        rotationSteps = steps;
      } else { /// If nothing matches, STOP
        digitalWrite(13, LOW);
        stepsPerCommand = 0;
      }
    }
  }

  if (stepsPerCommand > 0){ // Drive backwards
    myStepper1.step(1);
    myStepper2.step(1);
    stepsPerCommand--;
  } 
  if (stepsPerCommand < 0){ // Drive forward
    myStepper1.step(-1);
    myStepper2.step(-1);
    stepsPerCommand++;
  }
  if (rotationSteps < 0) { /// Go Left
    myStepper1.step(1);
    myStepper2.step(-1);
    rotationSteps++;
  }
  if (rotationSteps > 0) { /// Go Right
    myStepper1.step(-1);
    myStepper2.step(1);
    rotationSteps--;
  }

}