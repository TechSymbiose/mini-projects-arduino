/*  Code written by Adrien Louvrier, 07/01/2021
 *  Objective : display the tempereture measure on a LCD display
 * Card used : Mega 2560
 * Electronic Circuit : 
 * input : 
 *  - DHT11 temperature sensor (DHTPIN -> 53, Vcc -> 5V, grd -> grd)
 * output : 
 *  - LCD display (rs -> 2, en -> 3, d4 -> 4, d5 -> 5, d6 -> 6, d7 -> 7)
 */

#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN 53
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned int long timerMesure;
int temperatureValue;
int humidityValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(DHTPIN, INPUT);
  Serial.begin(9600);
  timerMesure = millis();
  dht.begin();
  temperatureValue = dht.readTemperature();
  humidityValue = dht.readHumidity();
  lcd.begin(16,2);
  lcd.display();
}

void loop() {
  if (millis() - timerMesure > 2000){
    timerMesure = millis();
    temperatureValue = dht.readTemperature();
    humidityValue = dht.readHumidity();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp : ");
    lcd.print(temperatureValue);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Humidity : ");
    lcd.print(humidityValue);
    lcd.print("%");
    Serial.print("Température : ");
    Serial.print(temperatureValue);
    Serial.println("C°");
    Serial.print("Humidité : ");
    Serial.print(humidityValue);
    Serial.println("%");
  }
}
