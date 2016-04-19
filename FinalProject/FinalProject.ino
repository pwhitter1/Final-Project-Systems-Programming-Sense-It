#include <LiquidCrystal.h>
#include <Wire.h>
#include <SoftwareSerial.h>  

/* LED Matrix */
char frameBuffer[64];
#define PIN_SCK  13
#define  PIN_MOSI 11
#define PIN_SS   10

/* LCD */
LiquidCrystal lcd(A0, 9, 5, 4, 3, 2);

/* I2C Arduino Communication */
int buttonPressed = 0;

/* Software Serial communication */
int myTxPin = 7;  // Chosen pin for transmitting data
int myRxPin = 8;  // Chosen pin for receiving data
SoftwareSerial softSerial(myRxPin, myTxPin);  // Create software serial object
int sensorPressed = -1; //read from software serial

/* game-related variables */
int score = 0;
int state = 0;
long startTime;
long timeLimit;





// Send a single byte via SPI (for LED matrix)
void sendChar(char cData){
  SPDR = cData;
  while(!(SPSR&(1<<SPIF)));
}

void setup() {

  Serial.begin(9600);

  //set up LCD
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Start!");
  delay(500);

  //SPI communication setup
  SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
  SPSR = SPSR & B11111110;

  //set up pins
  pinMode(PIN_SCK, OUTPUT);
  digitalWrite(PIN_SCK, LOW); // ensure clock low
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_SS, OUTPUT);
  digitalWrite(PIN_SS, HIGH); // de-assert SS
  delay(500); // delay as the LED Matrix datasheet's recommends

  digitalWrite(PIN_SS, LOW);
  delay(500);
  sendChar('%');
  sendChar(1);
  digitalWrite(PIN_SS, HIGH);
  delay(10);
  
  softSerial.begin(9600); //software serial

  //for i2c arduino communication
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);

  

}


//for I2C arduino communication
void receiveEvent(int bytes) {
  buttonPressed = Wire.read();    // read one character from the I2C
  //Serial.begin(9600);
}

/* LED Matrix functions */
// Send a full frame to the LED matrix
void sendFrame(char *frame) {
  // Assert SS
  digitalWrite(PIN_SS, LOW);
  // delay as the LED Matrix datasheet's recommends
  delay(500);
  // send the full buffer
  for(int i=0;i<64;i++) {
    char c;
    c=*(frame+i);
    // This is needed because sending a '%' will reconfigure the
    // board for daisy chain operation
    if('%'==c)
      sendChar((2<<5)&(1<<2)&1); // similar color
    else
      sendChar(c);
  }
  // de-assert SS
  digitalWrite(PIN_SS, HIGH);
  //delayMicroseconds(10);
}

//Display square on LED that tells the user to push button1
void button1(int color) {
    
    for(int j=0;j<4;j++) {
      frameBuffer[j] = color;
    }

    for(int j=8; j< 12;j++) {
      frameBuffer[j] = color;
    }

    for(int j=16;j< 20;j++) {
      frameBuffer[j] = color;
    }

     for(int j=24;j< 28;j++) {
      frameBuffer[j] = color;
    }

    sendFrame(frameBuffer);
}


//Display square on LED that tells the user to push button2
void button2(int color) {
    
    for(int j=32;j<36;j++) {
      frameBuffer[j] = color;
    }

    for(int j=40; j< 44;j++) {
      frameBuffer[j] = color;
    }

    for(int j=48;j< 52;j++) {
      frameBuffer[j] = color;
    }

     for(int j=56;j< 60;j++) {
      frameBuffer[j] = color;
    }

    sendFrame(frameBuffer);
}

//Display square on LED that tells the user to push button3
void button3(int color) {
    
    for(int j=4;j<8;j++) {
      frameBuffer[j] = color;
    }

    for(int j=12; j< 16;j++) {
      frameBuffer[j] = color;
    }

    for(int j=20;j< 24;j++) {
      frameBuffer[j] = color;
    }

     for(int j=28;j< 32;j++) {
      frameBuffer[j] = color;
    }

    sendFrame(frameBuffer);
}

//Display square on LED that tells the user to push button4
void button4(int color) {
    
    for(int j=36;j<40;j++) {
      frameBuffer[j] = color;
    }

    for(int j=44; j< 48;j++) {
      frameBuffer[j] = color;
    }

    for(int j=52;j< 56;j++) {
      frameBuffer[j] = color;
    }

     for(int j=60;j< 64;j++) {
      frameBuffer[j] = color;
    }

    sendFrame(frameBuffer);
}

//displays a diamond-rhombus
//FILL THESE IN
void diamondRhombus(int color) {
  //Fill in everything
  for(int j=0;j<64;j++) {
     frameBuffer[j]=color;
   }

  //Clear the one that don't take the diamond shape
  frameBuffer[0]=0;
  frameBuffer[8]=0;
  frameBuffer[16]=0;
  frameBuffer[1]=0;
  frameBuffer[9]=0;
  frameBuffer[2]=0;
  frameBuffer[5]=0;
  frameBuffer[6]=0;
  frameBuffer[14]=0;
  frameBuffer[7]=0;
  frameBuffer[15]=0;
  frameBuffer[23]=0;

  frameBuffer[40]=0;
  frameBuffer[48]=0;
  frameBuffer[56]=0;
  frameBuffer[49]=0;
  frameBuffer[57]=0;
  frameBuffer[58]=0;
  frameBuffer[61]=0;
  frameBuffer[54]=0;
  frameBuffer[62]=0;
  frameBuffer[47]=0;
  frameBuffer[55]=0;
  frameBuffer[63]=0;

  sendFrame(frameBuffer);
}

//displays a triangle
void triangle(int color) {
  //Shape outline
  frameBuffer[26]=color;
  frameBuffer[34]=color;

  frameBuffer[19]=color;
  frameBuffer[12]=color;
  frameBuffer[5]=color;
  
  frameBuffer[43]=color;
  frameBuffer[52]=color;
  frameBuffer[61]=color;

  frameBuffer[13]=color;
  frameBuffer[21]=color;
  frameBuffer[29]=color;
  frameBuffer[37]=color;
  frameBuffer[45]=color;
  frameBuffer[53]=color;

  frameBuffer[27]=color;
  frameBuffer[35]=color;
  frameBuffer[20]=color;
  frameBuffer[28]=color;
  frameBuffer[36]=color;
  frameBuffer[44]=color;

  sendFrame(frameBuffer);
}

//displays a square
void square(int color) {
  frameBuffer[18]=color;
  frameBuffer[26]=color;
  frameBuffer[34]=color;
  frameBuffer[42]=color;
  
  frameBuffer[19]=color;
  frameBuffer[27]=color;
  frameBuffer[35]=color;
  frameBuffer[43]=color;
  
  frameBuffer[20]=color;
  frameBuffer[28]=color;
  frameBuffer[36]=color;
  frameBuffer[44]=color;

  frameBuffer[21]=color;
  frameBuffer[29]=color;
  frameBuffer[37]=color;
  frameBuffer[45]=color;

//  frameBuffer[22]=color;
//  frameBuffer[30]=color;
//  frameBuffer[38]=color;
//  frameBuffer[46]=color;

  sendFrame(frameBuffer);
}

//Displays "firework" pattern
void firework() {
  frameBuffer[2]=20;
  frameBuffer[7]=200;
  frameBuffer[9]=35;
  frameBuffer[10]=450;
  
  frameBuffer[15]=600;
  frameBuffer[16]=645;
  frameBuffer[13]=150;
  frameBuffer[19]=130;
  
  frameBuffer[20]=400;
  frameBuffer[23]=65;
  frameBuffer[24]=850;
  frameBuffer[29]=225;

  frameBuffer[33]=95;
  frameBuffer[34]=100;
  frameBuffer[38]=700;
  frameBuffer[40]=750;

  frameBuffer[41]=330;
  frameBuffer[42]=220;
  frameBuffer[46]=460;
  frameBuffer[49]=700;

  frameBuffer[52]=80;
  frameBuffer[54]=550;
  frameBuffer[57]=300;
  frameBuffer[59]=60;

  frameBuffer[62]=25;
  frameBuffer[63]=360;
  frameBuffer[66]=820;
  frameBuffer[68]=900;

  sendFrame(frameBuffer);
}

//displays an "arrow" pattern
void arrow(int color) {
    //Fill in everything
  for(int j=0;j<64;j++) {
     frameBuffer[j]=color;
   }

   //Clear the one that don't take the arrow
  frameBuffer[0]=0;
  frameBuffer[8]=0;
  frameBuffer[16]=0;
  frameBuffer[1]=0;
  frameBuffer[9]=0;
  frameBuffer[2]=0;
  
  frameBuffer[5]=0;
  frameBuffer[6]=0;
  frameBuffer[14]=0;
  frameBuffer[7]=0;
  frameBuffer[15]=0;
  frameBuffer[23]=0;

  frameBuffer[32]=0;
  frameBuffer[40]=0;
  frameBuffer[48]=-0;
  frameBuffer[56]=0;
  frameBuffer[33]=0;
  frameBuffer[41]=0;
  frameBuffer[49]=0;
  frameBuffer[57]=0;

  frameBuffer[38]=0;
  frameBuffer[46]=0;
  frameBuffer[54]=0;
  frameBuffer[62]=0;
  frameBuffer[39]=0;
  frameBuffer[47]=0;
  frameBuffer[55]=0;
  frameBuffer[63]=0;

  sendFrame(frameBuffer);
}


//Clear the LED Matrix of all color in order to show the next grid of color
void clearLEDMatrix() {
    int color = 0;
  
    for(int j=0;j<64;j++) {
      frameBuffer[j]=color;
    }

    sendFrame(frameBuffer);
}


//displays when someone gets something wrong
void oneStrike(int color) {

  //An X
  frameBuffer[0]=color;
  frameBuffer[9]=color;
  frameBuffer[18]=color;
  frameBuffer[27]=color;
  frameBuffer[36]=color;
  frameBuffer[45]=color;
  frameBuffer[54]=color;
  frameBuffer[63]=color;

  frameBuffer[7]=color;
  frameBuffer[14]=color;
  frameBuffer[21]=color;
  frameBuffer[28]=color;
  frameBuffer[35]=color;
  frameBuffer[42]=color;
  frameBuffer[49]=color;
  frameBuffer[56]=color;
  
  sendFrame(frameBuffer);
}

//displays big red X and a smiley face upon your loss
void loser(int color, int color2) {

  //Call one strike function three times
  for(int i = 0; i < 3; i++) {
     oneStrike(color2);
     delay(750);
     clearLEDMatrix();
     delay(500);
  }

  //A smiley face
  //Eye1
  frameBuffer[16]=color;
  frameBuffer[17]=color;
  frameBuffer[18]=color;

  //Eye2
  frameBuffer[40]=color;
  frameBuffer[41]=color;
  frameBuffer[42]=color;

  //Smile
  frameBuffer[23]=color;
  frameBuffer[31]=color;  
  frameBuffer[39]=color;
  frameBuffer[47]=color;
  
  frameBuffer[14]=color;
  frameBuffer[5]=color;
  frameBuffer[54]=color;
  frameBuffer[61]=color;


  sendFrame(frameBuffer);
  delay(2000);
  
}

//display corresponding shape on the 8x8 LED grid
/* 0: Green Arrow - Accelerometer
 * 1: Multicolor Firework - Color sensor
 * 2: Orange Rhombus - Force Sensitive Resistor
 * 3: Purple Square - Keypad
 * 4: Blue Triangle - RFID
 * 5: Top Left Square - Button
 * 6: Top Right Square - Button
 * 7: Bottom Left Square - Button
 * 8: Bottom Right Square - Button
 */
void displayShape(int state){

  switch(state){

    // green arrow: accelerometer
    case 0:
      arrow(300);
      break;
  
    // firework: color sensor
    case 1:
      firework();
      break;

    // rhombus: force resistor
    case 2:
      diamondRhombus(200);
      break;

    // square: keypad
    case 3:
      square(69);
      break;
    
    // triangle: RFID
    case 4:
      triangle(45);
      break;

    // top left square: button1
    case 5:
      button1(35);
      break;
    
    // top right square: button2
    case 6:
      button2(35);
      break;

    // bottom left square: button3
    case 7:
      button3(35);
      break;

    // bottom right square: button4
    case 8:
      button4(35);
      break;

  }

   delay(600);
   clearLEDMatrix();
  
  
}

//set time limit for user depending on current score
void setTimeLimit(){
  if(score < 30){
    timeLimit = 5000;
  }
  else{
    timeLimit = 3000;
  }
}

//print remaining time to LCD
void printTimeLeft(){

  lcd.begin(8, 1);
  lcd.setCursor(0,0);

  long timeLeft = timeLimit - (millis() - startTime);
  timeLeft = timeLeft / 1000;
  lcd.print("0:0");

  lcd.print(timeLeft);
  lcd.println("    ");

  delay(100);
}

void gameOver(){

  //send score to SD
  

  loser(500, 32);
  delay(700);
  clearLEDMatrix();
  delay(10000000);
  
}

void playButtonGame(){

  int buttonState = random(5, 9); //randomly generate button that player should press
  
  int i;
  for(i = 0; i < 5; i++){ //do 5 rounds of button game

    int done = 0;

    long buttonStart = millis();

    //give 2 seconds to press button
    while(millis() - buttonStart >= 2000){

        //game over if player pressed wrong button
        if(buttonPressed != 0 && buttonPressed != buttonState){
          gameOver();
          return;
        }
        //go to next round if player pressed right button
        else if(buttonPressed == buttonState){
          done = 1;
          break;
        }
     }

     //to check if user didn't press any buttons within time limit
     if(done == 0){
        gameOver();
        return;
     }

  }

  
}

void loop() {

  state = random(5);  //randomly choose next state

  displayShape(state); //display shape corresponding to state on LED grid

  //Serial.println(buttonPressed);

  lcd.setCursor(0,0);
  lcd.clear();
  delay(500);
  
  startTime = millis();  //start time of current state
  setTimeLimit();  //time limit for player to complete current state

  //check for pressed sensors while player has time remaining
  while(millis() - startTime < timeLimit){

    printTimeLeft(); //print remaining time on LCD

    //check software serial input
    if(softSerial.available()){  
      Serial.print("sensor pressed: ");
      sensorPressed = softSerial.parseInt(); 
      Serial.println(sensorPressed);
      //if they pressed the correct sensor, break from loop 
      if(sensorPressed == state){
        break;
      }
      //check for RFID
      else if(buttonPressed == 4){
        Serial.println("RFID tapped");
        if(buttonPressed == state){
          break;
        }
      }
      else{
        playButtonGame();
      }
    }
    
  }
  
  score++; //increment score


}
