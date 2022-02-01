# **4 bits 7 segments display**

Code written by Adrien Louvrier, 22/12/2020

*Objective* : use a 74HC595 IC registers to turn on leds

*Card used* : Arduino Uno

# **Electronic circuit**

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
74HC595 IC registers | 1
leds | 8
330 Ohms resistors | 8

### *input* : none

### *output* :
- a 74HC595 register connected to pins 8, 9 and 10, 5V and grd
- 8 leds with résistors connected to the register and grd

**Note** : the writeRegisters, setRegisterPin and clearRegisters weren't written by me