/*
 12-23-2013
 SparkFun Electronics 2013
 Shawn Hymel

 This code is public domain but you buy me a beer if you use this 
 and we meet someday (Beerware license).

 Description:

 This sketch shows how to use the SparkFun AT42QT1010 Breakout
 Board. If you touch the Capacitive Touch area on the breakout
 board, the LED attached to the Arduino will light up (in addition
 to the LED on the AT42QT1010 breakout board).

 Simply connect power and ground to the breakout board,
 and the AT42QT1010 handles all the capacitive touch functions.
 By default, the board will light up the green LED when the pad
 is touched. A wire may also be connected from OUT on the
 breakout board to a digital input pin on an Arduino. This signal
 is normally LOW but goes HIGH on a touch detection. 

 The "LED Enable" solder jumper may be de-soldered in order to
 control the LED directly from the LED pin. This is useful if you
 want to light up a button that the user needs to push.

 Hardware connections:

 Uno Pin    AT42QT1010 Board  Function

 +5V        VDD               Power supply
 GND        GND               Ground
 2          OUT               Capacitive touch state output
 */

// Constants
const int TOUCH_BUTTON_PIN1 = 9;  // Input pin for touch state
const int TOUCH_BUTTON_PIN2 = 10;  // Input pin for touch state
const int TOUCH_BUTTON_PIN3 = 11;  // Input pin for touch state
const int TOUCH_BUTTON_PIN4 = 12;  // Input pin for touch state

const int LED_PIN = 13;          // Pin number for LED

// Global Variables
int buttonState1 = 0;             // Variable for reading button1
int buttonState2 = 0;           
int buttonState3 = 0;            
int buttonState4 = 0; 
           
int randomNumber;

void setup() {

  // Configure button pin as input 
  pinMode(TOUCH_BUTTON_PIN1, INPUT);
  pinMode(TOUCH_BUTTON_PIN2, INPUT);
  pinMode(TOUCH_BUTTON_PIN3, INPUT);
  pinMode(TOUCH_BUTTON_PIN4, INPUT);
  
  // Configure LED pin as output
  pinMode(LED_PIN, OUTPUT);

  //randomNumber = random(1, 5);
  
  Serial.begin(9600);
}


int buttonPressed(int buttonStateX, int buttonStateY, int buttonStateZ) {
    if(buttonStateX | buttonStateX | buttonStateX){
      return 1;
    }
    else { return 0; }
}

void loop() {
  
  //set to a random number between 1 and 4
  //randomNumber = random(1, 5);
  randomNumber = 1;
  Serial.println(randomNumber);

  unsigned long timePassed = micros();
     
  if(timePassed > 10000000) { //??? seconds (DON'T REDUCE THIS TIME - THE TOTAL TIME IS SHORTER THAN THE MILLISECONDS VALUE LEADS YOU TO BELIEVE)
      Serial.println("GAME OVER!");
      exit(0);
  }

   
  // Read the state of the capacitive touch board
  buttonState1 = digitalRead(TOUCH_BUTTON_PIN1);
  buttonState2 = digitalRead(TOUCH_BUTTON_PIN1);
  buttonState3 = digitalRead(TOUCH_BUTTON_PIN1);
  buttonState4 = digitalRead(TOUCH_BUTTON_PIN1);

  //Game continues, time restarts, and the new target button changes if you hit the correct button
  //Game over if you hit the wrong button
  switch(randomNumber) {
    //if touch is detected, turn on LED
    case 1: if(buttonState1 == HIGH) {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("CORRECT!");
            timePassed = 0;
            //randomNumber = random(1, 5);
        } else if(buttonPressed(buttonState2, buttonState3, buttonState4)) { 
            Serial.println("GAME OVER!");
            exit(0); 
        }
    case 2: if(buttonState2 == HIGH) {
            digitalWrite(LED_PIN, HIGH);
            timePassed = 0;
            Serial.println("CORRECT!");
            //randomNumber = random(1, 5);
        } else if(buttonPressed(buttonState1, buttonState3, buttonState4)) { 
            Serial.println("GAME OVER!");
            exit(0); 
        }
    case 3: if(buttonState3 == HIGH) {
            digitalWrite(LED_PIN, HIGH); 
            timePassed = 0;
            Serial.println("CORRECT!");
            //randomNumber = random(1, 5);
        } else if(buttonPressed(buttonState1, buttonState2, buttonState4)) { 
            Serial.println("GAME OVER!");
            exit(0); 
        }
    case 4: if(buttonState4 == HIGH) {
            digitalWrite(LED_PIN, HIGH);
            timePassed = 0;
            Serial.println("CORRECT!");
            //randomNumber = random(1, 5);
        } else if(buttonPressed(buttonState1, buttonState2, buttonState3)) { 
            Serial.println("GAME OVER!");
            exit(0); 
        }  
  }

   digitalWrite(LED_PIN, LOW);
  
  //Serial.println(buttonState);
  

}

