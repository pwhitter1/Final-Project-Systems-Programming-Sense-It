#include <Wire.h>
  
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x1D);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(0x1D);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(0x1D,2);
  long xl = Wire.read();
  long xh = Wire.read();
  int x = xh <<8;
  x = x|xl;
  Serial.println(x);
  if(x > 30 || x < 10){
    Serial.println("Accelerometer works!");
  }
}
