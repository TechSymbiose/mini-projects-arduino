# **RGB led control**

Code written by Adrien Louvrier, 27/12/2020

*Objective* : control a rgb led with a joystick and an encoder

Card used : Arduino Uno

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
joystick | 1
encoder | 1
rgb led | 1
red led | 1
green led | 1
blue led | 1
330 Ohms resistor | 6

*input* : 
 - A joystick connected to pins A1, 5V and grd
 - An encoder (output A -> pin 4, output B -> pin 2)

*output* : 
 - 3 leds (red led, green led and blue led) with 330 Ohms resistors in serial connected to pins 8, 9, 10 and grd
 - An RGB led with 330 Ohms resitor in serial (red pin -> pin 6, green pin -> pin 5, blue pin -> pin 3, grd pin -> grd)