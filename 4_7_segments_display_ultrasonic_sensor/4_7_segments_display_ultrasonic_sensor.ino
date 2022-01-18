// Code written by Adrien Louvrier, 29/12/2020
// Objective : print the distance measured by the ultrasonic sensor on the 7 segments display

#define a 2 // segments
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define point 9

#define digit3 10 // digits
#define digit4 11

#define trigPin 12 // Ultrasonic sensor
#define echoPin 13

// prototypes of the functions

// If distance < 100(cm), print the units digit of the distance on digit 4, else print an error ('E')
void printDigit4(int distance);

// If distance < 100(cm), print the tens digit of the distance on digit 3, else print an error ('E')
void printDigit3(int distance);

// 
void printNumber(int number);
void printError();

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  // Put the segment pins in output mode
  for (int i = 0; i<12; ++i){
    pinMode(i, OUTPUT);
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(digit4, LOW);
  digitalWrite(digit3, LOW);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measurement of the duration between emission and reception of the signal
  duration = pulseIn(echoPin, HIGH);
  // Calculation of the distance with the duration : d = v*t
  distance = duration * 0.034/2;

  // Distance display on 7 segments displays
  printDigit4(distance);
  delay(10);
  printDigit3(distance);
  delay(10);
  Serial.println(distance);
}

void printNumber(int number){
  switch (number){
     case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  }
}

void printError(){
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  
}

void printDigit4(int distance){
  // if distance > 100(cm), print an erreor ('E' on digit 4)
  if (distance > 100){
    digitalWrite(digit4, LOW);
    digitalWrite(digit3, HIGH);
    printError();
  }
  else{
    digitalWrite(digit4, LOW);
    digitalWrite(digit3, HIGH);
    if (distance < 100){
      printNumber(distance % 10);
    }
  }
}

void printDigit3(int distance){
  // if distance > 100, print nothing on digit 3
  if (distance > 100){
    digitalWrite(digit4, LOW);
    digitalWrite(digit3, HIGH);   
  }
  else{
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, HIGH);
    if (distance < 10){
      digitalWrite(digit3, HIGH);
    }
    else if (distance < 100){
      printNumber(((distance - distance%10) % 100)/10);
    }
  }
}
