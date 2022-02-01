/*  Code written by Adrien Louvrier, 04/01/2021
 *
 *  Objective : make a countdown of one minute we can trigger by pressing a button
 * Card used : Arduino Uno
 * 
 * Eletronic Circuit :
 * 
 * input : 
 * - a button connected to pin 12, 5V and grd with a 10kOhms resistor in parallel connected to grd
 * 
 * output :
 * - 4x7 segments display (a to g -> pins 2 to 8, point -> 9, digit 1 to 4 -> pins 10 to 13) with 330 Ohms resistor for each pin
 */

#define a 2 // segments pins
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define point 9

#define digit1 10 // digits pins
#define digit2 11
#define digit3 12
#define digit4 13

#define button A0

/**
 * @brief Print the time using the 4*7 segments display
 * 
 * @param timeMinute : the value of the minuts to print
 * @param timeSecond  : the value of the seconds to print
 * @param timeTenthSecond  : the value of the tenths of a second to print
 */
void printTime(int timeMinute, int timeSecond, int timeTenthSecond);

/**
 * @brief : print on the digit 1
 * 
 * @param value : the value to print on the digit 1
 */
void printDigit1(int value);

/**
 * @brief : print on the digit 2
 * 
 * @param timeSecond : the value to print on the digit 2
 */
void printDigit2(int timeSecond);

/**
 * @brief : print on the digit 3
 * 
 * @param timeSecond : the value to print on the digit 3
 */
void printDigit3(int timeSecond);

/**
 * @brief : print on the digit 4
 * 
 * @param timeMinute the value to print on the digit 4
 */
void printDigit4(int timeMinute);

/**
 * @brief : Print a value on the current digit
 * 
 * @param number : the number to print on the current digit
 */
void printValue(int number);

int const delayValue = 10000; // delay used to display digits on 7 segments displays

int timeMinute = 1; // Values for the start time
int timeSecond = 0;
int timeTenthSecond = 0;

unsigned int long timerDisplay; // timer used to display
unsigned int long timerTime = 0; // timer used to count time
unsigned int long timerbutton = 0; // timer used to consider the press on the button

boolean endValue  = 0; // Booleans used  for the countdown
boolean isDisplayOK = 0;
boolean displayDigit1 = 0;
boolean displayDigit2 = 0;
boolean displayDigit3 = 0;
boolean displayDigit4 = 0;

void setup() {
  // Put the segments inputs in output mode
  for (int i = 2; i<=13; ++i) {
    pinMode(i, OUTPUT);
  }

  digitalWrite(point, LOW);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}

void loop() {
  // Read the current state of the button
  int buttonValue = digitalRead(button);

  // If the button is pressed, start the countdown
  if (buttonValue) {
    isDisplayOK = 1;
  }

  // Countdown until reaching the final value
  if (isDisplayOK && !endValue) {

    // Update time every tenth of a second
    if (micros()-timerDisplay > 100000) {
      timerTime = micros();

      // Loop the tenths of a second to 9 when reaching 0
      if (timeTenthSecond == 0) {
        timeTenthSecond = 9;

        // Decreasing the secunds until reaching 0 
        if (timeSecond != 0) {
          --timeSecond;

        } else {
          // Decreasing minuts until reaching 0
          if (timeMinute != 0) {
            --timeMinute;
          }
          // Loop the seconds to 59 when reaching 0
          timeSecond = 59;
        }
      } else {
        // Decreasing the tenths of a second until reaching 0
        --timeTenthSecond;
      }
    }
    
    // Stop the countdown when reaching the final value
    if (timeMinute == 0 && timeSecond == 0 && timeTenthSecond == 0){
      endValue  = 1;
    }
  }

  // Print the current time in the 4*7 segments display
  printTime(timeMinute, timeSecond, timeTenthSecond);
}

void printValue(int number){
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

void printTime(int timeMinute, int timeSecond, int timeTenthSecond){
  if (!displayDigit1 && !displayDigit2 && !displayDigit3 && !displayDigit4){
    displayDigit1 = 1;
    timerDisplay = micros();
  }
  if (displayDigit1 && (micros()-timerDisplay > delayValue)){
    printDigit1(timeMinute);
    displayDigit1 = 0; 
  }

  if (!displayDigit1 && !displayDigit2 && !displayDigit3 && !displayDigit4){
    displayDigit2 = 1;
    timerDisplay = micros();
  }
  if (displayDigit2 && (micros()-timerDisplay > delayValue)){
    printDigit2((timeSecond-(timeSecond%10))/10);
    displayDigit2 = 0; 
  }

  if (!displayDigit1 && !displayDigit2 && !displayDigit3 && !displayDigit4){
    displayDigit3 = 1;
    timerDisplay = micros();
  }
  if (displayDigit3 && (micros()-timerDisplay > delayValue)){
    printDigit3(timeSecond%10);
    displayDigit3 = 0;
  }

  if (!displayDigit1 && !displayDigit2 && !displayDigit3 && !displayDigit4){
    displayDigit4 = 1;
    timerDisplay = micros();
  }
  if (displayDigit4 && (micros()-timerDisplay > delayValue)){
    printDigit4(timeTenthSecond);
    displayDigit4 = 0; 
  }
}

void printDigit1(int timeMinute){
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, LOW);
  printValue(timeMinute);
}

void printDigit2(int timeSecondDizaine){
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit1, HIGH);
  printValue(timeSecondDizaine);
}

void printDigit3(int timeSecondUnite){
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printValue(timeSecondUnite);
  digitalWrite(point, HIGH);
}

void printDigit4(int timeTenthSecond){
  digitalWrite(point, LOW);
  digitalWrite(digit4, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printValue(timeTenthSecond);
}
