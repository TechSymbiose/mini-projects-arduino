/* Code written by Adrien Louvrier, 22/12/2020
 * Objective : Enter a 4 bits number (from 0 to 15) thanks to 4 buttons (one button per bit) and print this number on a 7 segments display
 * 
 * Electronic circuit : 
 *  - input :
 *  - 4 buttons connected to Vcc and pins 2 to 5
 *  - 4 resistances 10kOhms connected to grd and pins 2 to 5
 *  output :
 *  - a 7 segments display (with resistances 330 Ohms on each segment input) connected to grd and pins 6 to 12
 */
 
int const pin_d0 = 2;
int const pin_d1 = 3;
int const pin_d2 = 4;
int const pin_d3 = 5;

int const pin_a = 6;
int const pin_b = 7;
int const pin_c = 8;
int const pin_d = 9;
int const pin_e = 10;
int const pin_f = 11;
int const pin_g = 12;

int d0 = 0;
int d1 = 0;
int d2 = 0;
int d3 = 0;

int ok = 1;

void setup() {
  pinMode(pin_d0, INPUT);
  pinMode(pin_d1, INPUT);
  pinMode(pin_d2, INPUT);
  pinMode(pin_d3, INPUT);

  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
  pinMode(pin_e, OUTPUT);
  pinMode(pin_f, OUTPUT);
  pinMode(pin_g, OUTPUT);
}

void loop() {
  if (digitalRead(pin_d0) == HIGH && ok){
      d0 = !d0;
      ok = 0;
  }
  if (digitalRead(pin_d1) == HIGH && ok){
      d1 = !d1;
      ok = 0;
  }
  if (digitalRead(pin_d2) == HIGH && ok){
      d2 = !d2;
      ok = 0;
  }
  if (digitalRead(pin_d3) == HIGH && ok){
      d3 = !d3;
      ok = 0;
  }

  if (digitalRead(pin_d0) == LOW && digitalRead(pin_d1) == LOW && digitalRead(pin_d2) == LOW && digitalRead(pin_d3) == LOW){
    ok = 1;
  }

  int a = !d0 && !d1 && !d2 || !d0 && d2 && d3 || !d1 && !d2 && d3 || d0 && d2 && !d3 || d1 && !d3 || d1 && d2 || !d0 && !d2;
  int b = !d0 && !d1 && !d3 || d0 && d1 && !d3 || d0 && !d1 && d3 || !d0 && !d2 || !d2 && !d3;
  int c = !d1 && !d2 || d0 && !d2 || d0 && !d1 || !d2 && d3 || d2 && !d3;
  int d = !d0 && !d1 && !d2 || !d0 && d2 && d3 || !d0 && d1 && d2 || d1 && !d2 && !d3 || d0 && d1 && !d2 || d0 && !d2 && d3 || d0 && !d1 && d2;
  int e = !d0 && !d2 || d1 && d3|| !d0 && d1 || d2 && d3;
  int f = !d1 && d2 && !d3 || d1 && d3 || !d0 && d2 || !d0 && !d1 || !d2 && d3;
  int g = !d1 && d2 && !d3 || d0 && !d1 && d2 || d1 && !d2 || d1 && d3 || !d0 && d1 || !d2 && d3;

  if (a){
    digitalWrite(pin_a,HIGH);
  }
  else{
    digitalWrite(pin_a,LOW);
  }

  if (b){
    digitalWrite(pin_b,HIGH);
  }
  else{
    digitalWrite(pin_b,LOW);
  }

  if (c){
    digitalWrite(pin_c,HIGH);
  }
  else{
    digitalWrite(pin_c,LOW);
  }

  if (d){
    digitalWrite(pin_d,HIGH);
  }
  else{
    digitalWrite(pin_d,LOW);
  }

  if (e){
    digitalWrite(pin_e,HIGH);
  }
  else{
    digitalWrite(pin_e,LOW);
  }

  if (f){
    digitalWrite(pin_f,HIGH);
  }
  else{
    digitalWrite(pin_f,LOW);
  }

  if (g){
    digitalWrite(pin_g,HIGH);
  }
  else{
    digitalWrite(pin_g,LOW);
  }

  delay(30);
}
