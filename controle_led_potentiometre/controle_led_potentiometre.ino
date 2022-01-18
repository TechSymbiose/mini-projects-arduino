/* Code written by Adrien Louvrier
 *  Objective : control a ledPin with a potPinentiometer
 *  Card used : Arduino Uno
 *  
 *  Electronic Circuit :
 *  input :
 *    - 10kOmhs potPinentiometer in parallel with a 10kOhms resistance connected to pin A0, 5V and grd
 *  
 *  output :
 *    - ledPin with 330 Ohms resistance connected to pin 3 and grd
 * 
 */

#define ledPin 3
#define potPin A0

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int outputValue = analogRead(potPin);
  outputValue = map(outputValue, 1, 1024, 1 , 255);
  analogWrite(ledPin, outputValue);
}
