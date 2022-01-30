// Code written by Adrien Louvrier, 29/12/2020
// Objective : print the distance measured by the ultrasonic sensor and print the value on the 7 segments display

/* Code written by Adrien Louvrier, 29/12/2020
 * Objective : print the distance measured by the ultrasonic sensor and print the value on the 7 segments display
 * Card used : Arduino Uno
 * 
 * Electronic Circuit :
 * input :
 * - An ultrasonic sensor (trig pin -> pin 12, echo pin -> pin 13)
 * 
 * output :
 * - 4*7 segments display (segments pins connected to pins 2 to 9, digit3 pin -> pin 10, digit4 pin -> pin 11)
 */

#define a 2 // segments display pins
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define point 9

#define digit3 10 // digits pins
#define digit4 11

#define trigPin 12 // Ultrasonic sensor pins
#define echoPin 13

// prototypes of the functions

/* Objective : if distance < 100(cm), print the units digit of the distance on digit 4, else print an error ('E')
 * input : unit digit of the distance
 * output : none
 */
void printDigit4(int distance);

/* Objective : If distance < 100(cm), print the tens digit of the distance on digit 3, else print an error ('E')
 * input : tens digit of the distance
 * output : none
 */
void printDigit3(int distance);

/* Objective : Display a number on the current digit
 * input : the number to print
 * output : none
 */
void printNumber(int number);

/* Objective : print an error on the current digit
 * input : none
 * output : none
 */
void printError();

long duration; // Duration between emitting and receiving
int distance;

void setup() {
  // Setup the segment pins in output mode
  for (int i = 0; i<12; ++i){
    pinMode(i, OUTPUT);
  }

  pinMode(trigPin, OUTPUT); // Setup the ultrasonic sensor pins
  pinMode(echoPin, INPUT);

  digitalWrite(digit4, LOW); // Init the digits outputs
  digitalWrite(digit3, LOW);
}

void loop() {
  // Measure the duration between emitting and receiving
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2; // Calculation of the distance using the formula d=v*t

  // Distance display on 7 segments displays
  printDigit4(distance);
  delay(10);
  printDigit3(distance);
  delay(10);
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
