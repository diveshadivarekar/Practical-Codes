int num;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Enter a number : ");
  
  while (Serial.available() == 0) {}

  num = Serial.parseInt();

  Serial.print("Square of ");
  Serial.print(num);
  Serial.print(" is ");
  Serial.println(num*num);

  delay(500);
}