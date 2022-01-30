/* Code written by Adrien Louvrier, 07/01/2021

 * Objective : display the tempereture measure on a LCD display
 * Card used : Mega 2560
 * 
 * Electronic Circuit : 
 * input : 
 *  - DHT11 temperature sensor (DHTPIN -> 53, Vcc -> 5V, grd -> grd)
 * 
 * output : 
 *  - LCD display (rs -> 2, en -> 3, d4 -> 4, d5 -> 5, d6 -> 6, d7 -> 7)
 */

#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN 53 // Temperature sensor pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // Declaration of lcd screen pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned int long timerMeasure; // timer between two measurements
int temperatureValue;
int humidityValue;

void setup() {
  pinMode(DHTPIN, INPUT);

  // Init the temperature and humidity sensor
  timerMeasure = millis();
  dht.begin();
  temperatureValue = dht.readTemperature();
  humidityValue = dht.readHumidity();

  // Init the lcd screen
  lcd.begin(16,2);
  lcd.display();
}

void loop() {
  // Read the temperature and humidity values of the sensor every 2 seconds
  if (millis() - timerMeasure > 2000) {
    timerMeasure = millis(); // reset the timer
    temperatureValue = dht.readTemperature();
    humidityValue = dht.readHumidity();

    // Display the values on the lcd screen
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp : ");
    lcd.print(temperatureValue);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Humidity : ");
    lcd.print(humidityValue);
    lcd.print("%");
  }
}
