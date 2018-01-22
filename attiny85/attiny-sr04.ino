# attiny-i2c-sr04.ino
# by Francois Belleau

// Code for the ATtiny85

//const i2c
#define I2C_SLAVE_ADDRESS 0x4 // Address of the slave
 
#include <TinyWireS.h>

//const sr04
const int trigPin = 3;  // pin "trig" branchée à la broche 2 de l'ATTiny85
const int echoPin = 4;  // pin "echo" branchée à la broche 3 de l'ATTiny85
const int LED = 0;      // LED rouge branchée à la broche 7 de l'ATTiny85

int i=0;
int distance;
   
void setup()
{
//setup i2c
TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
    TinyWireS.onRequest(requestEvent);
 
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
  TinyWireS_stop_check();
  
  distance = sr04();
}
 
// Gets called when the ATtiny receives an i2c request
void requestEvent()
{
    TinyWireS.send(distance);
    //distance ++;
    
}
