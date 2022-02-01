# **Ultrasonic Sensor Meter with LCD Screen**

Code written by Adrien Louvrier, 08/01/2021

*Objective* : Print on a LCD display the distance measured by the ultrasonic sensor

Card used : Arduino Mega 2560

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Uno | 1
Ultrasonic sensor | 1
lcd screen | 1

*input* : 
 - Ultrasonic sensor (trig pin -> A0, echo pin ->A1, Vcc pin -> 5V, grd pin -> grd)

*output* : 
-lcd display (rs -> 45, en -> 43, d4 -> 41, d5 -> 39, d6 -> 37, d-> 35, Vcc -> 5V, grd -> grd)