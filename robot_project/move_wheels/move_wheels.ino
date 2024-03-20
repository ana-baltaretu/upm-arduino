#include <Stepper.h>

int stepsPerRevolution = 0;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper1(stepsPerRevolution, 5, 3, 4, 2);
Stepper myStepper2(stepsPerRevolution, 9, 7, 8, 6);

void setup() {
  // set the speed at 60 rpm:
  myStepper1.setSpeed(60);
  myStepper2.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  //Serial.println("clockwise");
  // drive forward
  if (Serial.available()) {
    val = Serial.read();
  }

  if (val == "F") {
    stepsPerRevolution = -500;
  } else if (val == "B") {
    stepsPerRevolution = 500;
  }

  if (stepsPerRevolution > 0){ // drive backwards
    myStepper1.step(1);
    myStepper2.step(1);
    stepsPerRevolution--;
  } else if (stepsPerRevolution < 0){ // drive forward
    myStepper1.step(-1);
    myStepper2.step(-1);
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