#define led1 5
#define led2 6
#define led3 3

#define p1 A0
#define p2 A2
#define p3 A3

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);

  Serial.begin(9600);
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

  Serial.print("Potentiometer 1: ");
  Serial.print(val1);
  Serial.print(" | Potentiometer 2: ");
  Serial.print(val2);
  Serial.print(" | Potentiometer 3: ");
  Serial.println(val3);
  
  delay(100);
}