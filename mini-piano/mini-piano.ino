/* Code written by Adrien Louvrier, 16/01/2021
 *
 *  Objective : make a mini piano with 5 notes
 *  Card used : Arduino Uno
 *  
 * Eletronic circuit :
 * 
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

#define FA_SHARP 370
#define SOL_SHARP 415
#define LA_SHARP 466

#define DURATION 50 // Duration of a note

void setup() {
  // Set the buttons pins in input mode
  digitalWrite(button1Pin, INPUT);
  digitalWrite(button2Pin, INPUT);
  digitalWrite(button3Pin, INPUT);
  digitalWrite(button4Pin, INPUT);
  digitalWrite(button5Pin, INPUT);

  // Set the buzzer pin in output mode
  digitalWrite(buzzerPin, OUTPUT);
}

void loop() {
  // Reading  the values from the buttons
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);
  int button5State = digitalRead(button5Pin);

  // Play notes according to the button state
  if (button1State){
    tone(buzzerPin, MI, DURATION);
  }
  if (button2State){
    tone(buzzerPin, FA_SHARP, DURATION);
  }
  if (button3State){
    tone(buzzerPin, SOL_SHARP, DURATION);
  }
  if (button4State){
    tone(buzzerPin, LA_SHARP, DURATION);
  }
  if (button5State){
    tone(buzzerPin, SI, DURATION);
  }
}
