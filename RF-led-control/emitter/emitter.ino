/* Code written by Adrien Louvrier
 *
 * Objective : control a led using RF communication
 * Card used : Arduino Nano
 *
 * Electronic Circuit :
 * 
 * input :
 * - button connected with 10kOhms in parallel connected to pin 4, 5V and grd
 * 
 * output: :
 * - led with 330 Ohms resistor connected to pin 6 and grd
 * - NRF24L01+LNA module (pin CE -> pin 9, pin CSN -> pin 10, MOSI -> pin 11, pin MISO -> pin 12, pin SCK -> pin 13, pin Vcc -> 5V, pin grd -> grd) 
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define LedPin 6
#define ButtonPin 4

// Structure used to transmit the data
typedef struct { 
  boolean b1=0;
  boolean b2=0;
}data;
data payload;

RF24 radio(9, 10); // CE, CSN

// Channels used (00001 for emitting, 00002 for receving)
const byte addresses[][6] = {"00001", "00002"}; 

boolean ok = true;
int ledState = 0;

void reception();
void emitting();
void changeLedState();

void setup() {
  pinMode(ButtonPin, INPUT);
  pinMode(LedPin, OUTPUT);

  // Setting the radio communication
  radio.begin();
  radio.setChannel(125);
  radio.openWritingPipe(addresses[0]); // set the channel 00001 for emitting
  radio.openReadingPipe(1, addresses[1]); //set the cannel 00002 for receiving
  radio.setPALevel(RF24_PA_MIN);
  delay(2000);
}
void loop() {
  /* The code inside the loop function wasn't written by myself */
  delay(5);
  /****************[ EMIT ]***************************/
  radio.stopListening();
  emitting();
  /**************************************************/
  delay(5);
  /**************[RECEPTION]************************/
  radio.startListening();
  reception();
  /***********************************************/
}

void reception() {
  if(radio.available()){
     radio.read(&payload, sizeof(payload));
     
    // Detect the rising edge 
    if (payload.b2 == HIGH){
      if (ok == true) {
        changeLedState();
        ok = false;
     }
      else {
        ok = true;
      }
    }
  }
}

void emitting(){
  // Reading the value of the button
  payload.b1 = digitalRead(ButtonPin);

  // If the button is pressed, send the information to the other transmitter
  if (payload.b1 == HIGH) {
    // Detect the rising edge
    if (ok) {
      ok = false;
      // Sending the data...
      radio.write(&payload, sizeof(payload));
    }
  }
  else {
    ok = true;
  }
}

// Turn on the led if it is off, turn off the led if it is on
void changeLedState() {
  if (ledState == 0) {
    digitalWrite(LedPin, HIGH);
    ledState = 1;
  }
  else {
    ledState = 0;
    digitalWrite(LedPin, LOW);
  }
  delay(5);
}
