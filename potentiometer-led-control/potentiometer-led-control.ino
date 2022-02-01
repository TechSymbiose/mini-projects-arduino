/* Code written by Adrien Louvrier
 *
 *  Objective : control a ledPin with a potentiometer
 *  Card used : Arduino Uno
 *  
 *  Electronic Circuit :
 * 
 *  input :
 *    - 10kOmhs poentiometer in parallel with a 10kOhms resistance connected to pin A0, 5V and grd
 *  
 *  output :
 *    - ledPin with 330 Ohms resistance connected to pin 3 and grd
 */

#define ledPin 3 // led pin
#define potPin A0 // potentiometer pin

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Reading the value of the potentiometer
  int outputValue = analogRead(potPin);
  
  // Mapping the value from 1 to 1024 to 1 to 255 to control the led
  outputValue = map(outputValue, 1, 1024, 1 , 255);

  // Control the led according to the value of the potentiometer
  analogWrite(ledPin, outputValue);
}
