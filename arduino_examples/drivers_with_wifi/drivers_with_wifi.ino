#include <Stepper.h>
#include <WiFiNINA.h>

char ssid[] = "Coldspotttt";
char pass[] = "password1234";
WiFiServer server(80); // Port 80

const int speed = 300;
const int steps = 200;
int stepsPerRevolution = 100;  // change this to fit the number of steps per revolution
int rotationSteps = 0;
char val;

// initialize the stepper library on pins 8 through 11:
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper1(stepsPerRevolution, 5, 3, 4, 2);
Stepper myStepper2(stepsPerRevolution, 9, 7, 8, 6);

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
    client.println("Hello from Arduino!");

    if (stepsPerRevolution == 0 && client.available()) {
      val = client.read();
      if (val == 'F') {
        digitalWrite(13, HIGH);
        stepsPerRevolution = -steps;
      } else if (val == 'B') {
        digitalWrite(13, HIGH);
        stepsPerRevolution = steps;
      } else if (val == 'L') {
        digitalWrite(13, HIGH);
        rotationSteps = -steps;
      } else if (val == 'R') {
        digitalWrite(13, HIGH);
        rotationSteps = steps;
      } else {
        digitalWrite(13, LOW);
        stepsPerRevolution = 0;
      }
    }
  }

  if (stepsPerRevolution > 0){ // Drive backwards
    myStepper1.step(1);
    myStepper2.step(1);
    stepsPerRevolution--;
  } 
  if (stepsPerRevolution < 0){ // Drive forward
    myStepper1.step(-1);
    myStepper2.step(-1);
    stepsPerRevolution++;
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