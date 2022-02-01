# **Water Level Indicator**

Code written by Adrien Louvrier, 14/01/2021

*Objective* : Turn on leds according to the level of water
 * Card used : Arduino Uno

Card used : Arduino UNo

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
water level sensor | 1
red led | 1
yellow led | 1
green led | 1
330 Ohms resistor | 3

*input* : 
- water level sensor (S -> A0, Vcc -> 5V, grd -> grd)

*output* : 
- red led with 330 Omhs resistance (Vcc -> 2, grd -> grd)
- yellow led with 330 Omhs resistance (Vcc -> 3, grd -> grd)
- green led with 330 Omhs resistance (Vcc -> 4, grd -> grd)
