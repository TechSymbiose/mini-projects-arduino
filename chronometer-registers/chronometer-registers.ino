/* Code written by Adrien Louvrier, 31/12/2020
 * Objective : implement a chronometer which can be turn on by a buttonPin and paused 
 * by pressing this buttonPin
 * Card used : Arduin Uno
 * Electronic Circuit :
 * input :
 *  - Button connected to pin A0, 5V and grd
 * output : 
 *  - 4x7 segments display with 330 Omhs resistor (segments connected to pins 2 to 8, 
 * point -> pin 9, digit4 -> pin 10, digit1 -> pin 11, digit2 -> pin 12, digit0 -> pin 13)
 */

#define PIN_0 B00000001
#define PIN_1 B00000010
#define PIN_2 B00000100
#define PIN_3 B00001000
#define PIN_4 B00010000
#define PIN_5 B00100000
#define PIN_6 B01000000
#define PIN_7 B10000000

#define PIN_8 B11000001
#define PIN_9 B11000010
#define PIN_10 B11000100
#define PIN_11 B11001000
#define PIN_12 B11010000
#define PIN_13 B11100000

#define INPUT_MODE 0
#define OUTPUT_MODE 1

volatile uint8_t *REGISTER_0 = &DDRC;
volatile uint8_t *REGISTER_1 = &DDRC;
volatile uint8_t *REGISTER_2 = &DDRC;
volatile uint8_t *REGISTER_3 = &DDRC;
volatile uint8_t *REGISTER_4 = &DDRC;
volatile uint8_t *REGISTER_5 = &DDRC;
volatile uint8_t *REGISTER_6 = &DDRC;
volatile uint8_t *REGISTER_7 = &DDRC;

volatile uint8_t *REGISTER_8 = &DDRB;
volatile uint8_t *REGISTER_9 = &DDRB;
volatile uint8_t *REGISTER_10 = &DDRB;
volatile uint8_t *REGISTER_11 = &DDRB;
volatile uint8_t *REGISTER_12 = &DDRB;
volatile uint8_t *REGISTER_13 = &DDRB;

volatile uint8_t *PORT_0 = &PORTC;
volatile uint8_t *PORT_1 = &PORTC;
volatile uint8_t *PORT_2 = &DDRC;
volatile uint8_t *PORT_3 = &PORTC;
volatile uint8_t *PORT_4 = &PORTC;
volatile uint8_t *PORT_5 = &PORTC;
volatile uint8_t *PORT_6 = &PORTC;
volatile uint8_t *PORT_7 = &PORTC;

volatile uint8_t *PORT_8 = &PORTB;
volatile uint8_t *PORT_9 = &PORTB;
volatile uint8_t *PORT_10 = &PORTB;
volatile uint8_t *PORT_11 = &PORTB;
volatile uint8_t *PORT_12 = &PORTB;
volatile uint8_t *PORT_13 = &PORTB;

#define a PIN_2
volatile uint8_t *aRegister = REGISTER_2;
volatile uint8_t *aPort = PORT_2;
#define b PIN_3
volatile uint8_t *bRegister = REGISTER_3;
volatile uint8_t *bPort = PORT_3;
#define c PIN_4
volatile uint8_t *cRegister = REGISTER_4;
volatile uint8_t *cPort = PORT_4;
#define d PIN_5
volatile uint8_t *dRegister = REGISTER_5;
volatile uint8_t *dPort = PORT_5;
#define e PIN_6
volatile uint8_t *eRegister = REGISTER_6;
volatile uint8_t *ePort = PORT_6;
#define f PIN_7
volatile uint8_t *fRegister = REGISTER_7;
volatile uint8_t *fPort = PORT_7;
#define g PIN_8
volatile uint8_t *gRegister = REGISTER_8;
volatile uint8_t *gPort = PORT_8;
#define point PIN_9
volatile uint8_t *pointRegister = REGISTER_9;
volatile uint8_t *pointPort = PORT_9;

#define digit1 PIN_10
volatile uint8_t *digit1Register = REGISTER_10;
volatile uint8_t *digit1Port = PORT_10;
#define digit2 PIN_11
volatile uint8_t *digit2Register = REGISTER_11;
volatile uint8_t *digit2Port = PORT_11;
#define digit3 PIN_12
volatile uint8_t *digit3Register = REGISTER_12;
volatile uint8_t *digit3Port = PORT_12;
#define digit4 PIN_13
volatile uint8_t *digit4Register = REGISTER_13;
volatile uint8_t *digit4Port = PORT_13;


/*
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
*/
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

void setPin(volatile uint8_t *reg, int pin, int mode);
void writePin(volatile uint8_t *port, int pin, int state);

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
  setPin(aRegister, a, OUTPUT_MODE);
  setPin(bRegister, b, OUTPUT_MODE);
  setPin(cRegister, c, OUTPUT_MODE);
  setPin(dRegister, d, OUTPUT_MODE);
  setPin(eRegister, e, OUTPUT_MODE);
  setPin(fRegister, f, OUTPUT_MODE);
  setPin(gRegister, g, OUTPUT_MODE);
  setPin(pointRegister, point, OUTPUT_MODE);

  setPin(digit1Register, digit1, OUTPUT_MODE);
  setPin(digit2Register, digit2, OUTPUT_MODE);
  setPin(digit3Register, digit3, OUTPUT_MODE);
  setPin(digit4Register, digit4, OUTPUT_MODE);
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
  /*
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, LOW);
  */
  writePin(pointPort, point, pointValue);
  writePin(digit4Port, digit4, HIGH);
  writePin(digit3Port, digit3, HIGH);
  writePin(digit2Port, digit2, HIGH);
  writePin(digit1Port, digit1, LOW);
  
  displayOnDigit(value);
}

void displayDigit2(int value, int pointValue){
  /*
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit1, HIGH);
  */

  writePin(pointPort, point, pointValue);
  writePin(digit4Port, digit4, HIGH);
  writePin(digit3Port, digit3, HIGH);
  writePin(digit2Port, digit2, LOW);
  writePin(digit1Port, digit1, HIGH);
  displayOnDigit(value);
}

void displayDigit3(int value, int pointValue){
  /*
  digitalWrite(point, pointValue);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  */

  writePin(pointPort, point, pointValue);
  writePin(digit4Port, digit4, HIGH);
  writePin(digit3Port, digit3, LOW);
  writePin(digit2Port, digit2, HIGH);
  writePin(digit1Port, digit1, HIGH);
  displayOnDigit(value);
}

void displayDigit4(int value, int pointValue){ 
  /*
  digitalWrite(point, pointValue);
  digitalWrite(digit4, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  */

  writePin(pointPort, point, pointValue);
  writePin(digit4Port, digit4, LOW);
  writePin(digit3Port, digit3, HIGH);
  writePin(digit2Port, digit2, HIGH);
  writePin(digit1Port, digit1, HIGH);
  displayOnDigit(value);
}

void displayOnDigit(int value){
  switch (value){
     case 0:
     /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, HIGH);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, LOW);
      break;
    case 1:
    /*
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      */
      writePin(aPort, a, LOW);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, LOW);
      writePin(ePort, e, LOW);
      writePin(fPort, f, LOW);
      writePin(gPort, g, LOW);
      break;
    case 2:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, LOW);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, HIGH);
      writePin(fPort, f, LOW);
      writePin(gPort, g, HIGH);
      break;
    case 3:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, LOW);
      writePin(fPort, f, LOW);
      writePin(gPort, g, HIGH);
      break;
    case 4:
    /*
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, LOW);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, LOW);
      writePin(ePort, e, LOW);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, HIGH);
      break;
    case 5:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, LOW);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, LOW);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, HIGH);
      break;
    case 6:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, LOW);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, HIGH);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, HIGH);
      break;
    case 7:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, LOW);
      writePin(ePort, e, LOW);
      writePin(fPort, f, LOW);
      writePin(gPort, g, LOW);
      break;
    case 8:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, HIGH);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, HIGH);
      break;
    case 9:
    /*
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      */
      writePin(aPort, a, HIGH);
      writePin(bPort, b, HIGH);
      writePin(cPort, c, HIGH);
      writePin(dPort, d, HIGH);
      writePin(ePort, e, LOW);
      writePin(fPort, f, HIGH);
      writePin(gPort, g, HIGH);
      break;
  }
}

void setPin(volatile uint8_t *reg, int pin, int mode) {
  if (mode == INPUT_MODE) {
    (*reg) = (*reg) & (pin ^ B11111111);
  }
  else {
    (*reg) = (*reg) | pin;
  }
}

void writePin(volatile uint8_t *port, int pin, int state) {
  if (state == LOW) {
    (*port) = (*port) & (pin ^ B11111111);
  }
  else {
    (*port) = (*port) | pin;
  }
}
