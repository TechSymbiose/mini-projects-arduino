# **Two Axis Angle**

Code written by Adrien Louvrier, 25/12/2020

*Objective* : Make a 2 axis angle using an accelerometer

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
accelerometer | 1
led | 10
330 Ohms resistor | 10
lcd screen | 1

*input* : 
 - An accelerometer connected to 5V, grd, SCL and SDA

*output* : 
 - 10 leds with 330 Ohms resistors connected to pins 36, 38, 40, 42, 44, 48, 19, 50, 53, 52 and grd
 - A lcd screen connected (rs -> pin 45, en -> pin 43, d4 -> pin 41, d5 -> pin 39, d6 -> pin 37, d7 -> pin 35, vcc -> 5V, grd -> grd)

 **Note** : The convert_int16_to_str function wasn't written by me
