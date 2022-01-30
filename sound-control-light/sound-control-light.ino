/* Code written by Adrien Louvrier, 13/01/2021
 * Objective : turn on an led with a sound sensor
 * Card used : Arduino Uno
 * 
 * Electronic Circuit :
 * input :
 * - A sound sensor connected to pin 3, 5V and grd
 * 
 * output :
 * - LED with a 330 Ohms resistor in serial connected to pin 9 and grd
 */

#define SoundSensorDigitalPin 3 // Sound sensor pin

#define LedPin 9 // led pin

boolean ledState = 0;

void setup() {
  pinMode(SoundSensorDigitalPin, INPUT);
  pinMode(LedPin, OUTPUT);
}

void loop() {
  // Read the values of the sound sensor
  int soundSensorDigitalValue = digitalRead(SoundSensorDigitalPin);

  // Change the led state if there is sound
  if (soundSensorDigitalValue){
    ledState = !ledState;
    digitalWrite(LedPin, ledState);

    // Wait 1 sec before detecting the sound
    delay(1000);
  }
}
