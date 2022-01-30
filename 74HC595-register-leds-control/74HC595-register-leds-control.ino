/* Code written by : Adrien Louvrier, 05/02/2021
 *  Objectif : use a 74HC595 IC registers to turn on leds
 * Card used : Arduino Uno
 * Electronic Circuit : 
 * input : none
 * output :
 * - a 74HC595 register connected to pins 8, 9 and 10, 5V and grd
 * - 8 leds with résistors connected to the register and grd
 * 
 * Note : the writeRegisters, setRegisterPin and clearRegisters weren't written by me
 */

#define PIN_DS 8 // 74HC595 module pins
#define PIN_STCP 9
#define PIN_SHCP 10

boolean registers[8]; // registers state

// Function prototypes
void clearRegisters();
void writeRegisters();
void setRegisterPin(int index, int value);

void setup() {
  pinMode(PIN_DS, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);
  pinMode(PIN_STCP, OUTPUT);

  // Registers initialization 
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
