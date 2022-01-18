 /* Code written by Adrien Louvrier, 26/12/2020
  *  Objective : turn on a ledPin thanks to a motion sensor
 * 
 * Electronic Circuit : 
 * input :
 *  - Motion sensor (out -> A0, Vcc -> 3V, grd -> grd)
 * output :
 *  - ledPin with 330 Ohms connected to pin 2 and grd
 */

#define ledPin 2
#define motionSensorPin 4

void setup() {
  pinMode(motionSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int motionSensValue = digitalRead(motionSensorPin);
  if (motionSensValue){
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }
}
