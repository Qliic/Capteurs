/*******************ULTRASONS HC-SR04*************************
   Démonstration de l'utilisation du module à  ultrasons HC-SR04
   avec un ATTiny.  3 LEDs (rouge, jaune, verte) indiquent si
   l'obstacle est loin ou proche.
   http://electroniqueamateur.blogspot.com
 **************************************************************/

// http://electroniqueamateur.blogspot.ca/2017/10/telemetre-hc-sr04-et-attiny85.html

// const sr04
const int trigPin = 3;  // pin "trig" branchée à la broche 2 de l'ATTiny85
const int echoPin = 4;  //pin "echo" branchée à la broche 3 de l'ATTiny85
const int LED = 0; // LED rouge branchée à la broche 7 de l'ATTiny85

void setup() {

// setup sr04
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(trigPin, LOW);
}

long sr04 ()
{
  long temps, distance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  temps = pulseIn(echoPin, HIGH);
  distance = temps * 340/(2*10000);
  
  return distance;
}

void loop()
{
  long distance;

  distance = sr04();

  if (distance <= 30) {
    digitalWrite(LED, HIGH);
    delay(distance * 10);
    digitalWrite(LED, LOW);
    delay(distance * 10);
  }

}
