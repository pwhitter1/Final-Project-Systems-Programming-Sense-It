#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int states[200];
int score = 0;

long startTime;
long timeLimit;

void setup() {

  //set up LCD
  lcd.begin(8, 1);
  lcd.setCursor(0,0);
  lcd.print("Start!");
  
  Serial.begin(9600);

}

//display corresponding shape on the 8x8 LED grid
void displayShape(int state){

  //Caitlin's code
  
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

void printTimeLeft(int timeLimit){

  lcd.begin(8, 1);
  lcd.setCursor(0,0);

  long timeLeft = timeLimit - (millis() - startTime);
  timeLeft = timeLeft / 1000;
  Serial.print(timeLeft);
  lcd.print("0:0");
  lcd.print(timeLeft);
  lcd.println("    ");

  delay(100);
}

void playButtonGame(){

  

  
}

void loop() {

  int state = random(5);  //randomly choose next state
  states[score] = state;  //add state to array

  displayShape(state); //display shape corresponding to state on LED grid

  startTime = millis();  //start time of current state
  setTimeLimit();  //time limit for user to complete current state

  while(millis() - startTime < timeLimit){

    //print remaining time on LCD
    lcd.clear();
    printTimeLeft(timeLimit);

    //check software serial input

    //check other input

    //if input doesn't match state, begin button game
    //else, break;
    
  }

  


}
