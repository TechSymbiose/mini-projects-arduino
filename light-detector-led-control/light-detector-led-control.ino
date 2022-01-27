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
 
#define ledPin 2 // led pin 
#define photores A0 // photoresistor pin

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the value of the photoresistor
  int value = digitalRead(photores);

  // Turn off the led if there is light
  if (value){
    digitalWrite(ledPin, LOW);
  }
  // Turn on the led if there isn't enough light
  else{
    digitalWrite(ledPin, HIGH);
  }
}
