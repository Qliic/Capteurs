#include <Wire.h>

//lcd include
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {

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

}


void detect_I2C() {
  byte error, address;
  int nDevices;
  nDevices = 0;

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
      }
      
      if (address == 0x05) {
        Serial.println("@ ATtiny85-test");
      }
      
      if (address == 0x1E) {
        Serial.println("@ magnetometre-HMC5883");
      }
      
      if (address == 0x27) {
        Serial.println("@ ecran-LCD1602");
      }
      
      if (address == 0x29) {
        Serial.println("@ couleur-TCS34725");
      }
      
      if (address == 0x68) {
        Serial.println("@ gyroscope-MPU6050");
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


void loop() {

  detect_I2C();

  Wire.beginTransmission(5);
  Wire.write(0);
  Wire.endTransmission();

  read();
  read();
    
  delay(1000);

  Wire.beginTransmission(5);
  Wire.write(3);
  Wire.endTransmission();

  read();
  read();
  read();
  read();
  read();
  read();
    
  delay(1000);
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

