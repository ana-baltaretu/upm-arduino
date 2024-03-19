/* Hello Mouse */
// My first program in Processing

void setup() {
  size(480, 320);
  smooth();
}

void draw() {
  print("Colour: ");
  if (mousePressed) {
    fill(0);
    println("Black");
  } else {
    fill(255);
    println("White");
  }
  ellipse(mouseX, mouseY, 80, 80);
}
