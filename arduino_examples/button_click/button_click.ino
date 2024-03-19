int LED_PIN = 13;
int BUT_PIN = 2; // Global variables
boolean VAL;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  VAL = digitalRead(BUT_PIN);

  if( VAL == LOW ) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
