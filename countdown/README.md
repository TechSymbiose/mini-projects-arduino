# **Countdown**

Code written by Adrien Louvrier, 04/01/2021

 *Objective* : make a countdown of one minute we can trigger by pressing a button

Card used : Arduino Uno

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
button | 1
10kOhms resistor | 1
4*7 segments display | 1
330 Ohms resistors | 12

*input* : 
- a button connected to pin 12, 5V and grd with a 10kOhms resistor in parallel connected to grd
	
*output* : 
- 4x7 segments display (a to g -> pins 2 to 8, point -> 9, digit 1 to 4 -> pins 10 to 13) with 330 Ohms resistor connected to each pin