/* Objectif : utiliser un capteur ultrasonic pour connaître et afficher des distances
 *  
 *  Date de création : 26/12/2020
 *  Auteur : Adrien Louvrier
 *  Circuit : 
 *  - un capteur ultrasonic connecté aux pins 8 et 10
 *  - 3 leds + résistances 330 Ohms connectées aux pins 2, 4 et 6
 */

#define trigPin A0 // ultrasonic sensor pins
#define echoPin A1

long duration; // Duration of one measurement
int distance; // Distance calculated

#define led1Pin 2 // leds pins
#define led2Pin 4
#define led3Pin 6

void setup() {
  pinMode(trigPin, OUTPUT); // Setup the ultrasonic sensor pins
  pinMode(echoPin, INPUT);

  pinMode(led1Pin, OUTPUT); // Setup leds pin to output mode
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
}

void loop() {
  // Measure the duration between emitting and receiving
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2; // Calculation of the distance with the formula d=v*t

  // Turn on the led 1 if the distance is under cm
  if (distance < 5){
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
  }

  // Turn on the led 2 if the distance is between 5 and 10 cm
  if (distance >= 5 && distance < 10){
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, LOW);
  }

  // Turn on the led 3 if the distance is above 10 cm
  if (distance > 10){
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
  }
}
