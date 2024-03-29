import processing.serial.*;

PImage photo;
Serial myPort;
int interval = 2000;  // Interval between temperature requests (in milliseconds)
int lastRequestTime = 0;


int rectX, rectY;      // Position of square button
int circleX, circleY;  // Position of circle button
int butX, butY;
int rectSizeW = 90;     // Diameter of rect
int rectSizeH = 90;
int butSizeW = 90;
int butSizeH = 90;
color rectColor, circleColor, baseColor, butColor;
color rectHighlight, circleHighlight, butHighlight;
color currentColor;
boolean rectOver = false;
boolean circleOver = false;
boolean butOver = false;

/// Colors
color grey = color(100,100,100);
color blue = color(0,0,255);
color red = color(255,0,0);
color green = color(0,255,0);
color white = color(255);

int buttonVal = 0;

void setup() {
  size(800, 550);
  
  println("Ola");
  
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[2], 9600);
  
  rectColor = color(0, 255, 0);
  rectHighlight = color(51);
  circleColor = color(255, 0, 0);
  circleHighlight = color(204);
  butColor = color(0, 0, 255);
  butHighlight = color(150);
  baseColor = color(102);
  currentColor = baseColor;
  circleX = width/2-rectSizeW+rectSizeW + 10;
  circleY = height/2-rectSizeH/2;
  rectX = width/2-rectSizeW-10;
  rectY = height/2-rectSizeH/2;
  
  
}

void draw() {
  update(mouseX, mouseY);
  if (rectOver) {
    fill(rectColor/2+50);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectX, rectY, rectSizeW, rectSizeH);
  
  if (circleOver) {
    fill(circleColor/2+50);
  } else {
    fill(circleColor);
  }
  stroke(0);
  rect(circleX, circleY, rectSizeW, rectSizeH);
  
  if (butOver) {
    fill(butColor/2+50);
  } else {
    fill(butColor);
  }
  stroke(0);
  rect(butX, butY, butSizeW, butSizeH);
    
  if (myPort.available() > 0) {
    String data = myPort.readStringUntil('\n');
    println(data);
  //  if (data != null) {
  //    float temperatureC = Float.parseFloat(data.trim());
  //    println("Temperature: " + temperatureC + " °C");
  //    temperatureC = (max(min(temperatureC, 30), 15) - 15) / 15 * 180;
  //    println("Angle: " + temperatureC);
  //  }
  }
  
}

void update(int x, int y) {
  if ( overCircle(circleX, circleY, rectSizeW, rectSizeH) ) {
    circleOver = true;
    rectOver = false;
    butOver = false;
  } else if ( overRect(rectX, rectY, rectSizeW, rectSizeH) ) {
    rectOver = true;
    circleOver = false;
    butOver = false;
  } else if ( overBut(butX, butY, butSizeW, butSizeH) ) {
    butOver = true;
    circleOver = false;
    rectOver = false;
  } else {
    circleOver = rectOver = butOver = false;
  }
  
  /*int VAL_BUT = btnToggle.getState();
  
  if (VAL_BUT == 1) {
    //println("Forward");
    myPort.write("H"); 
  } else {
    myPort.write("L");
  }*/
}

void mousePressed() {
  print("mousepressed: ");
  //if (millis() - lastRequestTime > interval) {
  //  println("Sending T");
  //  lastRequestTime = millis();
  //} else {
  //}
  if (rectOver == true) {
    println("Forward");
    myPort.write("F"); 
  } else  if (circleOver == true) {
    println("Backward");
    myPort.write("B");
  } else if (butOver == true) {
    println("Speed higher");
    myPort.write("H");
  }
  myPort.write("S"); /// STOP
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

boolean overBut(int x, int y, int width, int height) {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}
