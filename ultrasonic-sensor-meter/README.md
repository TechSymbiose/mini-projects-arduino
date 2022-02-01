# **Ultrasonic Sensor Meter**

Code written by Adrien Louvrier, 13/01/2021

*Objective* : Indicate the distance measured by an ultrasonic sensor with leds

Card used : Arduino Uno

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
Ultrasonic sensor | 1
led | 3
330 Ohms resistor | 3

*input* : 
- An ultrasonic sensor (trig pin -> pin A0, echo pin -> pin A1)

*output* : 
- 3 leds with a 330 Ohms resistors in serial connected to pins 2, 4, 6 and grd