/* Code written by Adrien Louvrier, 08/01/2021
 *
 * Objective : display on a leds matrix what the user is typing on the digicode
 * Card used : Arduino Mega 2560
 * 
 * Eletronic Circuit :
 * input : 
 * - a digicode (line0 -> pin 39, line1 -> pin 37, line2 -> pin 35, line3 -> pin 33,
 * column0 -> pin 29, column1 -> pin 27, column2 -> 25, column3 -> 23)
 * 
 * output :
 * - a 1088AS leds matrix connected to pins 49, 51, 53, 5V and grd
 * 
 * Note : the functions used weren't written by me
 */

#define DIN_PIN 49
#define CS_PIN 51
#define CLK_PIN 53

#define line0 39
#define line1 37
#define line2 35
#define line3 33

#define column0 29
#define column1 27
#define column2 25
#define column3 23

// Hexa values of each lines for each symbol
int const A[8] = {0x00, 0x3C, 0x24, 0x24, 0x3C, 0x24, 0x24, 0x24};
int const B[8] = {0x00, 0x38, 0x24, 0x24, 0x38, 0x24, 0x24, 0x38};
int const C[8] = {0x00, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C};
int const D[8] = {0x00, 0x38, 0x24, 0x24, 0x24, 0x24, 0x24, 0x38};

int const ZERO[8] = {0x00, 0x3C, 0x24, 0x24, 0x24, 0x24, 0x24, 0x3C};
int const ONE[8] = {0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08};
int const TWO[8] = {0x00, 0x3C, 0x04, 0x04, 0x3C, 0x20, 0x20, 0x3C};
int const THREE[8] = {0x00, 0x3C, 0x04, 0x04, 0x3C, 0x04, 0x04, 0x3C};
int const FOUR[8] = {0x00, 0x24, 0x24, 0x24, 0x3C, 0x04, 0x04, 0x04};
int const FIVE[8] = {0x00, 0x3C, 0x20, 0x20, 0x3C, 0x04, 0x04, 0x3C};
int const SIX[8] = {0x00, 0x3C, 0x20, 0x20, 0x3C, 0x24, 0x24, 0x3C};
int const SEVEN[8] = {0x00, 0x3C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04};
int const EIGHT[8] = {0x00, 0x3C, 0x24, 0x24, 0x3C, 0x24, 0x24, 0x3C};
int const NINE[8] = {0x00, 0x3C, 0x24, 0x24, 0x3C, 0x04, 0x04, 0x3C};

int const ASTERIX[8] = {0x00, 0x42, 0x24, 0x18, 0x7E, 0x18, 0x24, 0x42};
int const HASH_TAG[8] = {0x00, 0x14, 0x14, 0x7E, 0x28, 0x7C, 0x28, 0x28};


// Function prototypes
void writePix(int value);
void writeLine(int address, int value);
void writeMatrix(const  int *tab);
void init1088AS();
void clearMatrix();

void setup() {
  pinMode(CS_PIN, OUTPUT);
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  delay(50);

  // Lines are configured in output mode
  pinMode(line0, OUTPUT);
  pinMode(line1, OUTPUT);
  pinMode(line2, OUTPUT);
  pinMode(line3, OUTPUT);

  // Colomns are configured in input mode with pull-up
  pinMode(column0, INPUT_PULLUP);
  pinMode(column1, INPUT_PULLUP);
  pinMode(column2, INPUT_PULLUP);
  pinMode(column3, INPUT_PULLUP);  

  init1088AS();
  clearMatrix();
}

void loop() {
  int column0State = HIGH;
  int column1State = HIGH;
  int column2State = HIGH;
  int column3State = HIGH;

  // Put the line 0 to 0V and others to 5V
  digitalWrite(line0, LOW);
  digitalWrite(line1, HIGH);
  digitalWrite(line2, HIGH);
  digitalWrite(line3, HIGH);

  // Recover the columns state
  column0State = digitalRead(column0);
  column1State = digitalRead(column1);
  column2State = digitalRead(column2);
  column3State = digitalRead(column3);

  // If column 0 is at LOW, the button 1 is pressed
  if(column0State == LOW) {
    writeMatrix(ONE);
  }

  // If column 0 is at LOW, the button 2 is pressed
  if(column1State == LOW) {
    writeMatrix(TWO);    
  }

  // If column 0 is at LOW, the button 3 is pressed
  if(column2State == LOW) {
    writeMatrix(THREE);     
  }

  // If column 3 is at LOW, the button A is pressed
  if(column3State == LOW) {
    writeMatrix(A);    
  }

  // Put the line 1 to 0V and others to 5V
  digitalWrite(line0, HIGH);
  digitalWrite(line1, LOW);
  digitalWrite(line2, HIGH);
  digitalWrite(line3, HIGH);

  // Recover the columns state
  column0State = digitalRead(column0);
  column1State = digitalRead(column1);
  column2State = digitalRead(column2);
  column3State = digitalRead(column3);

  // If column 0 is at LOW, the button 4 is pressed
  if(column0State == LOW) {
    writeMatrix(FOUR);
  }

  // If column 1 is at LOW, the button 5 is pressed
  if (column1State == LOW) {
    writeMatrix(FIVE);    
  }

  // If column 2 is at LOW, the button 6 is pressed
  if(column2State == LOW) {
    writeMatrix(SIX);    
  }

  // If column 3 is at LOW, the button B is pressed
  if(column3State == LOW) {
    writeMatrix(B);    
  }

  // Put the line 2 to 0V and others to 5V
  digitalWrite(line0, HIGH);
  digitalWrite(line1, HIGH);
  digitalWrite(line2, LOW);
  digitalWrite(line3, HIGH);

  // Recover the columns state
  column0State = digitalRead(column0);
  column1State = digitalRead(column1);
  column2State = digitalRead(column2);
  column3State = digitalRead(column3);

  // If column 0 is at LOW, the button 7 is pressed
  if(column0State == LOW) {
    writeMatrix(SEVEN);
  }

  // If column 1 is at LOW, the button 8 is pressed
  if(column1State == LOW) {
    writeMatrix(EIGHT);    
  }

  // If column 2 is at LOW, the button 9 is pressed
  if(column2State == LOW) {
    writeMatrix(NINE);    
  }

  // If column 3 is at LOW, the button C is pressed
  if(column3State == LOW) {
    writeMatrix(C);    
  }  

  // Put the line 3 to 0V and others to 5V
  digitalWrite(line0, HIGH);
  digitalWrite(line1, HIGH);
  digitalWrite(line2, HIGH);
  digitalWrite(line3, LOW);

  // Recover the columns state
  column0State = digitalRead(column0);
  column1State = digitalRead(column1);
  column2State = digitalRead(column2);
  column3State = digitalRead(column3);

  // If column 0 is at LOW, the button * is pressed
  if(column0State == LOW) {
    writeMatrix(ASTERIX);
  }

  // If column 1 is at LOW, the button 0 is pressed
  if(column1State == LOW) {
    writeMatrix(ZERO);    
  }

  // If column 2 is at LOW, the button # is pressed
  if(column2State == LOW) {
    writeMatrix(HASH_TAG);    
  }

  // If column 3 is at LOW, the button D is pressed
  if(column3State == LOW) {
    writeMatrix(D);    
  }   
}

void writePix(int value){
  digitalWrite(CS_PIN, LOW);
  for (int i = 0; i<8; ++i){
    digitalWrite(CLK_PIN,LOW);
    digitalWrite(DIN_PIN, value & 0x80); // masking the data
    value = value << 1; // Shift bits to the left
    digitalWrite(CLK_PIN, HIGH);
  }
}

void writeLine(int address, int value){
  digitalWrite(CS_PIN, LOW);
  writePix(address);
  writePix(value);
  digitalWrite(CS_PIN, HIGH);
  
}

void writeMatrix(const  int *tab) { // or int tab[8]
  for (int i = 0; i<8; ++i){
    writeLine(i+1,tab[i]);  
  }
}

void init1088AS() {
  writeLine(0x09, 0x00); // decoding : BCD
  writeLine(0x0A, 0x01); // brightness
  writeLine(0x0B, 0x07); // scanlimit: 8 LEDs
  writeLine(0x0C, 0x01); // power_down mode : 0, normal mode : 1
  writeLine(0x0F, 0x00); // //test display: 1; EOT, display : 0
}

void clearMatrix() { // or int tab[8]
  const int clean[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  writeMatrix(clean);
}
