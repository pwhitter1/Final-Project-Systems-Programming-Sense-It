#include <SoftwareSerial.h>  
#include <Wire.h>
#include <Keypad.h>
#include "Adafruit_TCS34725.h"


//Software Serial
int myTxPin = 6;  
int myRxPin = 5; 
int counter = 0;

SoftwareSerial softSerial(myRxPin, myTxPin);

//Color sensor
#define redpin 3
#define greenpin 5
#define bluepin 6
#define commonAnode true

byte gammatable[256]; 

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

//Force Sensitive Resistor
int fsrAnalogPin = 3; 
int fsrReading;     
int prevReading = 3000;
int callnum = 0;


//Keypad
const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2','3'},
  {'4','5','6'},
  {'7','8','9'},  
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 8, 3, 2}; 
byte colPins[COLS] = {4, 5, 6}; 


Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup(){
  accelerometerSetup();
  colorviewSetup();
  forceResistorSetup();
  keypadSetup();
  Serial.begin(9600);
}


void accelerometerSetup() {  
  softSerial.begin(9600); 
  Wire.begin();
  Wire.beginTransmission(0x1D);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  Wire.begin();
}

void colorviewSetup() {
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    Serial.println(gammatable[i]);
  }
}


void forceResistorSetup() {
  //empty purposely  
}

void keypadSetup(){ 
  //empty purposely
}

void accelerometerLoop() {
  Wire.beginTransmission(0x1D);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(0x1D,2);
  long xl = Wire.read();
  long xh = Wire.read();
  int x = xh <<8;
  x = x|xl;
  Serial.println(x);
  if(x > 10){
    softSerial.print(0);
  }

    softSerial.print( ++counter );
    delay(500);
}


void colorviewLoop() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      

  delay(200); 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true); 
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  //ARBITRARY VALUES
  if(r > 100 && g > 100 && b > 100){
    softSerial.print(1);
  }

    softSerial.print( ++counter );
    delay(500);
}

void forceResistorLoop() {
   fsrReading = analogRead(fsrAnalogPin);
  Serial.println(fsrReading);
  if(fsrReading > prevReading+5){
    prevReading = fsrReading;
    softSerial.print(2);
  }

  softSerial.print( ++counter );
  delay(500);
  prevReading = fsrReading;
}


void keypadLoop() {
   //ONLY KEY #1 WORKS
  char customKey = customKeypad.getKey();
  if(customKey){
    softSerial.print(3);
  }
  
  softSerial.print( ++counter );
  delay(500);
}


void loop(){
  accelerometerLoop();
  colorviewLoop();
  forceResistorLoop();
  keypadLoop();
}
