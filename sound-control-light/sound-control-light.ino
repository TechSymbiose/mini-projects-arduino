/* Objectif : Allumer une led avec un capteur de son
 * Carte utilisée : Arduino Uno
 * Date de création : 13/01/2021
 * Auteur : Adrien Louvrier
 * Circuit :
 * - un capteur de son connecté aux pins 3, 5V et grd
 * - une led avec résistance 330 Ohms en série connectée à la pin 9 et grd
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
