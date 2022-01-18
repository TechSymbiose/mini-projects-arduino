/* Code written by Adrien Louvrier, 25/12/2020
 * Objective : control leds with a photoresistor
 * Card used : Arudino Uno
 * 
 * Electronic circuit :
 * input :
 *  - Photoresistor with 10kOhms in parallel connected to pin A0, 5V and grd
 * output :
 *  - 5 leds with 330 Ohms resistors connected to pin 2, 4, 6, 8, 10 and grd
 */

#define photoresistorPin A0

const int leds[]= {2, 4, 6, 8, 10};

void setup() {
  // Put leds pins in output mode
  for (int i = 0; i<5; ++i){
    pinMode(leds[i], OUTPUT);
  }

}

void loop() {
  int photoresistorValue = analogRead(A0);
  photoresistorValue = map(photoresistorValue, 0, 900, 0, 4);
  for (int i = 0; i<5; ++i){
    if (i == photoresistorValue){
      digitalWrite(leds[i], HIGH);
    }
    else{
      digitalWrite(leds[i], LOW);
    }
  }
}
