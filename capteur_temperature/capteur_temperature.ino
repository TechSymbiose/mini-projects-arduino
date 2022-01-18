/* Code written by Adrien Louvrier, 06/01/2021
 *  
 * Objective : display the tempereture measure on a 4x7 segments display
 * Card used : Arduino Mega 2560
 * 
 * Electronic circuit
 * input : 
 * - DHT11 temperature sensor (DHTPIN -> 53, Vcc -> 5V, grd -> grd)
 * output : 
 * - 4x7 segments display (a -> 45, b -> 43, c -> 41, d -> 39, e > 37, f -> 35, 
 *  g -> 33, point -> 32, digit1 -> 29, digit2 -> 27, digit3 -> 25, digit4 -> 23)
 */

// /!\ DOESN'T WORK /!\

#include <DHT.h>
#include <DHT_U.h>

#define a 45 // 7 segments displays
#define b 43
#define c 41
#define d 39
#define e 37
#define f 35
#define g 33
#define point 32
#define digit1 29
#define digit2 27
#define digit3 25
#define digit4 23

#define DHTPIN 53 // Temperature sensor
#define DHTTYPE DHT11

// prototypes of the functions
void printTemperature(int temperature);
void printDigit3(int tempsSeconde);
void printDigit4(int tempsMinute);
void printNumber(int chiffre);
int displayDigit3 = 0;
int displayDigit4 = 0;

int const delayValue = 10000;

DHT dht(DHTPIN, DHTTYPE);

unsigned int long timer;
unsigned int long timerMesure;
int temperatureValue;

void setup() {
  // Put the 7 segments displays pins to output mode
  for (int i = 23; i <=45; i +=2){
    pinMode(i, OUTPUT);
  }

  pinMode(DHTPIN, OUTPUT);
  
  digitalWrite(point, LOW);
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);

  timerMesure = millis();
  dht.begin();
  temperatureValue = dht.readTemperature();
}

void loop() {
  if (millis() - timerMesure > 2000){
    temperatureValue = dht.readTemperature();
    timerMesure = millis();
  }
  printTemperature(temperatureValue);
  Serial.println(temperatureValue);
}

void printNumber(int chiffre){
  switch (chiffre){
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

void printTemperature(int temperature){
  if (!displayDigit3 && !displayDigit4){
    displayDigit3 = 1;
    timer = micros();
  }
  if (displayDigit3 && (micros()-timer > delayValue)){
    printDigit3((temperature - temperature%10)/10);
    displayDigit3 = 0; 
  }

  if (!displayDigit3 && !displayDigit4){
    displayDigit4 = 1;
    timer = micros();
  }
  if (displayDigit4 && (micros()-timer > delayValue)){
    printDigit4(temperature%10);
    displayDigit4 = 0; 
  }
  
}

void printDigit3(int temperatureDixaine){
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printNumber(temperatureDixaine);
}

void printDigit4(int temperatureUnite){
  digitalWrite(digit4, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printNumber(temperatureUnite);
}
