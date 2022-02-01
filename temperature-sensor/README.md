# **Temperature indicator	**

Code written by Adrien Louvrier, 13/01/2021

*Objective* : display the tempereture measure on a 4x7 segments display

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Mega 2560 | 1
DHT11 sensor | 1
4*7 segments display | 1
330 Ohms resistor | 12

*input* : 
- DHT11 temperature sensor (DHTPIN -> 53, Vcc -> 5V, grd -> grd)

*output* : 
 - 4x7 segments display (a -> 45, b -> 43, c -> 41, d -> 39, e > 37, f -> 35, g -> 33, point -> 32, digit1 -> 29, digit2 -> 27, digit3 -> 25, digit4 -> 23)