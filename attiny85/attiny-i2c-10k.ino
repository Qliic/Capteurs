# attiny-i2c-10k.ino
# by Francois Belleau

// Code for the ATtiny85

//const i2c
#define I2C_SLAVE_ADDRESS 0x5 // Address of the slave
 
#include <TinyWireS.h>

//const analog
const int analogPin = 3;  // pin "trig" branchée à la broche 2 de l'ATTiny85
const int ledPin = 0;      // LED rouge branchée à la broche 7 de l'ATTiny85

int sensorValue;
   
void setup()
{
//setup i2c
  TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
  TinyWireS.onRequest(requestEvent);
 
// setup analog
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

int readAnalog ()
{ 
  return map(analogRead(analogPin),0,1024,0,255);
}

void loop()
{
  TinyWireS_stop_check();
  
  sensorValue = readAnalog();

  //digitalWrite(ledPin, HIGH);
  //delay(sensorValue);
  //digitalWrite(ledPin, LOW);
  //delay(sensorValue);
  
}
 
// Gets called when the ATtiny receives an i2c request
void requestEvent()
{
    TinyWireS.send(sensorValue);
    //distance ++;
    
}
