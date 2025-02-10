const int speed = 200;
int inp;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  Serial.println("enter pattern number (1,2,3,4,5) = ");
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("enter pattern number (1,2,3,4,5) = ");
    inp = Serial.parseInt();
    switch (inp) {
      case 1:
        down_to_up();
        down_to_up();
        down_to_up();
        break;
      case 2:
        up_to_down();
        up_to_down();
        up_to_down();
        break;
      case 3:
        design_divesh();
        design_divesh();
        design_divesh();
        break;
      case 4:
        design_pratik();
        design_pratik();
        design_pratik();
        break;
      case 5:
        design_random();
        design_random();
        design_random();
        break;
    }
  }
}
void design_divesh() {
  digitalWrite(4, HIGH);
  digitalWrite(8, HIGH);
  delay(speed);
  digitalWrite(4, LOW);
  digitalWrite(8, LOW);
  delay(speed);
  digitalWrite(2, HIGH);
  digitalWrite(7, HIGH);
  delay(speed);
  digitalWrite(2, LOW);
  digitalWrite(7, LOW);
  delay(speed);
}
void design_pratik() {
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  delay(speed);
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  delay(speed);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  delay(speed);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  delay(speed);
}
void design_random() {
  digitalWrite(4, HIGH);
  delay(speed);
  digitalWrite(2, HIGH);
  delay(speed);
  digitalWrite(4, LOW);
  delay(speed);
  digitalWrite(2, LOW);
  delay(speed);
  digitalWrite(8, HIGH);
  delay(speed);
  digitalWrite(7, HIGH);
  delay(speed);
  digitalWrite(8, LOW);
  delay(speed);
  digitalWrite(7, LOW);
  delay(speed);
}
void up_to_down() {
  digitalWrite(4, HIGH);
  delay(speed);
  digitalWrite(2, HIGH);
  delay(speed);
  digitalWrite(8, HIGH);
  delay(speed);
  digitalWrite(7, HIGH);
  delay(speed);
  digitalWrite(4, LOW);
  delay(speed);
  digitalWrite(2, LOW);
  delay(speed);
  digitalWrite(8, LOW);
  delay(speed);
  digitalWrite(7, LOW);
  delay(speed);
}
void down_to_up() {
  digitalWrite(7, HIGH);
  delay(speed);
  digitalWrite(8, HIGH);
  delay(speed);
  digitalWrite(2, HIGH);
  delay(speed);
  digitalWrite(4, HIGH);
  delay(speed);
  digitalWrite(7, LOW);
  delay(speed);
  digitalWrite(8, LOW);
  delay(speed);
  digitalWrite(2, LOW);
  delay(speed);
  digitalWrite(4, LOW);
  delay(speed);
}
