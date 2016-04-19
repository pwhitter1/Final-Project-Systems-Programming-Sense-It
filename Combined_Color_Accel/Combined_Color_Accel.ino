#include <Wire.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include "Adafruit_TCS34725.h"

#define ADXL_I2C_ADDR 0x1D
#define DATAX0_ADDR 0x32

//Accelerometer
int x, y, z; 
char toPrint[50]; // Formatted accelerometer output

//Color sensor
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

//Software Serial
int myTxPin = 5;  // Chosen pin for transmitting data
int myRxPin = 6;  // Chosen pin for receiving data
// Create software serial object
SoftwareSerial softSerial(myRxPin, myTxPin); // Format is (RX pin, TX, pin)

//Keypad
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2','3'},
  {'4','5','6'},
  {'7','8','9'},  
  {'*','0','#'}
};
byte rowPins[ROWS] = {7}; 
byte colPins[COLS] = {4}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Force Sensitive Resistor
int fsrAnalogPin = 3; 
int fsrReading;     
int prevReading = 3000;
int callnum = 0;

//SD card
File fd;
const uint8_t BUFFER_SIZE = 20;
char fileName[] = "demoFile.txt"; // SD library only supports up to 8.3 names
char buff[BUFFER_SIZE+2] = "";  // Added two to allow a 2 char peek for EOF state
uint8_t index = 0;
const uint8_t chipSelect = 8;
const uint8_t cardDetect = 9;
enum states: uint8_t { NORMAL, E, EO };
uint8_t state = NORMAL;
bool alreadyBegan = false;  // SD.begin() misbehaves if not first call



void setup() {
  
  Serial.begin(9600);
  softSerial.begin(9600);
  Wire.begin();
  
  //-----color sensor setup--------
  Serial.println("Color View Test!");
  if (tcs.begin()) {
    Serial.println("Found sensor");
   } else {
   Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  //gamma table to convert RGB colors
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
  }
  
  
  //------accelerometer setup---------
  Wire.beginTransmission(ADXL_I2C_ADDR);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();  


  //----SD Card setup---
  pinMode(cardDetect, INPUT);
  //initializeCard();
  
}

void SDCard(int score)
{
  Serial.print(F("Initializing SD card..."));

  // Is there even a card?
  if (!digitalRead(cardDetect))
  {
    Serial.println(F("No card detected. Waiting for card."));
    while (!digitalRead(cardDetect));
    delay(250); // 'Debounce insertion'
  }

  // Card seems to exist.  begin() returns failure
  // even if it worked if it's not the first call.
  if (!SD.begin(chipSelect) && !alreadyBegan)  // begin uses half-speed...
  {
    Serial.println(F("Initialization failed!"));
    SDCard(score); // Possible infinite retry loop is as valid as anything
  }
  else
  {
    alreadyBegan = true;
  }
  Serial.println(F("Initialization done."));

  Serial.print(fileName);
  if (SD.exists(fileName))
  {
    Serial.println(F(" exists."));
  }
  else
  {
    Serial.println(F(" doesn't exist. Creating."));
  }

  Serial.print("Opening file: ");
  Serial.println(fileName);

  //FILE WRITING
  fd = SD.open(fileName, FILE_WRITE);
  fd.write("score: ");
  char str[15];
  sprintf(str, "%d", score);
  fd.write(str);
  fd.flush();
  fd.close();

}




void loop() {
  
  //-------CHECK COLOR SENSOR--------
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);    
  delay(60);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  if(red < 300){
    softSerial.println(2);
  }
  //some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
  
  //-------CHECK ACCELEROMETER-------
  Wire.beginTransmission(ADXL_I2C_ADDR);
  Wire.write(DATAX0_ADDR);
  Wire.endTransmission();
  Wire.beginTransmission(ADXL_I2C_ADDR);
  Wire.requestFrom(ADXL_I2C_ADDR, 6);
  //LSB first
  x = Wire.read() | (((int)Wire.read()) << 8);
  y = Wire.read() | (((int)Wire.read()) << 8);
  z = Wire.read() | (((int)Wire.read()) << 8);
  Wire.endTransmission();
  sprintf(toPrint, "X: %8d\tY: %8d\tZ: %8d", x, y, z);
  Serial.println(toPrint);
  if(x > 40){
    Serial.println("SENT ONE!!!!!!!!!");
    softSerial.println(1);
  }

  //------CHECK KEYPAD--------
  char customKey = customKeypad.getKey();
  if(customKey){
    softSerial.println(4);
    Serial.println("keypad works");
  }


  //-------CHECK FSR----------
  fsrReading = analogRead(fsrAnalogPin);
  if(fsrReading > prevReading+5){
    prevReading = fsrReading;
    softSerial.println(3);
    Serial.println("force resistor works");
  }
  prevReading = fsrReading;


  int score = 0;

  if(softSerial.available()){
    score = softSerial.parseInt();
    if(score >= 1000){
      score = score / 1000;
      score = score - 1;
      Serial.print("SCORE SCORE SCORE:");
      Serial.println(score);
      SDCard(score);
    }
  }
  
  
  delay(250);
}
