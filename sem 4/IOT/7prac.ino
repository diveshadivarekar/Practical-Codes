char choice;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Enter choice (r, g, y, b): ");
  
  while (Serial.available() == 0) {}

  choice = Serial.read();

  choice = tolower(choice); 

  switch(choice) {
    case 'r':
      digitalWrite(4,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(1,HIGH);
      digitalWrite(0,HIGH);
      break;
    case 'g':
      digitalWrite(4,HIGH);
      digitalWrite(2,HIGH);
      digitalWrite(1,HIGH);
      digitalWrite(0,LOW);
      break;
    case 'y':
      digitalWrite(4,HIGH);
      digitalWrite(2,HIGH);
      digitalWrite(1,LOW);
      digitalWrite(0,HIGH);
      break;
    case 'b':
      digitalWrite(4,LOW);
      digitalWrite(2,HIGH);
      digitalWrite(1,HIGH);
      digitalWrite(0,HIGH);
      break;
    default:
      Serial.println("Invalid choice! Please enter 'r', 'g', 'y', or 'b'.");
      break;
  }

  delay(500);
}