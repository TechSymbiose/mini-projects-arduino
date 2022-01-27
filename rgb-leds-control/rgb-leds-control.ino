/* Objectif : piloter une led RGB avec un joysticks et 2 boutons (+ et -)
 *  
 *  Date de création : 27/12/2020
 *  Auteur : Adrien Louvrier
 *  Circuit : 
 *  - un joystick connecté aux pins A1, 12, 5V et grd
 *  - 3 leds rgbRedPin, rgbGreenPin et rgbBluePin + résistances 330 Ohms en série connectées aux pins 8, 9, 10 et grd
 *  - une led RGB connectée aux pins 3, 5, 6, et grd
 *  - un encodeur rotatif connecté aux pins 2, 4, 5V et grd
 */

 #define VRy A1

 #define encoderOutputA 4 // encoder pins
 #define encoderOutputB 2

 #define redLedPin 8 // leds pins
 #define greenLedPin 9
 #define blueLedPin 10

 #define rgbRedPin 6 // rgb led pins
 #define rgbGreenPin 5
 #define rgbBluePin 3

 int redValue = 0; // Amount of color
 int greenValue = 0;
 int blueValue = 0;

 int ledState = 0; // Color of the rgb led we want to change
 boolean ledChanged = false; // Variable used to know if the color selected has changed
 int aState; // Current state of the output A of the encoder
 int aLastState; // Last state of the output A of the encoder

void setup() {
  // Setup the output A of the encoder
  pinMode(encoderOutputA, INPUT);
  pinMode(encoderOutputB, INPUT);

  // Setup the leds pins in output mode
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // Setup the rgb pins in output mode
  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);

  // Initialize the last state of the output A of the encoder
  aLastState = digitalRead(encoderOutputA);
}

void loop() {
  // Read the value of the y axis of the joystick
  int VRyValue = analogRead(VRy);

  // Change the color we want to change the amount of brightness
  if ((VRyValue > 1000) && (ledState < 2) && (ledChanged == true)){
   ++ledState;
   ledChanged = false;
  }
  if ((VRyValue < 100) && (ledState > 0) && (ledChanged == true)){
   --ledState;
   ledChanged = false;
  }

  if ((VRyValue >= 100) && (VRyValue <= 1000)){
   ledChanged = false;
  }

  // Read the state of the output A of the encoder
  aState = digitalRead(encoderOutputA);

  // Turn on and off leds according to the color selected
  // If the ledState is at 0, change the red amount of color
  if (ledState == 0){
   digitalWrite(redLedPin, HIGH);
   digitalWrite(greenLedPin, LOW);
   digitalWrite(blueLedPin, LOW);

   // Increase or decrease the amount of the color according to the direction of rotation of the encoder
   if (aState != aLastState){
    if (digitalRead(encoderOutputB) != aState && redValue < 255) {
      ++redValue;
    } else if (redValue > 0) {
      --redValue;
    }
   }
  }

  // If the ledState is at 1, change the green amount of color
  if (ledState == 1) {
   digitalWrite(redLedPin, LOW);
   digitalWrite(greenLedPin, HIGH);
   digitalWrite(blueLedPin, LOW);

   // Increase or decrease the amount of the color according to the direction of rotation of the encoder
   if (aState != aLastState) {
    if (digitalRead(encoderOutputB) != aState && greenValue < 255){
      ++greenValue;
    } else if (greenValue > 0) {
      --greenValue;
    }
   }
  }

  // If the ledState is at20, change the blue amount of color
  if (ledState == 2) {
   digitalWrite(redLedPin, LOW);
   digitalWrite(greenLedPin, LOW);
   digitalWrite(blueLedPin, HIGH);

   // Increase or decrease the amount of the color according to the direction of rotation of the encoder
   if (aState != aLastState) {
    if (digitalRead(encoderOutputB) != aState && blueValue < 255) {
      ++blueValue;
    } else if (blueValue > 0) {
      --blueValue;
    }
   }
  }

  // Keep in memory the last state of the output A of the encoder
  aLastState = aState;

  // Turn on the rgb led according to the amount of red, blue and green
  analogWrite(rgbRedPin, redValue);
  analogWrite(rgbGreenPin, greenValue);
  analogWrite(rgbBluePin, blueValue);
}
