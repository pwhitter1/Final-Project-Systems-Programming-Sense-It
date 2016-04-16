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
void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  pinMode(TOUCH_BUTTON_PIN1, INPUT);
  pinMode(TOUCH_BUTTON_PIN2, INPUT);
  pinMode(TOUCH_BUTTON_PIN3, INPUT);
  pinMode(TOUCH_BUTTON_PIN4, INPUT);
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
  
  Wire.endTransmission();    // stop transmitting
  digitalWrite(LED_PIN, LOW);
}
