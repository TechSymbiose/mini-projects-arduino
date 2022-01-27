/* Code written by Adrien Louvrier, 08/01/2021
 * Objective : print on a LCD display the distance measured by the ultrasonic sensor
 * Card used : Mega 2560
 * Electronic Circuit :
 * input :
 *  - Ultrasonic sensor (trig -> A0, echo ->A1, Vcc -> 5V, grd -> grd)
 * output : 
 *  -LCD display (rs -> 45, en -> 43, d4 -> 41, d5 -> 39, d6 -> 37, 
 *  d-> 35, Vcc -> 5V, grd -> grd)
 */

#include <LiquidCrystal.h>

#define trigPin A0 // ultrasonic sensor pins
#define echoPin A1

long duration; // Duration of one measurement
int distance; // Distance calculated

const int rs = 45, en = 43, d4 = 41, d5 = 39, d6 = 37, d7 = 35; // lcd display pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(trigPin, OUTPUT); // Setup the ultrasonic sensor pins
  pinMode(echoPin, INPUT);

  // Init the lcd screen
  lcd.begin(16,2);
  lcd.display();
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

  // Display the distance measured on the lcd screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance : ");
  // Print an error if distance > 1000(cm)
  if (distance >1000){
    lcd.print("Error");
  }
  else{
    lcd.print(distance);
    lcd.print("cm");
  }
  delay(100);
}
