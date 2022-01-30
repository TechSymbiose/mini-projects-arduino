 /* Code written by Adrien Louvrier, 26/12/2020
  * Objective : turn on a ledPin thanks to a motion sensor
  * Card used : Arduino Uno
  * 
  * Electronic Circuit : 
  * input :
  *  - Motion sensor (out -> A0, Vcc -> 3V, grd -> grd)
  * 
  * output :
  *  - ledPin with 330 Ohms connected to pin 2 and grd
  */

#define ledPin 2 // led pin
#define motionSensorPin 4 // motion sensor pin

void setup() {
  pinMode(motionSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Reading the motion sensor pin
  int motionSensValue = digitalRead(motionSensorPin);

  // Turn on the led if there are movements
  if (motionSensValue){
    digitalWrite(ledPin, HIGH);
    delay(5000); // Let the led on for 5 seconds minimum
  }
  // Turn off the led if there isn't any movement
  else {
    digitalWrite(ledPin, LOW);
  }
}
