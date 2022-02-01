# **4 bits 7 segments display**

Code written by Adrien Louvrier, 22/12/2020

*Objective* : Enter a 4 bits number (from 0 to 15) thanks to 4 buttons (one button for each bit) and print this number on a 7 segments display.

*Card used* : Arduino Uno

# **Electronic circuit**

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
buttons | 4
10kOhms resistors | 4
7 segments display | 1
330 Ohms resistors | 7

### *input* :
- 4 buttons connected to Vcc and pins 2 to 5
- 4 10kOhms resistors connected to grd and pins 2 to 5

### *output* :
- A 7 segments display (with resistances 330 Ohms on each segment input) connected to grd and pins 6 to 12