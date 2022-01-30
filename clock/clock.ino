/*  Code written by Adrien Louvrier, 01/02/2021
 *  Objective : make a clock and print the date and time on a LCD screen, 
 *  on serial monitoring and on a 4x7 segments display 
 * Card used : Arduino Mega 2560
 * Electronic circuit :
 * input :
 * - RTC module (Vcc -> 5V, grd -> grd, SDA -> SDA, SCL -> SCL, SQW -> pin 3)
 * 
 * output :
 * - 4x7 segments display with 330 Ohms resistance on each segments (a -> 51, b -> 43, 
 * c -> 46, d -> 50, e -> 52, f -> 49, g -> 44, point -> 48, digit1 -> 53, digit2 -> 47, 
 * digit3 -> 45, digit4 -> 42)
 * 
 * - LCD screen (rs -> 32, en -> 30, d4 -> 28, d5 -> 26, d6 -> 24, d7 -> 22, 
 * Vcc -> 5V, grd -> grd)
*/

#include "RTClib.h"
#include <LiquidCrystal.h>

#define a 51 // segments pins
#define b 43
#define c 46
#define d 50
#define e 52
#define f 49
#define g 44
#define point 48

#define digit1 53 // digits pins
#define digit2 47
#define digit3 45
#define digit4 42

RTC_DS1307 rtc; // clock

const int rs = 32, en = 30, d4 = 28, d5 = 26, d6 = 24, d7 = 22; // lcd screen pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // days of the week

// Function prototypes
void printTime(int tempsHeure, int tempsMinute);
void printDigit4(int tempsMinute);
void printDigit3(int tempsMinute);
void printDigit2(int tempsHeure);
void printDigit1(int tempsHeure);
void printValue(int number);

void setup() {
  Serial.begin(9600);
  // Put the segments pins in output mode
  for (int i = 42; i <= 53; ++i) {
    pinMode(i, OUTPUT);
  }
  
  digitalWrite(point, LOW);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);

  Serial.begin(9600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  /* the following instruction and comments aren't from me */
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // February 01, 2021 at 15h38m00 you would call:
    // rtc.adjust(DateTime(2021, 2, 5, 19, 00, 00));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // February 01, 2021 at 15h38m00 you would call:
  // rtc.adjust(DateTime(2021, 2, 5, 19, 00, 00));
  
  lcd.begin(16,2);
  lcd.display();
  delay(50);

  lcd.display();
  lcd.begin(16,2);
}

void loop() {
  DateTime now = rtc.now(); // Read the date and the time

  // Print the date and the time in the serial monitor
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // Print the date and the time in the lcd screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");

  // Printthe  day
  if (now.day() < 10) {
    lcd.print("0");
  }
  
  lcd.print(now.day());
  lcd.print("/");

  // Print the month
  if (now.month() < 10) {
    lcd.print("0");
  }
  
  lcd.print(now.month());
  lcd.print("/");
  // Print the year
  lcd.print(now.year());

  // Print hours
  lcd.setCursor(0,1);
  lcd.print("    ");
  
  if (now.hour() < 10) {
    lcd.print("0");
  }

  lcd.print(now.hour());
  lcd.print(":");

  // Print minutes
  if (now.minute() < 10) {
    lcd.print("0");
  }
  
  lcd.print(now.minute());
  lcd.print(":");

  // Print the seconds
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second());

  // Print time (hours and minutes) on a segments display
  printTime(now.hour(), now.minute());
}

void printValue(int number) {
  switch (number) {
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

void printTime(int tempsHeure, int tempsMinute) {
  for (int i = 0; i<50; ++i) {
    printDigit1((tempsHeure - tempsHeure%10 )/10);
    delay(5);
    printDigit2(tempsHeure%10);
    delay(5);
    printDigit3((tempsMinute - tempsMinute%10 )/10);
    delay(5);
    printDigit4(tempsMinute%10);
    delay(5);
  }
}

void printDigit1(int timeHourTenth) {
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, LOW);
  digitalWrite(point, LOW);
  printValue(timeHourTenth);
}

void printDigit2(int tempsHeureUnite) {
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit1, HIGH);
  digitalWrite(point, HIGH);
  printValue(tempsHeureUnite);
}

void printDigit3(int tempsMinuteDixaine) {
  digitalWrite(digit4, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printValue(tempsMinuteDixaine);
  digitalWrite(point, LOW);
}

void printDigit4(int tempsMinuteUnite) {
  digitalWrite(point, LOW);
  digitalWrite(digit4, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit1, HIGH);
  printValue(tempsMinuteUnite);
}
