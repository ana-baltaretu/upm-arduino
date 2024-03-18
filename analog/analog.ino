int LED_PIN = 3;
int POT_PIN = A7;
int VAL_POT;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  VAL_POT = analogRead(POT_PIN);
  VAL_POT = map(VAL_POT, 0, 1023, 0, 255); // Need to map from potentiometer to LED
  analogWrite(LED_PIN, VAL_POT);
  delay(20);
}