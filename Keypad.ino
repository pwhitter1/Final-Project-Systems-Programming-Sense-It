#include <Wire.h>
//#include "RTC.h"
//#include <LiquidCrystal.h>
#include <Keypad.h>

//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

//Wire.begin();
//setRtcTime(0, 35, 11, 3, 23, 2, 16); //the current time

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2','3'},
  {'4','5','6'},
  {'7','8','9'},  //USE THE NUMBER "ONE" ONLY
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 5, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}




