#include <math.h>

int num;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Choose an operation:");
  Serial.println("1. Square");
  Serial.println("2. Cube");
  Serial.println("3. Square Root");
  Serial.println("4. Cube Root");
  Serial.println("Enter your choice (1-4):");

  while (Serial.available() == 0) {}
  int choice = Serial.parseInt();

  Serial.println("Enter a number:");
  while (Serial.available() == 0) {}
  num = Serial.parseInt();

  switch (choice) {
    case 1:
      Serial.print("Square of ");
      Serial.print(num);
      Serial.print(" is ");
      Serial.println(num * num);
      break;
      
    case 2:
      Serial.print("Cube of ");
      Serial.print(num);
      Serial.print(" is ");
      Serial.println(num * num * num);
      break;
      
    case 3:
      Serial.print("Square root of ");
      Serial.print(num);
      Serial.print(" is ");
      Serial.println(sqrt(num));
      break;
      
    case 4:
      Serial.print("Cube root of ");
      Serial.print(num);
      Serial.print(" is ");
      Serial.println(cbrt(num));
      break;
      
    default:
      Serial.println("Invalid choice. Please select between 1 and 4.");
      break;
  }

  delay(500);
}
