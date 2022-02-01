/* Code written by Adrien Louvrier, 31/01/2021
 *
 * Objective : Make a 2 axis angle using an accelerometer
 * Card used : Arduino Mega 2560
 * 
 * Electronic circuit :
 * 
 * input :
 *  - An accelerometer connected to 5V, grd, SCL and SDA
 * 
 * output :
 *  - 10 leds with 330 Ohms resistors connected to pins 36, 38, 40, 42, 44, 
 * 48, 19, 50, 53, 52 and grd
 * - A lcd screen connected (rs -> pin 45, en -> pin 43, d4 -> pin 41,
 * d5 -> pin 39, d6 -> pin 37, d7 -> pin 35, vcc -> 5V, grd -> grd)
 * 
 * The convert_int16_to_str function wasn't written by me
 */


#include <Wire.h>
#include <LiquidCrystal.h>

#define MPU_ADDR 0x68 // adress of the accelerometer

#define ledx1 44 // leds pins
#define ledx2 42
#define ledx3 40
#define ledx4 38
#define ledx5 36

#define ledy1 52
#define ledy2 53
#define ledy3 50
#define ledy4 49
#define ledy5 48

#define ledPin 6

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer row data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature;

const int rs = 45, en = 43, d4 = 41, d5 = 39, d6 = 37, d7 = 35; // lcd screen pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char tmp_str[7]; // temporary variable used in convert function

// Prototype of the function

/* Objective : convert a int16_t number into string
 * input : a int16_t number
 * output : the string corresponding to the int16_t number value
 */
char* convert_int16_to_str(int16_t i);

void setup() {
  Serial.begin(9600);
  delay(50);
  // Set leds pins in output mode
  pinMode(ledPin, OUTPUT);
  pinMode(ledx1, OUTPUT);
  pinMode(ledx2, OUTPUT);
  pinMode(ledx3, OUTPUT);
  pinMode(ledx4, OUTPUT);
  pinMode(ledx5, OUTPUT);
  pinMode(ledy1, OUTPUT);
  pinMode(ledy2, OUTPUT);
  pinMode(ledy3, OUTPUT);
  pinMode(ledy4, OUTPUT);
  pinMode(ledy5, OUTPUT);

  // Turn off all leds
  digitalWrite(ledx1, LOW);
  digitalWrite(ledx2, LOW);
  digitalWrite(ledx3, LOW);
  digitalWrite(ledx4, LOW);
  digitalWrite(ledx5, LOW);
  digitalWrite(ledy1, LOW);
  digitalWrite(ledy2, LOW);
  digitalWrite(ledy3, LOW);
  digitalWrite(ledy4, LOW);
  digitalWrite(ledy5, LOW);

  // Setup the lcd screen
  lcd.begin(16,2);

  // Setup the accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  lcd.display();
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

  // Reverse the y value of the accelerometer
  accelerometer_y = - accelerometer_y;

  // Mapping the x value of the accelerometer
  if (accelerometer_x < 16500 && accelerometer_x > -16500) {
    accelerometer_x = map(accelerometer_x, -16500, 16500, -180, 180);
    
  } else if (accelerometer_x < -16500) {
    accelerometer_x = -180;
    
  } else if (accelerometer_x > 16500) {
    accelerometer_x = 180;
  }
  
  // Mapping the y value of the accelerometer
  if (accelerometer_y < 16500 && accelerometer_y > -16500) {
    accelerometer_y = map(accelerometer_y, -16500, 16500, -180, 180);
    
  } else if (accelerometer_y < -16500) {
    accelerometer_y = -180;
    
  } else if (accelerometer_y > 16500) {
    accelerometer_y = 180;
  }

  // Display the value of the angle for both axis
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Angle x : ");
  lcd.print(accelerometer_x);
  
  lcd.setCursor(0,1);
  lcd.print("Angle y : ");
  lcd.print(accelerometer_y);

  // Mapping the brightness of the brightness led which must be turned on according to the value of the angle for x axis
  int ledBrightness = map(accelerometer_x, -180, 180, -15, 15);

  if (ledBrightness < 0) {
    ledBrightness = 0;
  }

  // Turn on (or off) the led according to the value of the angle for x axis
  switch (ledBrightness) {
    case 0:
      analogWrite(ledPin,0);
      break;
    case 1:
      analogWrite(ledPin,0);
      break;
    case 2:
      analogWrite(ledPin,0);
      break;
    case 3:
      analogWrite(ledPin,51);
      break;
    case 4:
      analogWrite(ledPin,68);
      break;
    case 5:
      analogWrite(ledPin,85);
      break;
    case 6:
      analogWrite(ledPin,102);
      break;
    case 7:
      analogWrite(ledPin,119);
      break;
    case 8:
      analogWrite(ledPin,136);
      break;
    case 9:
      analogWrite(ledPin,153);
      break;
    case 10:
      analogWrite(ledPin,170);
      break;
    case 11:
      analogWrite(ledPin,187);
      break;
    case 12:
      analogWrite(ledPin,204);
      break;
    case 13:
      analogWrite(ledPin,221);
      break;
    case 14:
      analogWrite(ledPin,255);
      break;
    case 15:
      analogWrite(ledPin,255);
      break;
  }

  // Mapping the number of the angle leds which must be turned on according to the value of the angle for both axis
  accelerometer_x = map (accelerometer_x, -180, 180, 1, 9);
  accelerometer_y = map (accelerometer_y, -180, 180, 1, 9);

  // Turn on and off leds according to the angle for x axis
  switch (accelerometer_x) {
    case 1:
      digitalWrite(ledx1, HIGH);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, LOW);
      break;
    case 2:
      digitalWrite(ledx1, HIGH);
      digitalWrite(ledx2, HIGH);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, LOW);
      break;
    case 3:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, HIGH);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, LOW);
      break;
    case 4:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, HIGH);
      digitalWrite(ledx3, HIGH);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, LOW);
      break;
    case 5:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, HIGH);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, LOW);
      break;
    case 6:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, HIGH);
      digitalWrite(ledx4, HIGH);
      digitalWrite(ledx5, LOW);
      break;
    case 7:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, HIGH);
      digitalWrite(ledx5, LOW);
      break;
    case 8:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, HIGH);
      digitalWrite(ledx5, HIGH);
      break;
    case 9:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledx2, LOW);
      digitalWrite(ledx3, LOW);
      digitalWrite(ledx4, LOW);
      digitalWrite(ledx5, HIGH);
      break;
  }

  // Turn on and off leds according to the angle for y axis
  switch (accelerometer_y) {
    case 1:
      digitalWrite(ledy1, HIGH);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, LOW);
      break;
    case 2:
      digitalWrite(ledy1, HIGH);
      digitalWrite(ledy2, HIGH);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, LOW);
      break;
    case 3:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, HIGH);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, LOW);
      break;
    case 4:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, HIGH);
      digitalWrite(ledy3, HIGH);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, LOW);
      break;
    case 5:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, HIGH);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, LOW);
      break;
    case 6:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, HIGH);
      digitalWrite(ledy4, HIGH);
      digitalWrite(ledy5, LOW);
      break;
    case 7:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, HIGH);
      digitalWrite(ledy5, LOW);
      break;
    case 8:
      digitalWrite(ledx1, LOW);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, HIGH);
      digitalWrite(ledy5, HIGH);
      break;
    case 9:
      digitalWrite(ledy1, LOW);
      digitalWrite(ledy2, LOW);
      digitalWrite(ledy3, LOW);
      digitalWrite(ledy4, LOW);
      digitalWrite(ledy5, HIGH);
      break;
  }

  // delay of 1 seconde between two measurements
  delay(1000);
}

char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
