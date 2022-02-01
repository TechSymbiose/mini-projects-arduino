# **RFID Access Control**

Code written by Adrien Louvrier, 25/12/2020

*Objective* : Make an RFID access control turning on the red led when putting the card, turning on the green led and playing music when putting the badge

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Mega 2560 | 1
RFID reader | 1
buzzer | 10
red led | 1
green led | 1
330 Ohms resistor | 2

*input* : 
- A RFID reader (RST -> pin 23, SS -> pin 25)

*output* : 
 - A buzzer connected to pin 45
 - A red led with 330 Ohms resistor connected to pin 8 and grd
 - A green led with 330 Ohms resistor connected to pin 9 and grd