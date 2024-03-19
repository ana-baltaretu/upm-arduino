import processing.serial.*;

PImage photo;
Serial myPort;
int interval = 2000;  // Interval between temperature requests (in milliseconds)
int lastRequestTime = 0;

void setup() {
  size(800, 550);
  photo = loadImage("myphoto.jpeg");
  scale(0.5);
  image(photo, 0, 0);
  
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  //myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  

  
  if (millis() - lastRequestTime > interval) {
    println("Sending T");
    myPort.write("T"); // Send command to request temperature data
    lastRequestTime = millis();
  } else {
    myPort.write("N");
  }
  
    //println(myPort.available());
  
  if (myPort.available() > 0) {
    String data = myPort.readStringUntil('\n');
    //println("Data: " + data);
    if (data != null) {
      float temperatureC = Float.parseFloat(data.trim());
      println("Temperature: " + temperatureC + " °C");
      temperatureC = (max(min(temperatureC, 30), 15) - 15) / 15 * 180;
      println("Angle: " + temperatureC);
      scale(0.5);
      image(photo, 0, 0);
      scale(2);
      drawArrow(390, 380, 150, temperatureC);
    }
  }
  
  
  
  //delay(5000);
}

void drawArrow(float x, float y, float length, float angle) { /// ANGLE IS IN PI
  angle = (180 - angle) / 180 * PI;
  // Calculate the endpoint of the arrow shaft
  float xEnd = x + length * cos(angle);
  float yEnd = y - length * sin(angle);
  
  // Draw the arrow shaft
  stroke(0);
  strokeWeight(2);
  line(x, y, xEnd, yEnd);
  
  // Calculate the coordinates for the arrowhead
  float arrowSize = 60;
  float x1 = xEnd - arrowSize * cos(angle - PI / 6);
  float y1 = yEnd + arrowSize * sin(angle - PI / 6);
  float x2 = xEnd - arrowSize * cos(angle + PI / 6);
  float y2 = yEnd + arrowSize * sin(angle + PI / 6);
  
  // Draw the arrowhead
  triangle(xEnd, yEnd, x1, y1, x2, y2);
}
