/* Code written by Adrien Louvrier, 16/01/2021
 *  Objective : make a mini piano with 5 notes
 *  Card used : Arduino Uno
 *  
 * Eletronic circuit :
 * input :
 *  - 5 buttons connected to 5V and grd
 *  - 5 10KOhms resistances connected to pins 2 to 6 and 5V 
 *  (each resistance is in parallel with one button) 
 *  
 * output :
 *  - Passive buzzer connected to pin 8 and grd
 */
 
#define button1Pin 2 //buttons
#define button2Pin 3
#define button3Pin 4
#define button4Pin 5
#define button5Pin 6

#define buzzerPin 8 // buzzer

#define DO 262 // Notes frequencies
#define RE 292
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 494

#define FA_DIESE 370
#define SOL_DIESE 415
#define LA_DIESE 466

#define DURATION 50

void setup() {
  digitalWrite(button1Pin, INPUT);
  digitalWrite(button2Pin, INPUT);
  digitalWrite(button3Pin, INPUT);
  digitalWrite(button4Pin, INPUT);
  digitalWrite(button5Pin, INPUT);
  
  digitalWrite(buzzerPin, OUTPUT);
}

void loop() {
  int bouton1Value = digitalRead(button1Pin);
  int bouton2Value = digitalRead(button2Pin);
  int bouton3Value = digitalRead(button3Pin);
  int bouton4Value = digitalRead(button4Pin);
  int bouton5Value = digitalRead(button5Pin);

  if (bouton1Value){
    tone(buzzerPin, MI, DURATION);
  }
  if (bouton2Value){
    tone(buzzerPin, FA_DIESE, DURATION);
  }
  if (bouton3Value){
    tone(buzzerPin, SOL_DIESE, DURATION);
  }
  if (bouton4Value){
    tone(buzzerPin, LA_DIESE, DURATION);
  }
  if (bouton5Value){
    tone(buzzerPin, SI, DURATION);
  }
}
