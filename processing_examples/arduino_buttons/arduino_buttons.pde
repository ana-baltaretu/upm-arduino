/**
 * Button. 
 * 
 * Click on one of the colored shapes in the 
 * center of the image to change the color of 
 * the background. 
 */
 
import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int greenLed = 13;
int redLed = 12;
int buttonPin = 2;
 
int rectX, rectY;      // Position of square button
int circleX, circleY;  // Position of circle button
int rectSize = 90;     // Diameter of rect
int circleSize = 93;   // Diameter of circle
color rectColor, circleColor, baseColor;
color rectHighlight, circleHighlight;
color currentColor;
boolean rectOver = false;
boolean circleOver = false;

/// Colors
color grey = color(100,100,100);
color blue = color(0,0,255);
color red = color(255,0,0);
color green = color(0,255,0);
color white = color(255);

int buttonVal = 0;

void setup() {
  
  //println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(greenLed, Arduino.OUTPUT);
  arduino.pinMode(redLed, Arduino.OUTPUT);
  arduino.pinMode(buttonPin, Arduino.INPUT);
  
  size(640, 360);
  rectColor = color(255);
  rectHighlight = color(51);
  circleColor = color(255);
  circleHighlight = color(204);
  baseColor = color(102);
  currentColor = baseColor;
  circleX = width/2-rectSize+rectSize + 10;
  circleY = height/2-rectSize/2;
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
  ellipseMode(CENTER);
}

void draw() {
  update(mouseX, mouseY);
  //background(currentColor);
  
  if (rectOver) {
    fill(rectColor/2+50);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectX, rectY, rectSize, rectSize);
  
  if (circleOver) {
    fill(circleColor/2+50);
  } else {
    fill(circleColor);
  }
  stroke(0);
  rect(circleX, circleY, circleSize, circleSize);
  //ellipse(circleX, circleY, circleSize, circleSize);
}

int greenWasPressed = 0, redWasPressed = 0;

void update(int x, int y) {
  buttonVal = arduino.digitalRead(buttonPin);
  
  arduino.digitalWrite(greenLed, greenWasPressed);
  arduino.digitalWrite(redLed, redWasPressed);
  //delay(1000);
  //println("Off");
  //arduino.digitalWrite(greenLed, Arduino.LOW);
  //arduino.digitalWrite(redLed, Arduino.HIGH);
  //delay(1000);
  
  if (buttonVal == 1) {
    background(blue);
  } else {
    background(grey);
  }
  
  
  if ( overCircle(circleX, circleY, circleSize, circleSize) ) {
    circleOver = true;
    rectOver = false;
  } else if ( overRect(rectX, rectY, rectSize, rectSize) ) {
    rectOver = true;
    circleOver = false;
  } else {
    circleOver = rectOver = false;
  }
}

void mousePressed() {
  println("mousepressed");
  if (circleOver == true && redWasPressed == 0) {
    circleColor = red;
    redWasPressed = 1;
  } else if (circleOver == true && redWasPressed == 1) {
    circleColor = white;
    redWasPressed = 0;
  }
  if (rectOver == true && greenWasPressed == 0) {
    rectColor = green;
    greenWasPressed = 1;
  } else if (rectOver == true && greenWasPressed == 1) {
    rectColor = white;
    greenWasPressed = 0;
  }
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

boolean overCircle(int x, int y, int width, int height) {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}
