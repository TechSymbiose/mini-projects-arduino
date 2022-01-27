/* Code written by Adrien Louvrier, 25/12/2020
 * Objective : control leds with a potPinPinentiometer
 * Card used : Arudino Uno
 * 
 * Electronic circuit :
 * input :
 *  - Photoresistor with 10kOhms in parallel connected to pin A0, 5V and grd
 * output :
 *  - 5 leds with 330 Ohms resistors connected to pin 2, 4, 6, 8, 10 and grd
 */

#define potPin A0 // potentiometer pin

const int leds[]= {2, 4, 6, 8, 10}; // leds pins

void setup() {
  // Put leds pins in output mode
  for (int i = 0; i<5; ++i){
    pinMode(leds[i], OUTPUT);
  }

}

void loop() {
  // Reading the value of the potentiometer
  int potValue = analogRead(A0);

  // Mapping the value of the potentiometer from 1 to 675 to 0 to 4
  potValue = map(potValue, 1, 675, 0, 4);

  // Turn on and off leds according to the value of the potentiometer
  for (int i = 0; i<5; ++i){
    if (i == potValue){
      digitalWrite(leds[i], HIGH);
    }
    else{
      digitalWrite(leds[i], LOW);
    }
  }
}
