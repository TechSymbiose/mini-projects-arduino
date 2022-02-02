# **led **

Code written by Adrien Louvrier

*Objective* : control a led using RF communication

Card used : Arduino Nano

# Electronic circuit

## **List of the components**

Component | Quantity 
----------|----------
Arduino Nano | 1
button | 1
10kOhms resistor | 1
led | 1
330 Ohms resistor | 1
NRF24L01+LNA module | 1

*input* : 
- button connected with 10kOhms in parallel connected to pin 4, 5V and grd
- NRF24L01+LNA module (pin CE -> pin 9, pin CSN -> pin 10, MOSI -> pin 11, pin MISO -> pin 12, pin SCK -> pin 13, pin Vcc -> 5V, pin grd -> grd) (channel 00002)

*output* : 
- led with 330 Ohms resistor connected to pin 6 and grd
- NRF24L01+LNA module (pin CE -> pin 9, pin CSN -> pin 10, MOSI -> pin 11, pin MISO -> pin 12, pin SCK -> pin 13, pin Vcc -> 5V, pin grd -> grd) (channel 00001)
