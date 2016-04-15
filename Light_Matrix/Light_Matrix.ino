// Sample Arduino Duemilanove interface code for Sparkfun's
// LED Matrix - Serial Interface - Red/Green/Blue
// http://www.sparkfun.com/commerce/product_info.php?products_id=760
//
// Written by:
// Fabio Pugliese Ornellas
// fabio.ornellas@gmail.com

// Pin definitions for Duemilanove.
// If you have a different board, check its datasheet SPI
// documentation for the corret pins.
#define PIN_SCK  13
#define PIN_MISO 12
#define  PIN_MOSI 11
#define PIN_SS   10


/**
 * Rhombus - Force Sensitive Resistor
 * Triangle - RFID
 * Square - Keypad
 * Firework - Color sensor
 * Arrow - Accelerometer
 */

char frameBuffer[64];

// Send a single byte via SPI, taken from Atmel's datasheet example.
void sendChar(char cData){
  SPDR = cData;
  while(!(SPSR&(1<<SPIF)));
}

// Send a full frame to the LED matrix
void sendFrame(char *frame) {
  // Assert SS
  digitalWrite(PIN_SS, LOW);
  // delay as the LED Matrix datasheet's recommends
  delayMicroseconds(500);
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
  // The LED Matrix datasheet's recommends this delay on daisy
  // chain configurations
  //delayMicroseconds(10);
}

void setup(){
  // SPI communication setup. Please refer to Atmel's datasheets
  // to understand all this. Basically it sets up the Arduino as
  // master and configure the appropriate clock speed.

  // Configuration register
  SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
  // Status register
  SPSR = SPSR & B11111110;

  // setup pins
  pinMode(PIN_SCK, OUTPUT);
  digitalWrite(PIN_SCK, LOW); // ensure clock low
  pinMode(PIN_MOSI, OUTPUT);
  pinMode(PIN_SS, OUTPUT);
  digitalWrite(PIN_SS, HIGH); // de-assert SS
  delayMicroseconds(500); // delay as the LED Matrix datasheet's recommends

  // This section reconfigure the board to no daisy chain
  // operation.
  // This can be confirmed by an RRGGBB pattern beginning at a
  // corner, with no black LEDs before the first LED, when the
  // matrix is powered on.
  // Warning: this will take effect only after first run, power
  // off and power on!
  digitalWrite(PIN_SS, LOW);
  delayMicroseconds(500);
  sendChar('%');
  sendChar(1);
  digitalWrite(PIN_SS, HIGH);
  delayMicroseconds(10);
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

  frameBuffer[22]=color;
  frameBuffer[30]=color;
  frameBuffer[38]=color;
  frameBuffer[46]=color;

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


void loop(){

  //Purple = 35
  //Red = 32
  //Orange = 200
  //Pinkish-Purple = 69
  //Neon green = 300
  //Yellow = 500

  
  button1(35);
  delay(750);
  clearLEDMatrix();

  button2(35);
  delay(750);
  clearLEDMatrix();

  button3(35);
  delay(750);
  clearLEDMatrix();

  button4(35);
  delay(750);
  clearLEDMatrix();

  oneStrike(32);
  delay(750);
  clearLEDMatrix();

  diamondRhombus(200);
  delay(750);
  clearLEDMatrix();

  triangle(45);
  delay(750);
  clearLEDMatrix();

  square(69);
  delay(750);
  clearLEDMatrix();

  firework();
  delay(750);
  clearLEDMatrix();

  arrow(300);
  delay(750);
  clearLEDMatrix();
  
  loser(500, 32);
  delay(750);
  clearLEDMatrix();

}
