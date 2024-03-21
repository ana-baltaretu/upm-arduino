#include <Stepper.h>
#include <WiFiNINA.h>

char ssid[] = "Coldspotttt";
char pass[] = "password1234";

int stepsPerRevolution = 100;  // change this to fit the number of steps per revolution
char val;
WiFiServer server(80); // Port 80
// for your motor

// initialize the stepper library on pins 8 through 11:
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper1(stepsPerRevolution, 5, 3, 4, 2);
Stepper myStepper2(stepsPerRevolution, 9, 7, 8, 6);

void setup() {
  // set the speed at 60 rpm:
  myStepper1.setSpeed(80);
  myStepper2.setSpeed(80);
  // initialize the serial port:
  //Serial.begin(9600);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
}

void loop() {
  WiFiClient client = server.available();
  // step one revolution  in one direction:
  //Serial.println("clockwise");
  // drive forward
  if (client){
    if (stepsPerRevolution == 0){
      //stepsPerRevolution = 50;
      //timeSinceLastCheck = timeSinceLastCheck - 500;
      //Serial.println("time " + timeSinceLastCheck);
    
      /*if (Serial.available()) {
        val = Serial.read();
        Serial.println(val);
      }*/
      //val = 'F';
      if (client.available()) {
        val = client.read();
      }
      client.stop();

      if (val == 'F') {
        stepsPerRevolution = -500;
        //Serial.println("Forward");
      } else if (val == 'B') {
        stepsPerRevolution = 500;
        //Serial.println("Backward");
      } else if (val == 'H') {
        myStepper1.setSpeed(200);
        myStepper2.setSpeed(200);
      } /*else if (val == 'L') {
        myStepper1.setSpeed(20);
        myStepper2.setSpeed(20);
      }*/
    } 
  }
    //delay(10);


  if (stepsPerRevolution > 0){ // drive backwards
    //Serial.println(stepsPerRevolution);
    myStepper1.step(2);
    myStepper2.step(2);
    stepsPerRevolution--;
  } 
  if (stepsPerRevolution < 0){ // drive forward
    //Serial.println(stepsPerRevolution);
    myStepper1.step(-2);
    myStepper2.step(-2);
    stepsPerRevolution++;
  }
  
  //for (int i = 0; i < stepsPerRevolution; i++) {
  //  myStepper1.step(1);
  // myStepper2.step(1);
  //}
  
  //delay(500);

  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //for (int i = 0; i < stepsPerRevolution; i++) {
  //  myStepper1.step(-1);
  //  myStepper2.step(-1);
  //}
  
  //delay(500);
}