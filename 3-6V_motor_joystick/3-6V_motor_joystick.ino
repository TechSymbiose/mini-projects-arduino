// Code written by : Adrien Louvrier, 28/12/2020
// Objective : control of the speed of a 3-6V motor with a joystick

 #define joystickPin A0
 #define motorPin 3

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int joystickValue = analogRead(joystickPin);
  // Mapping of the x values of the joystickValue to control the motor from 0 to 255 
  joystickValue = map(joystickValue, 507, 1023, 0, 255);
  analogWrite(motorPin, joystickValue);
  Serial.println(joystickValue);
  delay(15);
}
