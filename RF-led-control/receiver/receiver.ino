#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define LedPin 6
#define ButtonPin 4

typedef struct{
  boolean b1=0;
  boolean b2=0;
}data;
data payload;


RF24 radio(9, 10); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

boolean ok = true;
int ledState = 0;

void reception();
void emitting();
void changeLedState();

void setup() {
  //Serial.begin(9600);
  pinMode(ButtonPin, INPUT);
  pinMode(LedPin, OUTPUT);
  
  radio.begin();
  radio.setChannel(125);
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  delay(2000);
}
void loop() {
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
     
     if (payload.b1 == HIGH){
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
  payload.b2 = digitalRead(ButtonPin);
  if (payload.b2 == HIGH) {
    if (ok) {
      ok = false;
      radio.write(&payload, sizeof(payload));
      //changeLedState();
      //Serial.println("sheeesh");
    }
  }
  else {
    ok = true;
  }
}

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
