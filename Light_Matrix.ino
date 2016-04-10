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

void loop(){
  char frameBuffer[64];

  // Cycle through each possible color
  for(int color=0;color<=255;color++) {
    // And populate each position of the buffer with one color
    for(int j=0;j<64;j++) {
      frameBuffer[j]=j+color;
    }
    // Send the frame to the LED Matrix
    sendFrame(frameBuffer);
    // Colors are made by blinking the LEDs very fast.
    // Decreasing this delay too much (or removing it) may lead
    // to corrupted images.
    delay(200);
  }
}
