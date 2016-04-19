// Include the required Wire library for I2C<br>#include 
#include <Wire.h>

// Constants
const int TOUCH_BUTTON_PIN1 = 9;  // Input pin for touch state
const int TOUCH_BUTTON_PIN2 = 10;  // Input pin for touch state
const int TOUCH_BUTTON_PIN3 = 11;  // Input pin for touch state
const int TOUCH_BUTTON_PIN4 = 12;  // Input pin for touch state
int buttonState1 = 0;             // Variable for reading button1
int buttonState2 = 0;           
int buttonState3 = 0;            
int buttonState4 = 0; 
const int LED_PIN = 13;

int x = 0;




//RFID
//When you upload sketch, disconnect pin 0
int RFIDResetPin = 13;

//Register your RFID tags here
char tag1[13] = "2C0043256923";
/*char tag2[13] = "010230F28243";
char tag3[13] = "01023C013A04";
char tag4[13] = "01023101093A";
char tag5[13] = "01023C0A4376";
char tag6[13] = "01023C000E31";
char tag7[13] = "01023C0A3207";
char tag8[13] = "1A004116317C";
char tag9[13] = "1E009A81F9FC";
char tag10[13] = "1A004162261F";*/

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  pinMode(TOUCH_BUTTON_PIN1, INPUT);
  pinMode(TOUCH_BUTTON_PIN2, INPUT);
  pinMode(TOUCH_BUTTON_PIN3, INPUT);
  pinMode(TOUCH_BUTTON_PIN4, INPUT);

  //RFID may need more
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);

  Serial.begin(9600);

}

void loop() {
  
  buttonState1 = digitalRead(TOUCH_BUTTON_PIN1);
  buttonState2 = digitalRead(TOUCH_BUTTON_PIN2);
  buttonState3 = digitalRead(TOUCH_BUTTON_PIN3);
  buttonState4 = digitalRead(TOUCH_BUTTON_PIN4);

  Wire.beginTransmission(9); // transmit to device #9

  if(buttonState1 == HIGH){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("8");
      Wire.write(8); 
   }

   else if(buttonState2 == HIGH){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("9");
      Wire.write(9); 
    }

    else if(buttonState3 == HIGH){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("10");
      Wire.write(10); 
    }

   else if(buttonState4 == HIGH){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("11");
      Wire.write(11); 
    }

   else{
      Serial.println("0");
      Wire.write(0); 
      }
  
  //RFID------------------------------------
  char tagString[13];
  int index = 0;
  boolean reading = false;

  while(Serial.available()){

    int readByte = Serial.read(); //read next available byte

    if(readByte == 2) reading = true; //begining of tag
    if(readByte == 3) reading = false; //end of tag

    if(reading && readByte != 2 && readByte != 10 && readByte != 13){
      //store the tag
      tagString[index] = readByte;
      index ++;
    }
  }

  checkTag(tagString); //Check if it is a match
  //clearTag(tagString); //Clear the char of all value
  //resetReader(); //eset the RFID reader
 //-------------------------------------------------- 
  
  Wire.endTransmission();    // stop transmitting
  digitalWrite(LED_PIN, LOW);
  clearTag(tagString); //Clear the char of all value
  resetReader(); //eset the RFID reader
}


//RFID---------------------------------------------------

void checkTag(char tag[]){
///////////////////////////////////
//Check the read tag against known tags
///////////////////////////////////

  if(strlen(tag) == 0) return; //empty, no need to contunue

  /*if(compareTag(tag, tag1)){ // if matched tag1, do this
    lightLED(2);

  }else if(compareTag(tag, tag2)){ //if matched tag2, do this
    lightLED(3);

  }else if(compareTag(tag, tag3)){
    lightLED(4);

  }else if(compareTag(tag, tag4)){
    lightLED(5);

  }else if(compareTag(tag, tag5)){
    lightLED(6);

  }else if(compareTag(tag, tag6)){
    lightLED(7);

  }else if(compareTag(tag, tag7)){
    lightLED(8);

  }else if(compareTag(tag, tag8)){
    lightLED(9);

  }else if(compareTag(tag, tag9)){
    lightLED(10);

  }else if(compareTag(tag, tag10)){
    lightLED(11);

  }else{*/
    Serial.println(tag); //read out any unknown tag
    
  if(compareTag(tag, tag1)){
      Serial.println("5");
      Wire.write(5);
       Wire.write(5);
        Wire.write(5);
  }

}

/*void lightLED(int pin){
///////////////////////////////////
//Turn on LED on pin "pin" for 250ms
///////////////////////////////////
  Serial.println(pin);

  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}*/

void resetReader(){
///////////////////////////////////
//Reset the RFID reader to read again.
///////////////////////////////////
  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(150);
}

void clearTag(char one[]){
///////////////////////////////////
//clear the char array by filling with null - ASCII 0
//Will think same tag has been read otherwise
///////////////////////////////////
  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}

boolean compareTag(char one[], char two[]){
///////////////////////////////////
//compare two value to see if same,
//strcmp not working 100% so we do this
///////////////////////////////////

  if(strlen(one) == 0) return false; //empty

  for(int i = 0; i < 12; i++){
    if(one[i] != two[i]) return false;
  }

  return true; //no mismatches
}
