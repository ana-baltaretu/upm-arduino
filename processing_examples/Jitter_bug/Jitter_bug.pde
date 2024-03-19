JitterBug bug, bug2; // Declare object

void setup() {
  size(800, 120);
  // Create object and pass in parameters
  bug = new JitterBug(width/2 - 100, height/2, 20);
  bug2 = new JitterBug(width/2 + 100, height/2, 10);
}
void draw() {
  bug.move();
  bug.display();
  bug2.move();
  bug2.display();
}
