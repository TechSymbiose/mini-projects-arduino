/*  Code written by Adrien Louvrier, 14/01/2021

 *  Objective : turn on leds according to the level of water
 * Card used : Arduino Uno
 * 
 * Electronic circuit
 * input : 
 *  - water level sensor (S -> A0, Vcc -> 5V, grd -> grd)
 * 
 * output : 
 *  - red led with 330 Omhs resistance (Vcc -> 2, grd -> grd)
 *  - yellow led with 330 Omhs resistance (Vcc -> 3, grd -> grd)
 *  - green led with 330 Omhs resistance (Vcc -> 4, grd -> grd)
 */

#define sensorPin A0 // water level sensor

#define redLedPin 2 // leds pins
#define yellowLedPin 4
#define greenLedPin 6

void setup() {
  pinMode(redLedPin, OUTPUT); // Setup the leds pins in output mode
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Reading the water level sensor pin

  // Level 1 : turn on green led if (SensorValue <= 330)
  if (sensorValue <= 330) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  }

  // Level 2 : turn on red led if 330 < SensorValue <= 345
  if (sensorValue > 330 && sensorValue <= 345) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  }

  // Level 3 : turn on red led if SensorValue > 345
  if (sensorValue > 345) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  }
}
