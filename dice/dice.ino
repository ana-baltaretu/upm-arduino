int LED_PIN_LEFT_TOP = 13;
int LED_PIN_LEFT_MID = 9;
int LED_PIN_LEFT_BOT = 3;

int LED_PIN_MID_MID = 10;

int LED_PIN_RIGHT_TOP = 6;
int LED_PIN_RIGHT_MID = 5;
int LED_PIN_RIGHT_BOT = 4;

int BUT_PIN = 2; // Global variables
boolean VAL;
boolean startRolling = false;

int POT_PIN = A7;
int VAL_POT;

int diceMap[6][7] = {
  {0, 0, 0, 1, 0, 0, 0}, // Number 1
  {1, 0, 0, 0, 0, 0, 1}, // Number 2
  {0, 0, 1, 1, 1, 0, 0}, // Number 3
  {1, 0, 1, 0, 1, 0, 1}, // Number 4
  {1, 0, 1, 1, 1, 0, 1}, // Number 5
  {1, 1, 1, 0, 1, 1, 1}  // Number 6
};

int randomNumber = random(0, 6);

void setup() {
  Serial.begin(9600);
  Serial.println(randomNumber + 1);

  randomSeed(analogRead(0));

  // LEFT SIDE
  pinMode(LED_PIN_LEFT_TOP, OUTPUT);
  pinMode(LED_PIN_LEFT_MID, OUTPUT);
  pinMode(LED_PIN_LEFT_BOT, OUTPUT);

  // MIDDLE
  pinMode(LED_PIN_MID_MID, OUTPUT);

  // RIGHT SIDE
  pinMode(LED_PIN_RIGHT_TOP, OUTPUT);
  pinMode(LED_PIN_RIGHT_MID, OUTPUT);
  pinMode(LED_PIN_RIGHT_BOT, OUTPUT);

  /// Button
  pinMode(BUT_PIN, INPUT);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN_LEFT_TOP, HIGH);
    digitalWrite(LED_PIN_LEFT_MID, HIGH);
    digitalWrite(LED_PIN_LEFT_BOT, HIGH);
    digitalWrite(LED_PIN_MID_MID, HIGH);
    digitalWrite(LED_PIN_RIGHT_TOP, HIGH);
    digitalWrite(LED_PIN_RIGHT_MID, HIGH);
    digitalWrite(LED_PIN_RIGHT_BOT, HIGH);
    delay(1000);

    digitalWrite(LED_PIN_LEFT_TOP, LOW);
    digitalWrite(LED_PIN_LEFT_MID, LOW);
    digitalWrite(LED_PIN_LEFT_BOT, LOW);
    digitalWrite(LED_PIN_MID_MID, LOW);
    digitalWrite(LED_PIN_RIGHT_TOP, LOW);
    digitalWrite(LED_PIN_RIGHT_MID, LOW);
    digitalWrite(LED_PIN_RIGHT_BOT, LOW);
    delay(1000);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  VAL = digitalRead(BUT_PIN);
  VAL_POT = analogRead(POT_PIN);
  delay(20);

  if (VAL == HIGH && startRolling == true) { 
    Serial.println("STOP");
    startRolling = false;

    digitalWrite(LED_PIN_LEFT_TOP, diceMap[randomNumber][0]);
    digitalWrite(LED_PIN_LEFT_MID, diceMap[randomNumber][1]);
    digitalWrite(LED_PIN_LEFT_BOT, diceMap[randomNumber][2]);
    digitalWrite(LED_PIN_MID_MID, diceMap[randomNumber][3]);
    digitalWrite(LED_PIN_RIGHT_TOP, diceMap[randomNumber][4]);
    digitalWrite(LED_PIN_RIGHT_MID, diceMap[randomNumber][5]);
    digitalWrite(LED_PIN_RIGHT_BOT, diceMap[randomNumber][6]);
    delay(1000);
  } else if( VAL == HIGH ) {
    Serial.println("CLICKED");
    startRolling = true; 
  } 

  if (startRolling == true) {
    digitalWrite(LED_PIN_LEFT_TOP, diceMap[randomNumber][0]);
    digitalWrite(LED_PIN_LEFT_MID, diceMap[randomNumber][1]);
    digitalWrite(LED_PIN_LEFT_BOT, diceMap[randomNumber][2]);
    digitalWrite(LED_PIN_MID_MID, diceMap[randomNumber][3]);
    digitalWrite(LED_PIN_RIGHT_TOP, diceMap[randomNumber][4]);
    digitalWrite(LED_PIN_RIGHT_MID, diceMap[randomNumber][5]);
    digitalWrite(LED_PIN_RIGHT_BOT, diceMap[randomNumber][6]);
    delay(VAL_POT);

    digitalWrite(LED_PIN_LEFT_TOP, LOW);
    digitalWrite(LED_PIN_LEFT_MID, LOW);
    digitalWrite(LED_PIN_LEFT_BOT, LOW);
    digitalWrite(LED_PIN_MID_MID, LOW);
    digitalWrite(LED_PIN_RIGHT_TOP, LOW);
    digitalWrite(LED_PIN_RIGHT_MID, LOW);
    digitalWrite(LED_PIN_RIGHT_BOT, LOW);
    delay(VAL_POT);

    randomNumber = random(0, 6);
    Serial.println(randomNumber + 1);
  }
}
