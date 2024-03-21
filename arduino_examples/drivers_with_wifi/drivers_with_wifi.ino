#include <Stepper.h>
#include <WiFiNINA.h>

char ssid[] = "Coldspotttt";
char pass[] = "password1234";
WiFiServer server(80); // Port 80

const int speed = 150;
const int steps = 150;
int stepsPerRevolution = 100;  // change this to fit the number of steps per revolution
char val;
// for your motor

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
    // Serial.println("New client connected");
    client.println("Hello from Arduino!");

    if (stepsPerRevolution == 0 && client.available()) {
      val = client.read();
      // Serial.println(val);
      if (val == 'F') {
        // Serial.println("Setting to high");
        digitalWrite(13, HIGH);
        stepsPerRevolution = -steps;
      } else if (val == 'B') {
        digitalWrite(13, HIGH);
        stepsPerRevolution = steps;
      } else {
        // Serial.println("Setting to low");
        digitalWrite(13, LOW);
        stepsPerRevolution = 0;
      }
    }

    // client.stop();
    // Serial.println("Client disconnected");
  }


  if (stepsPerRevolution > 0){ // drive backwards
    //Serial.println(stepsPerRevolution);
    myStepper1.step(1);
    myStepper2.step(1);
    stepsPerRevolution--;
  } 
  if (stepsPerRevolution < 0){ // drive forward
    //Serial.println(stepsPerRevolution);
    myStepper1.step(-1);
    myStepper2.step(-1);
    stepsPerRevolution++;
  }

}