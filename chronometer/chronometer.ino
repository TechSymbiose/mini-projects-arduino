/* Code written by Adrien Louvrier, 31/12/2020
 * Objective : implement a chronometer which can be turn on by a buttonPin and paused 
 * by pressing this buttonPin
 * Card used : Arduin Uno
 * Electronic Circuit :
 * input :
 *  - Button connected to pin A0, 5V and grd
 * output : 
 *  - 4x7 segments display with 330 Omhs resistances (segments connected to pins 2 to 8, point -> 9, digit4 -> 10, digit1 -> 11, digit2 -> 12, digit0 -> 13)
 */

#define a 2 // 4x7 segments display
#define b 3
#define c 4
#define d 5
#define e 6
#define f 7
#define g 8
#define point 9

#define digit1 10
#define digit2 11
#define digit3 12
#define digit4 13

#define buttonPin A0

/* Values used to display points : points are represented in binary */
#define _0000 0
#define _0001 1
#define _0010 2
#define _0011 3
#define _0100 4
#define _0101 5
#define _0110 6
#define _0111 7
#define _1000 8
#define _1001 9
#define _1010 10
#define _1011 11
#define _1100 12
#define _1101 13
#define _1110 14
#define _1111 15

void displayTime(int timeMinute, int timeSecond, int timeTenthSecond);
void displayValue(int value, int points);
void displayDigit0(int value, int pointValue);
void displayDigit1(int value, int pointValue);
void displayDigit2(int value, int pointValue);
void displayDigit3(int value, int pointValue);
void displayOnDigit(int value);

int const delayValue = 10000;

unsigned int long timer;
unsigned int long timerTime = 0;
unsigned int long timerbuttonPin = 0;
int buttonPressed = 0;
int isDisplayOK = 0;
int digit1Displayed = 0;
int digit2Displayed = 0;
int digit3Displayed = 0;
int digit4Displayed = 0;

int timeMinute = 0;
int timeSecond = 0;
int timeTenthSecond = 0;

void setup() {
  for (int i = 2; i<=13; ++i){
    pinMode(i, OUTPUT);
  }

  digitalWrite(point, LOW);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}

void loop() {
  int buttonPinValue = digitalRead(buttonPin);
  if (buttonPinValue && buttonPressed){
    isDisplayOK = !isDisplayOK;
    buttonPressed = 0;
  }
  if (isDisplayOK){
    if (timerTime == 0) {
      timerTime = micros();
    }
    if (micros()-timerTime > 100000) {
      ++timeTenthSecond;
      timerTime = 0;
    }
    if (timeTenthSecond == 10){
      ++timeSecond;
      timeTenthSecond = 0;
    }
  
    if (timeSecond == 60){
      ++timeMinute;
      timeSecond = 0;
    }
  
    timeMinute = timeMinute%10;
  }

  if (!buttonPinValue && micros() - timerbuttonPin > 30000){
    buttonPressed = 1;
  }
  displayTime(timeMinute, timeSecond, timeTenthSecond);
}

void displayTime(int timeMinute, int timeSecond, int timeTenthSecond) {
  displayValue(timeMinute * 1000 + timeSecond * 10 + timeTenthSecond, _1010);
}

void displayValue(int value, int points) {
  if (!digit1Displayed && !digit2Displayed && !digit3Displayed && !digit4Displayed){
    digit1Displayed = 1;
    timer = micros();
  }
  if (digit1Displayed && (micros()-timer > delayValue)){
    displayDigit1(value/1000, (points>>3) & 1);
    digit1Displayed = 0;
  }

  if (!digit1Displayed && !digit2Displayed && !digit3Displayed && !digit4Displayed){
    digit2Displayed = 1;
    timer = micros();
  }
  if (digit2Displayed && (micros()-timer > delayValue)){
    displayDigit2((value%1000)/100, (points>>2) & 1);
    digit2Displayed = 0;
  }

  if (!digit1Displayed && !digit2Displayed && !digit3Displayed && !digit4Displayed){
    digit3Displayed = 1;
    timer = micros();
  }
  if (digit3Displayed && (micros()-timer > delayValue)){
    displayDigit3((value%100)/10, (points >> 1) & 1);
    digit3Displayed = 0;
  }

  if (!digit1Displayed && !digit2Displayed && !digit3Displayed && !digit4Displayed){
    digit4Displayed = 1;
    timer = micros();
  }
  if (digit4Displayed && (micros()-timer > delayValue)){
    displayDigit4(value%10, points & 1);
    digit4Displayed = 0; 
  }
}

void displayDigit1(int value, int pointValue){
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, LOW);
  displayOnDigit(value);
}

void displayDigit2(int value, int pointValue){
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit1, HIGH);
  displayOnDigit(value);
}

void displayDigit3(int value, int pointValue){
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  displayOnDigit(value);
}

void displayDigit4(int value, int pointValue){ 
  digitalWrite(point, pointValue);
  digitalWrite(digit4, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  displayOnDigit(value);
}

void displayOnDigit(int value){
  switch (value){
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
      digitalWrite(d, HIGH);
      digitalWrite(c, HIGH);
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
