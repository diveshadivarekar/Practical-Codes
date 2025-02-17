#define BUZZER_PIN A1

void setup() {
  pinMode(BUZZER_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int knockStatus = analogRead(BUZZER_PIN);

  Serial.println(knockStatus);

  if (knockStatus > 500) {
    playToneForOneSecond();
    delay(1000);
  }

  delay(100);
}

void playToneForOneSecond() {
  pinMode(BUZZER_PIN, OUTPUT);
  
  tone(BUZZER_PIN, 1000);
  delay(1000);
  noTone(BUZZER_PIN);
  
  pinMode(BUZZER_PIN, INPUT);
}