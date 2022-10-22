#include <MD_YX5300.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

MD_YX5300 mp3(Serial);
LiquidCrystal_I2C lcd(0x27, 16, 2); //address, char width, height
const uint8_t ARDUINO_RX = 0;  // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 1; // connect to RX of MP3 Player module


//TODO: 
//specify to user which command to execute
//add start condition
//add lose/end game function
//add win condition
//standardize delay times, shrink delay times over time


//prototypes
bool drive_it();
bool gas_it();
bool shift_it();

//pins
int wheelPin = 0;
int gearPin = 13;
int stompPin = 9;
int seedPin = 1;

//consts 
int highScore = 10;

void setup() {
  //set up ports
  pinMode(wheelPin, INPUT); //POT
  pinMode(gearPin, INPUT_PULLUP); //TOGGLE
  pinMode(stompPin, INPUT_PULLUP); //STOMP
  //pinMode(8, OUTPUT); //LED
  //pinMode(9, OUTPUT); //LED
  //pinMode(5, OUTPUT); //OLED
  //pinMode(4, OUTPUT); //OLED

  //set up I2C
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("hello world");
  
  // set up mp3
  delay(1000);
  Serial.begin(9600);
  mp3.begin();
  mp3.setSynchronous(true);
  mp3.volumeMax();

  //seed random number
  randomSeed(analogRead(seedPin));
}


void loop() {
  /*//mp3.playTrack(001);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  //delay(2000);*/

  bool startGame = false;
  while (!startGame)
  {
    //play mp3 to start
    double switchPin = analogRead(togPin);
    lcd.print("Shift gears to start!");
    
    delay(200); //flip switch to start game? 
    lcd.clear();
    delay(2000);  //flip swithc in this delay - add LCD prompt? 
    startGame = (switchPin != digitalRead(togPin)); 

  }

  lcd.clear();
  delay(1000);

  lcd.print("start");
  delay(1000);
  lcd.clear();
  int score = 0;
  bool success = false;
  while (score <=10)
  {
    int task = (int)random(1,3); 
    switch (task)
    {
      case 1:
        //TODO: play gas_it prompt or print to LCD 
        success = gas_it();
        break;
      case 2:
        //TODO: play shift_it prompt or print to LCD 
        success = shift_it();
        break;
      case 3:
        //TODO: play shift_it prompt or print to LCD 
        success = drive_it();
        break;
    }
    delay(500);
    if(success)
    {
      score++;
      print("Point! Score: %d", score);
      if(score = highScore)
      {
        print("You win!")
      }
    }
    else
    {
      print("You lose!! </3");
      break;
    }
  }
  

  delay(2000);
  lcd.clear();
}


//ACTION 1: DRIVE IT: POTENTIOMETER
//TODO: can clean up logic here, return stuff here, based on winner/loser, print stuff
bool drive_it(){
  bool winner;
  double last_volt = analogRead(wheelPin));
  delay(5000);

  //0-1023
  /*if(abs(last_volt - analogRead(wheelPin)) > 100){
      lcd.print("winner");
      winner = true;
  }
  else{
      lcd.print("loser");
      winner = false;
  }  */
  return (abs(last_volt - analogRead(wheelPin)) > 100)
  
}


//ACTION 2: SHIFT IT: TOGGLE SWITCH
bool shift_it(){
  bool winner;
  int last_state = digitalRead(gearPin);
  delay(5000);
  
  /*if(last_state != digitalRead(gearPin)){
    lcd.print("winner");
    winner = true;
  }
  else{
      lcd.print("loser");
      winner = false;
  }*/
  return (last_state != digitalRead(gearPin));
}


//ACTION 3: GAS IT: BUTTON PRESS 
bool gas_it(){
  bool winner;
  int last_state = digitalRead(stompPin);
  delay(5000);
  
  //if last state != current state, winner
  /*if(last_state != digitalRead(stompPin)){
      lcd.print("winner");
      winner = true;
    }
    else{   //last_state == digitalRead(stomPin)
      lcd.print("loser");
      winner = false;
    }*/
  
  return (last_state != digitalRead(stompPin));
  
}
