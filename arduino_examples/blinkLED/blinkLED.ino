void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  /// MAKE SURE that it's connected to ground
  digitalWrite(13, HIGH); /// 13 == D13, LED_BUILTIN = the led on the arduino
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
