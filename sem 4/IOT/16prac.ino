#define ROAD1_GREEN A2
#define ROAD1_YELLOW 11
#define ROAD1_RED A1

#define ROAD2_GREEN 0
#define ROAD2_YELLOW 5
#define ROAD2_RED 6

#define ROAD3_GREEN 10
#define ROAD3_YELLOW 13
#define ROAD3_RED A3

#define ROAD4_GREEN 12
#define ROAD4_YELLOW 9
#define ROAD4_RED A0

void setup() {
  // Initialize all the traffic lights (RED, YELLOW, GREEN) as OUTPUT
  pinMode(ROAD1_GREEN, OUTPUT);
  pinMode(ROAD1_YELLOW, OUTPUT);
  pinMode(ROAD1_RED, OUTPUT);

  pinMode(ROAD2_GREEN, OUTPUT);
  pinMode(ROAD2_YELLOW, OUTPUT);
  pinMode(ROAD2_RED, OUTPUT);

  pinMode(ROAD3_GREEN, OUTPUT);
  pinMode(ROAD3_YELLOW, OUTPUT);
  pinMode(ROAD3_RED, OUTPUT);

  pinMode(ROAD4_GREEN, OUTPUT);
  pinMode(ROAD4_YELLOW, OUTPUT);
  pinMode(ROAD4_RED, OUTPUT);
}

void setAllLightsLow() {
  // Set all lights to LOW (Red)
  digitalWrite(ROAD1_GREEN, LOW);
  digitalWrite(ROAD1_YELLOW, LOW);
  digitalWrite(ROAD1_RED, HIGH);

  digitalWrite(ROAD2_GREEN, LOW);
  digitalWrite(ROAD2_YELLOW, LOW);
  digitalWrite(ROAD2_RED, HIGH);

  digitalWrite(ROAD3_GREEN, LOW);
  digitalWrite(ROAD3_YELLOW, LOW);
  digitalWrite(ROAD3_RED, HIGH);

  digitalWrite(ROAD4_GREEN, LOW);
  digitalWrite(ROAD4_YELLOW, LOW);
  digitalWrite(ROAD4_RED, HIGH);
}

void setGreenForRoad(int road) {
  // Reset all roads to red
  setAllLightsLow();
  
  // Set the correct green light and turn off the red light
  switch(road) {
    case 1:
      digitalWrite(ROAD1_GREEN, HIGH);
      digitalWrite(ROAD1_RED, LOW);
      break;
    case 2:
      digitalWrite(ROAD2_GREEN, HIGH);
      digitalWrite(ROAD2_RED, LOW);
      break;
    case 3:
      digitalWrite(ROAD3_GREEN, HIGH);
      digitalWrite(ROAD3_RED, LOW);
      break;
    case 4:
      digitalWrite(ROAD4_GREEN, HIGH);
      digitalWrite(ROAD4_RED, LOW);
      break;
  }
}

void setYellowForRoad(int road) {
  // Reset all roads to red
  setAllLightsLow();
  
  // Set the correct yellow light and turn off the green light
  switch(road) {
    case 1:
      digitalWrite(ROAD1_YELLOW, HIGH);
      digitalWrite(ROAD1_GREEN, LOW);
      break;
    case 2:
      digitalWrite(ROAD2_YELLOW, HIGH);
      digitalWrite(ROAD2_GREEN, LOW);
      break;
    case 3:
      digitalWrite(ROAD3_YELLOW, HIGH);
      digitalWrite(ROAD3_GREEN, LOW);
      break;
    case 4:
      digitalWrite(ROAD4_YELLOW, HIGH);
      digitalWrite(ROAD4_GREEN, LOW);
      break;
  }
}

void loop() {
  // Road 1 (North) Green, others Red
  setGreenForRoad(1);
  delay(5000);  // Green for 5 seconds
  setYellowForRoad(1);
  delay(2000);  // Yellow for 2 seconds
  
  // Road 2 (East) Green, others Red
  setGreenForRoad(2);
  delay(5000);  // Green for 5 seconds
  setYellowForRoad(2);
  delay(2000);  // Yellow for 2 seconds
  
  // Road 3 (South) Green, others Red
  setGreenForRoad(3);
  delay(5000);  // Green for 5 seconds
  setYellowForRoad(3);
  delay(2000);  // Yellow for 2 seconds
  
  // Road 4 (West) Green, others Red
  setGreenForRoad(4);
  delay(5000);  // Green for 5 seconds
  setYellowForRoad(4);
  delay(2000);  // Yellow for 2 seconds
}