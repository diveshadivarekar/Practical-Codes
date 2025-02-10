char choice;

void setup() {
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  digitalWrite(4,HIGH);
}

int speed = 500;

void loop() {
  Serial.println("Enter choice (0,1,2): ");
  
  while (Serial.available() == 0) {}

  choice = Serial.read();

  choice = tolower(choice); 

  switch(choice) {
    case '0':
      digitalWrite(4,HIGH);
      break;
    case '1':
      digitalWrite(4,LOW);
      break;
    case '2':
      for (int i = 0; i< 10; i++){
        digitalWrite(4,HIGH);
        delay(speed);
        digitalWrite(4,LOW);
        delay(speed);
      }
      break;
    default:
      Serial.println("Invalid choice!");
      break;
  }

  delay(500);
}