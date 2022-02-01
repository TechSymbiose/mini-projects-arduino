# **leds Matrix Digicode Control**

Code written by Adrien Louvrier, 08/01/2021

 *Objective* : display on a leds matrix what the user is typing on the digicode

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Mega 2560 | 1
digicole | 1
1088AS leds matrix | 1

input : 
- a digicode (line0 -> pin 39, line1 -> pin 37, line2 -> pin 35, line3 -> pin 33, column0 -> pin 29, column1 -> pin 27, column2 -> 25, column3 -> 23)
	
output : 
- a 1088AS leds matrix connected to pins 49, 51, 53, 5V and grd

**Note** : the functions used weren't written by me