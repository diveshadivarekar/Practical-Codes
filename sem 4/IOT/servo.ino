#include <Servo.h>

Servo myServo;

int angle; 

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

int speed = 200;
void loop() {

  myServo.write(0);
  delay(speed);
  myServo.write(30);
  delay(speed);
  myServo.write(60);
  delay(speed);
  myServo.write(90);
  delay(speed);

}
