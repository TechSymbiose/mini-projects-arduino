/* Objectif : tester le buzzer passif
 * 
 * 
 */

#include <SPI.h>
#include <MFRC522.h>

#define buzzerPin 45 // buzzer pin

#define redLedPin 8 // leds pins
#define greenLedPin 9

#define RST_PIN 23 // RFID reader pins
#define SS_PIN 25

// Card UID: 97 99 EE A6
// Badge UID: 47 19 20 B5

// Prototype of the function

/*  Objective : Play Ode to Joy by Beethoven using the buzzer
 * input : none
 * output : none
 */
void playMusic();

MFRC522 module_rfid(SS_PIN, RST_PIN);

void setup() {
  // Set buzzer and leds pins in output mode
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  delay(30);

  // Initialiaz the RFID reader
  SPI.begin();
  module_rfid.PCD_Init();
}

void loop() {
  // Detect if there isn't any RFID card
  if ( ! module_rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!module_rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Read the value of the RFID card
  String UID = "";
  for (byte i = 0; i < module_rfid.uid.size; i++){
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase();

  // If the ID corresponds to the card, turn on the red led and make a sound
  if (UID.substring(1) == "97 99 EE A6"){
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 900, 1000);
    delay(1000);
    digitalWrite(redLedPin, LOW);
  }

  // If the ID corresponds to the badge, turn on the green led and play Ode to Joy with the buzzer
  if (UID.substring(1) == "47 19 20 B5"){
    digitalWrite(greenLedPin, HIGH);
    playMusic();
    digitalWrite(greenLedPin, LOW);
  }
}

void playMusic(){
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 330, 795);
  delay(800);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 294, 795);
  delay(800);

  delay(400);

  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 795);
  delay(800);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 262, 795);
  delay(800);

  delay(400);

  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 195);
  delay(200);
  tone(buzzerPin, 350, 195);
  delay(200);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 195);
  delay(200);
  tone(buzzerPin, 350, 195);
  delay(200);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 196, 795);
  delay(800);

  delay(400);

  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 392, 395);
  delay(400);
  tone(buzzerPin, 349, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 294, 395);
  delay(400);
  tone(buzzerPin, 330, 395);
  delay(400);
  tone(buzzerPin, 294, 795);
  delay(800);
  tone(buzzerPin, 262, 395);
  delay(400);
  tone(buzzerPin, 262, 795);
  delay(800);
}
