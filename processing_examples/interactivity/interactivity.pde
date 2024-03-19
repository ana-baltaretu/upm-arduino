void setup() {
  size(640,320);
  background(100);
}
void draw() {
  rect(250, 100, 150, 150);
}
void keyPressed() {
  if (key == 'b' || key == 'B') {
    fill(0, 0, 255); /// RGB
  } else if (key == 'r') {
    fill(255, 0, 0);
  } else if (key == 'g') {
    fill(0, 255, 0);
  }
}
void mousePressed() {
  if (mouseButton == LEFT) {
    fill(0);
  } else if (mouseButton == RIGHT) {
    fill(255);
  } else {
    fill(126);
  }
}
