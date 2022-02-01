# **Chronometer with registers**

Code written by Adrien Louvrier, 31/12/2020

*Objective* : implement a chronometer which can be turn on by a buttonPin and paused by pressing this buttonPin

card used : Arduino Uno

# **Electronic circuit**

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
4x7 segments display | 1
330 resistor resistor | 12
Button | 1
10kOhms resistor | 1

### *input* : 
- Button connected to pin A0, 5V and grd
- 10kOhms resistor connected to pin A0 and grd
	
### *output* : 
- 4x7 segments display with 330 Omhs resistances (segments connected to pins 2 to 8, point -> 9, digit4 -> 10, digit1 -> 11, digit2 -> 12, digit0 -> 13)
