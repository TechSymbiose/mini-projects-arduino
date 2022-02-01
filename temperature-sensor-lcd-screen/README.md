# **Temperature indicator with lcd screen display**

Code written by Adrien Louvrier, 13/01/2021

*Objective* : display the tempereture measured on a LCD display

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Mega 2560 | 1
DHT11 sensor | 1
lcd screen | 1

*input* : 
- DHT11 temperature sensor (DHTPIN -> 53, Vcc -> 5V, grd -> grd)

*output* : 
- LCD display (rs -> 2, en -> 3, d4 -> 4, d5 -> 5, d6 -> 6, d7 -> 7)
