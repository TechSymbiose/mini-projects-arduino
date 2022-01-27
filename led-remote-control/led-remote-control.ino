/* Code Written by Adrien Louvrier
 * Objective : control leds with an IR remote
 * Card used : Arduino Mega 2560
 * 
 * Electronic circuit : 
 * input :
 *  - IR receiver connected to pin 23, 5V and grd
 * output :
 *  - 9 leds with 330 Ohms resistors connected to grd and pins 45, 41, 37, 43, 39, 35, 33, 31, 29
 */

#include <IRremote.h>

#define led1Pin 45 // Leds pins
#define led2Pin 41
#define led3Pin 37
#define led4Pin 43
#define led5Pin 39
#define led6Pin 35
#define led7Pin 33
#define led8Pin 31
#define led9Pin 29

#define IR_PIN 23 // Remote pin

#define POWER 0xFFA25D // Remote buttons values
#define VOL_PLUS 0xFF629D
#define STOP 0xFFE21D
#define PREV 0xFF22DD
#define PAUSE 0xFF02FD
#define NEXT 0xFFC23D
#define DOWN 0xFFE01F
#define VOL_MINUS 0xFFA857
#define UP 0xFF906F
#define ZERO 0xFF6897
#define EQ 0xFF9867
#define REPT 0xFFB04F
#define ONE 0xFF30CF
#define TWO 0xFF18E7
#define THREE 0xFF7A85
#define FOUR 0xFF10EF
#define FIVE 0xFF38C7
#define SIX 0xFF5AA5
#define SEVEN 0xFF42BD
#define HEIGHT 0xFF4AB5
#define NINE 0xFF52AD

int led1State = 0; // Leds states
int led2State = 0;
int led3State = 0;
int led4State = 0;
int led5State = 0;
int led6State = 0;
int led7State = 0;
int led8State = 0;
int led9State = 0;

IRrecv irrecv(IR_PIN);
decode_results results;

void setup() {
  // Setting the leds pins in output mode
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  pinMode(led8Pin, OUTPUT);
  pinMode(led9Pin, OUTPUT);

  delay(30);

  irrecv.enableIRIn();
}

void loop() {
  // Check if we received something

  // If we received something, change leds state according to the button pressed
  if (irrecv.decode(&results)){
    switch (results.value){
      case ONE:{
        led1State = !led1State;
        digitalWrite(led1Pin, led1State);
        break;
      }
      case TWO:{
        led2State = !led2State;
        digitalWrite(led2Pin, led2State);
        break;
      }
      case THREE:{
        led3State = !led3State;
        digitalWrite(led3Pin, led3State);
        break;
      }
      case FOUR:{
        led4State = !led4State;
        digitalWrite(led4Pin, led4State);
        break;
      }
      case FIVE:{
        led5State = !led5State;
        digitalWrite(led5Pin, led5State);
        break;
      }
      case SIX:{
        led6State = !led6State;
        digitalWrite(led6Pin, led6State);
        break;
      }
      case SEVEN:{
        led7State = !led7State;
        digitalWrite(led7Pin, led7State);
        break;
      }
      case HEIGHT:{
        led8State = !led8State;
        digitalWrite(led8Pin, led8State);
        break;
      }
      case NINE:{
        led9State = !led9State;
        digitalWrite(led9Pin, led9State);
        break;
      }      
    }
    irrecv.resume();
    delay(30);
  }
}
