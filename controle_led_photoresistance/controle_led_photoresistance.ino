/* Code written by Adrien Louvrier, 26/12/2020
 * Objective : control a led with a photoresistor
 * Card used : Arduino Uno
 * 
 * Electronic circuit :
 * input :
 *  - photoresistor in parallel with a 10kOhms resistor connected to pin A0, 3V and grd
 * output :
 *  - led with 330 Ohms resistance connected to pin 3 and grd
 * 
 */
 
#define ledPin 2
#define photores A0

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int value = digitalRead(photores);
  if (value){
    digitalWrite(ledPin, LOW);
  }
  else{
    digitalWrite(ledPin, HIGH);
  }
}
