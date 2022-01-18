/*  Code written by Adrien Louvrier, 14/01/2021
 *  Objective : turn on leds according to the level of water
 * Card used : Arduino Uno
 * Electronic circuit
 * input : 
 *  - water level sensor (S -> A0, Vcc -> 5V, grd -> grd)
 * output : 
 *  - red led with 330 Omhs resistance (Vcc -> 2, grd -> grd)
 *  - yellow led with 330 Omhs resistance (Vcc -> 3, grd -> grd)
 *  - green led with 330 Omhs resistance (Vcc -> 4, grd -> grd)
 */

#define sensorPin A0 // Water level sensor

#define redLedPin 2 // Leds
#define yellowLedPin 4
#define greenLedPin 6

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  // Level 1 (SensorValue <= 330) : turn on green led
  if (sensorValue <= 330){
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  }

  // Level 2 (330 < SensorValue <= 345) : turn on yellow led
  if (sensorValue > 330 && sensorValue <= 345){
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  }

  // Level 3 (SensorValue > 345) : turn on red led
  if (sensorValue > 345){
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  }
}
