/* Objectif : Utiliser un accéléromètre pour afficher des leds sur une matrice de led
   Carte utilisée : Arduino Uno
   Date de création : 30/01/2021
   Auteur : Adrien Louvrier
   Circuit :
   - Un accéléromètre connecté à 5V, grd, SCL et SDA
   - Une matrice de leds connectée à 5V, grd, pins 8, 9 et 10
   The following functions weren't written by me : convert_int16_to_str, writeLine, writeMatrix, init_1088AS, clearMatrix
*/

#include <Wire.h>

#define MPU_ADDR 0x68

#define LED_LT 5
#define LED_LB 2
#define LED_RB 3
#define LED_RT 4

#define DIN_PIN 8
#define CS_PIN 9
#define CLK_PIN 10

int linesValues[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Values for each line

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer row data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature;

char tmp_str[7]; // temporary variable used in convert function

// Function prototypes
char* convert_int16_to_str(int16_t i);
void writePix(int value);
void writeLine(int address, int value);
void writeMatrix(int *tab);
void init_1088AS(void);
void clearMatrix();
void manageDisplay(int i);
void manageDisplay(void);

char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void writePix(int value) {
  digitalWrite(CS_PIN, LOW);
  for (int i = 0; i < 8; ++i) {
    digitalWrite(CLK_PIN, LOW);
    digitalWrite(DIN_PIN, value & 0x80); // masquage de la donnée
    value = value << 1; // Shift left bits 
    digitalWrite(CLK_PIN, HIGH);
  }
}

void writeLine(int address, int value) {
  digitalWrite(CS_PIN, LOW);
  writePix(address);
  writePix(value);
  digitalWrite(CS_PIN, HIGH);

}

void writeMatrix(int *tab) { // ou int tab[8]
  for (int i = 0; i < 8; ++i) {
    writeLine(i + 1, tab[i]);
  }
}

void init_1088AS(void) {
  writeLine(0x09, 0x00); // decoding : BCD
  writeLine(0x0A, 0x01); // brightness
  writeLine(0x0B, 0x07); // scanlimit: 8 LEDs
  writeLine(0x0C, 0x01); // power_down mode : 0, normal mode : 1
  writeLine(0x0F, 0x00); // //test display: 1; EOT, display : 0
}

void clearMatrix() { // or int tab[8]
  int clean[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  writeMatrix(clean);
}

void manageDisplay(int i) {
  if (accelerometer_x > 16000) {
    linesValues[i] = 0x01;
    
  } else if (accelerometer_x <= 16000 && accelerometer_x > 14000) {
    linesValues[i] = 0x03;
    
  } else if (accelerometer_x <= 14000 && accelerometer_x > 12000) {
    linesValues[i] = 0x02;
    
  } else if (accelerometer_x <= 12000 && accelerometer_x > 8000) {
    linesValues[i] = 0x06;
    
  } else if (accelerometer_x <= 8000 && accelerometer_x > 6000) {
    linesValues[i] = 0x04;
    
  } else if (accelerometer_x <= 6000 && accelerometer_x > 4000) {
    linesValues[i] = 0x0C;
    
  } else if (accelerometer_x <= 4000 && accelerometer_x > 2000) {
    linesValues[i] = 0x08;
    
  } else if (accelerometer_x <= 2000 && accelerometer_x > -2000) {
    linesValues[i] = 0x18;
    
  } else if (accelerometer_x <= -2000 && accelerometer_x > -4000) {
    linesValues[i] = 0x10;
    
  } else if (accelerometer_x <= -4000 && accelerometer_x > -6000) {
    linesValues[i] = 0x30;
    
  } else if (accelerometer_x <= -6000 && accelerometer_x > -8000) {
    linesValues[i] = 0x20;
    
  } else if (accelerometer_x <= -8000 && accelerometer_x > -12000) {
    linesValues[i] = 0x60;
    
  } else if (accelerometer_x <= -12000 && accelerometer_x > -14000) {
    linesValues[i] = 0x40;
    
  } else if (accelerometer_x <= -14000 && accelerometer_x > -16000) {
    linesValues[i] = 0xC0;
    
  } else if (accelerometer_x <= -16000) {
    linesValues[i] = 0x80;
  }
}

void manageDisplay() {
  for (int i = 0; i < 8; ++i) {
    linesValues[i] = 0x00;
  }
  if (accelerometer_y >= 14000) {
    manageDisplay(0);
  }
  if (accelerometer_y >= 8000 && accelerometer_y < 16000) {
    manageDisplay(1);
  }
  if (accelerometer_y >= 4000 && accelerometer_y < 12000) {
    manageDisplay(2);
  }
  if (accelerometer_y >= -2000 && accelerometer_y < 6000) {
    manageDisplay(3);
  }
  if (accelerometer_y >= -6000 && accelerometer_y < 2000) {
    manageDisplay(4);
  }
  if (accelerometer_y >= -12000 && accelerometer_y < -4000) {
    manageDisplay(5);
  }
  if (accelerometer_y >= -16000 && accelerometer_y < -8000) {
    manageDisplay(6);
  }
  if (accelerometer_y < -14000) {
    manageDisplay(7);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  delay(50);
  init_1088AS();
  clearMatrix();
  pinMode(LED_LT, OUTPUT);
  pinMode(LED_LB, OUTPUT);
  pinMode(LED_RB, OUTPUT);
  pinMode(LED_RT, OUTPUT);
  digitalWrite(LED_LT, LOW);
  digitalWrite(LED_LB, LOW);
  digitalWrite(LED_RB, LOW);
  digitalWrite(LED_RT, LOW);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the conneciton is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read(); means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_XOUT_H) and 0x3E (ACCEL_XOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_XOUT_H) and 0x40 (ACCEL_XOUT_L)
  temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (ACCEL_XOUT_H) and 0x44 (ACCEL_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (ACCEL_XOUT_H) and 0x46 (ACCEL_XOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (ACCEL_XOUT_H) and 0x48 (ACCEL_XOUT_L)

  //print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register MAP and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature / 340.00 + 36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();

  // Turn on and off leds according to the inclination of the gyroscope
  if (accelerometer_x < 1000 && accelerometer_y < -8000) {
    digitalWrite(LED_LB, HIGH);
    digitalWrite(LED_RB, HIGH);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, LOW);
  } else if (accelerometer_x < 1000 && accelerometer_y > 8000) {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, HIGH);
    digitalWrite(LED_LT, HIGH);
  } else if (accelerometer_x > 8000 && accelerometer_y < 1000) {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, HIGH);
    digitalWrite(LED_RT, HIGH);
    digitalWrite(LED_LT, LOW);
  } else if (accelerometer_x < -8000 && accelerometer_y < 1000) {
    digitalWrite(LED_LB, HIGH);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, HIGH);
  } else {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, LOW);
  }

  // Display on the leds matrix
  manageDisplay();
  writeMatrix(linesValues);

  delay(30);
}
