#include <SoftwareServo.h>
#include <TinyWireS.h>


SoftwareServo servo1;

void setup()
{
//setup servo
  servo1.attach(1);
  servo1.setMaximumPulse(2200);

//setup i2c
  TinyWireS.begin(4); // join i2c network
  TinyWireS.onRequest(requestEvent);

}

// Gets called when the ATtiny receives an i2c request
void requestEvent()
{
    TinyWireS.send(distance);
}

void loop()
{
  static int value = 0;
  static char CurrentServo = 0;

  servo1.write(90);
  SoftwareServo::refresh();
  delay(500);
  
  servo1.write(120);
  SoftwareServo::refresh();
  delay(500);
  
}
