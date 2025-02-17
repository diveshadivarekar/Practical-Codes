#define led1 9
#define led2 10
#define led3 11

#define p1 A0
#define p2 A1
#define p3 A2

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
}

void loop()
{
  int val1 = analogRead(p1); 
  int val2 = analogRead(p2);
  int val3 = analogRead(p3);
  
  val1 = map(val1, 0, 1023, 0, 255);
  val2 = map(val2, 0, 1023, 0, 255);
  val3 = map(val3, 0, 1023, 0, 255);
  
  analogWrite(led1, val1);
  analogWrite(led2, val2);
  analogWrite(led3, val3);
  delay(10);
}