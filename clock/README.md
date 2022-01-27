# Clock

Project done by Adrien Louvrier, 01/02/2021
The goal is make a clock and print the date and time on a LCD screen, on screen and on a 4x7 segments display
Card used : Arduino Mega 2560

# Electronic circuit
input : 
	- RTC module (Vcc -> 5V, grd -> grd, SDA -> SDA, SCL -> SCL, SQW -> pin 3)
	
output : 
	- 4x7 segments display with 330 Ohms resistance on each segments
	(a -> 51, b -> 43, c -> 46, d -> 50, e -> 52, f -> 49, g -> 44, point -> 48, digit1 -> 53, digit2 -> 47, digit3 -> 45, digit4 -> 42)
		
	- LCD screen (rs -> 32, en -> 30, d4 -> 28, d5 -> 26, d6 -> 24, d7 -> 22, Vcc -> 5V, grd -> grd)