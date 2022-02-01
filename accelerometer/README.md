# **4 bits 7 segments display**

Code written by : Adrien Louvrier, 30/01/2021

*Objective* : control a leds matrix with an accelerometer

*Card used* : Arduino Uno

# **Electronic circuit**

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
GY-521 MPU-6050 accelerometer | 1
leds matrix | 1
leds | 4
330 Ohms resistors | 4

### *input* :
- an accelerometer connected to 5V, grd, SCL and SDA

### *output* :
- A leds matrix connected to 5V, grd, pins 8, 9 and 10
- 4 leds with 330 Ohms resistors in serial connected to pins 2, 3, 4, 5 and grd

**Note** : Note : the following functions weren't written by me : convert_int16_to_str, writeLine, writeMatrix, init_1088AS, clearMatrix