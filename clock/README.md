# **Clock**

Code written by Adrien Louvrier, 01/02/2021

*Objective* : make a clock and print the date and time on a LCD screen, on serial monitoring and on a 4x7 segments display 

Card used : Arduino Mega 2560

# Electronic circuit

Component | Quantity 
----------|----------
Arduino Uno | 1
4x7 segments display | 1
330 resistor resistor | 12
Button | 1
10kOhms resistor | 1

input : 
- RTC module (Vcc -> 5V, grd -> grd, SDA -> SDA, SCL -> SCL, SQW -> pin 3)
	
output : 
- 4x7 segments display with 330 Ohms resistance on each segments (a -> 51, b -> 43, c -> 46, d -> 50, e -> 52, f -> 49, g -> 44, point -> 48, digit1 -> 53, digit2 -> 47, digit3 -> 45, digit4 -> 42)
		
- LCD screen (rs -> 32, en -> 30, d4 -> 28, d5 -> 26, d6 -> 24, d7 -> 22, Vcc -> 5V, grd -> grd)