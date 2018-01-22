# nano-i2c-scan-log.ino
# by Francois Belleau
#include <Wire.h>

//lcd include
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "Adafruit_TCS34725.h"
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

#include <Servo.h>
Servo servo;
int servo_pos;

int rg,gg,bg;

#include <Adafruit_NeoPixel.h>
#define PIN            4
#define NUMPIXELS      3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

boolean sr04 = false;
boolean analog10k = false;
boolean mpu6050 = false;
boolean attiny85_4 = false;
boolean tcs34725 = false;
boolean hmc5883 = false;

void detect_I2C() {
  
  byte error, address;
  int nDevices;
  nDevices = 0;

  lcd.clear();

  for (address = 1; address < 127; address++ )  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0){
      Serial.print("0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.print(" ");

      nDevices++;

      if (address == 0x04) {
        Serial.println("@ ATtiny85-SR04");
        sr04 = true;
        lcd.clear();
        lcd.print("ATtiny85-SR04");
        delay(1000);
      }
      
      if (address == 0x05) {
        Serial.println("@ ATtiny85-analog10k");
        analog10k = true;
        lcd.clear();
        lcd.print("ATtiny85-analog10k");
        delay(1000);
      }
      
      if (address == 0x1E) {
        Serial.println("@ magnetometre-HMC5883");
        hmc5883 = true;
        lcd.clear();
        lcd.print("magnetometre-HMC5883");
        delay(1000);
      }
      
      if (address == 0x27) {
        Serial.println("@ ecran-LCD1602");
        lcd.clear();
        lcd.print("ecran-LCD1602");
        delay(1000);
      }
      
      if (address == 0x29) {
        Serial.println("@ couleur-TCS34725");
        tcs34725 = true;
        lcd.clear();
        lcd.print("couleur-TCS34725");
        delay(1000);
      }
      
      if (address == 0x68) {
        Serial.println("@ gyroscope-MPU6050");
        mpu6050 = true;
        lcd.clear();
        lcd.print("gyroscope-MPU6050");
        delay(1000);
      }
      
    } else if (error == 4) {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found");

  Serial.println("");
}

String read_tcs34725() {
  uint16_t r, g, b, c, colorTemp, lux;
  char json[200];
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  //Serial.print(r, DEC); Serial.print(" ");
  //Serial.print(g, DEC); Serial.print(" ");
  //Serial.print(b, DEC); Serial.print(" ");
  //Serial.print(c, DEC); Serial.print(" ");
  //Serial.println(" ");
  
  //snprintf (json, 200, "{\"tcs34725\":{\"CT\":%ld,\"Lux\":%ld,\"R\":%ld,\"G\":%ld,\"B\":%ld,\"C\":%ld}}", colorTemp, lux, r, g, b, c);
  snprintf (json, 200, "R:%d G:%d B:%d", r, g, b);
  Serial.println(json);

  rg = r;
  gg = g;
  bg = b;
  
  return json;
}

String read_mpu6050() {
  const int MPU_addr=0x68;  // I2C address of the MPU-6050
  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
  size_t st;
  char json[200];
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14);  // request a total of 14 registers
  //st = Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //Serial.print("MPU6050: "); 
  //Serial.print("AcX = "); Serial.print(AcX);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  //Serial.print(" | GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ);

  int degre = map((AcZ/128),-140,140,20,160);
  
  snprintf (json, 200, "x:%i y:%i z:%i", AcX/128, AcY/128, AcZ/128);
  //Serial.println(json);

  //servo_pos = degre;
  //Serial.println(servo_pos);

  return json;
}

String read_hmc5883(){
    
  const int address=0x1E;
  int x,y,z; //triple axis data
  int xmin,xmax,ymin,ymax,zmin,zmax;
  xmin=0; xmax=0; ymax=0; ymin = 0; zmin=0;zmax=0;

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    z = -z; //inversion du module
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  //Print out values of each axis
  //Serial.print("x: ");Serial.print(x);Serial.print("  y: ");Serial.print(y);Serial.print("  z: ");Serial.println(z);
  

    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(y, x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  //Serial.println(headingDegrees);

  int degre = (int) headingDegrees;
  servo_pos = (degre/2);
  //Serial.println(servo_pos);

  char buf[80];
  sprintf(buf,"D:%i",(int) degre);
  return buf;

}

void read() {
  int i2c;
  char buf[8];

  Wire.requestFrom(5, 1); // request 1 byte from slave device address 4
  i2c = Wire.read();

  sprintf(buf,"i2c #5: %i",i2c);
  Serial.println(buf);
  lcd.clear();
  lcd.print(buf);
  delay(300);
}

void setup() {
// servo setup
  servo.attach(5);
  
// ws2812 setup
  pixels.begin();
  
// lcd setup
  lcd.init();
  lcd.backlight();
  
//serial_setup
  Serial.begin(115200);
  while (!Serial);

//wire_setup
  //Arduino Uno, Nano
  Wire.begin();
  Serial.println("Scanning (SDA : SCL) - A4 A5");
  //ESP8266
  //Wire.begin(5,4);
  //Serial.println("Scanning (SDA : SCL) - GPIO5 GPIO4");

//mpu6050 setup
  const int MPU_addr=0x68;  // I2C address of the MPU-6050

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //Put the HMC5883 IC into the correct operating mode
  const int address=0x1E;
  
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
  
detect_I2C();
}


void loop() {
  String read_string;
  int distance;
  char buffer[80];
  
//detect_I2C();
//delay(1000);

if (hmc5883) {
  read_string = read_hmc5883();

  servo.write(servo_pos);
  delay(15);

  Serial.println(read_string);
  lcd.clear();
  lcd.print(read_string);
  delay(1000);
}

if (tcs34725) {
  read_string = read_tcs34725();

  Serial.println(read_string);
  lcd.clear();
  lcd.print(read_string);
  delay(1000);

  //pixels.setPixelColor(0, pixels.Color(rg,gg,bg));
  //pixels.show();

}

if (mpu6050) {
  read_string = read_mpu6050();

  servo.write(servo_pos);
  delay(15);

  Serial.println(read_string);
  lcd.clear();
  lcd.print(read_string);
  delay(1000);
}

if (sr04) {
  Wire.requestFrom(4, 1); // request 1 byte from slave device address 4
 
  while(Wire.available()) // slave may send less than requested
  {
    distance = Wire.read(); // receive a byte as character
    sprintf(buffer,"Distance:%i",(int) distance);
  
    //Serial.println(i); // print the character
    Serial.println(buffer);
    lcd.clear();
    lcd.print(buffer);
    delay(1000);
  }
}
      
if (analog10k) {
  Wire.requestFrom(5, 1); // request 1 byte from slave device address 4
 
  while(Wire.available()) // slave may send less than requested
  {
    distance = Wire.read(); // receive a byte as character
    sprintf(buffer,"Valeur:%i",(int) distance);
  
    //Serial.println(i); // print the character
    Serial.println(buffer);
    lcd.clear();
    lcd.print(buffer);
    delay(1000);
  }   
}

}

