int counter;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  Serial.println("Enter Counter:");
  
  while (Serial.available() == 0) {
  }
  
  counter = Serial.parseInt();
  
  if (counter < 100) {
    digitalWrite(4, LOW);
    digitalWrite(2, HIGH);
    digitalWrite(1, HIGH);
  }
  else if (counter >= 101 && counter <= 200) {
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
  }
  else if (counter > 200) {
    // Counter is greater than 200, turn on red LED
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(1, LOW);
  }
  
  delay(1000);  // Wait for a second before asking for input again
}