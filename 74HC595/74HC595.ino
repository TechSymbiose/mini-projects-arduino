/* Objectif : se servir du registre 74HC595 IC pour allumer des leds
 * Carte utilisée : Arduino Uno
 * Date de création : 05/02/2021
 * Auteur : Adrien Louvrier
 * Circuit : 
 * - un registre 74HC595 connecté aux pins 8, 9 et 10, 5V et grd
 * -8 leds avec résistances en séries connectées au registre et au grd
 */

#define PIN_DS 8
#define PIN_STCP 9
#define PIN_SHCP 10

boolean registers[8];

void clearRegisters();
void writeRegisters();
void setRegisterPin(int index, int value);

void setup() {
  pinMode(PIN_DS, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);

  clearRegisters();
  writeRegisters();
  delay(50);
  setRegisterPin(6, LOW);
  writeRegisters();
}

void loop() {
  for (int i = 0; i < 8; ++i) {
    setRegisterPin(i, HIGH);
    writeRegisters();
    delay(100);
  }

  for (int i = 0; i < 8; ++i) {
    setRegisterPin(i, LOW);
    writeRegisters();
    delay(100);
  }
}

void clearRegisters() {
  for (int i = 7; i >= 0; --i) {
    registers[i] = HIGH;
  }
}

void writeRegisters() {
  digitalWrite(PIN_STCP, LOW);

  for (int i = 7; i >= 0; --i) {
    digitalWrite(PIN_SHCP, LOW);

    int value = registers[i];

    digitalWrite(PIN_DS, value);
    digitalWrite(PIN_SHCP, HIGH);
  }
  digitalWrite(PIN_STCP, HIGH);
}

void setRegisterPin(int index, int value) {
  registers[index] = value;
}
