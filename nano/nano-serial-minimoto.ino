# nano-serial-minimoto.ino
# by Francois Belleau

#include <Wire.h>

#include <SparkFunMiniMoto.h>  // Include the MiniMoto library


// Create two MiniMoto instances, with different address settings.
  MiniMoto motor0(0xC4); 
  MiniMoto motor1(0xC0);
  
char receivedChar;
boolean newData = false;

void setup() {
 Serial.begin(115200);
 Serial.println("<Arduino is ready>");

 Wire.begin();
 i2c_scanner(); 
}

int speed = 60;

void loop() {

  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    Serial.print("car:");
    Serial.println(receivedChar);
    switch (receivedChar) {
    case 49 :
      Serial.println("1");
      speed = 10;
      break;
    case 50 :
      Serial.println("2");
      speed = 20;
      break;
    case 51 :
      Serial.println("3");
      speed = 30;
      break;
    case 52 :
      Serial.println("4");
      speed = 40;
      break;
    case 53 :
      Serial.println("5");
      speed = 50;
      break;
    case 54 :
      Serial.println("6");
      speed = 60;
      break;
    case 97 :
      Serial.println("avancer");
      motor0.drive(speed);
      motor1.drive(speed);
      delay(500);
      motor0.stop();
      motor1.stop();
      break;
    case 114 :
      Serial.println("reculer");
      motor0.drive(-speed);
      motor1.drive(-speed);
      delay(500);
      motor0.stop();
      motor1.stop();
      break;
    case 103 :
      Serial.println("gauche");
      Serial.println("avancer");
      motor0.drive(speed);
      motor1.drive(-speed);
      delay(500);
      motor0.brake();
      motor1.brake();
      break;
    case 100 :
      Serial.println("droite");
      Serial.println("avancer");
      motor0.drive(-speed);
      motor1.drive(speed);
      delay(500);
      motor0.brake();
      motor1.brake();
      break;
    default :  ;
    }
  }

}

void i2c_scanner()
{
  byte error, address;
  int nDevices;
 
  Serial.println("\nI2C Scanner");
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address:");
      Serial.println(address,DEC);
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}
