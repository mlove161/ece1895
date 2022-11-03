#include <MD_YX5300.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
#include <EEPROM.h>

MD_YX5300 mp3(Serial);
LiquidCrystal_I2C lcd(0x27, 16, 2); //address, char width, height
const uint8_t ARDUINO_RX = 0;  // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 1; // connect to RX of MP3 Player module


//TODO: 
//add start condition
//add lose/end game function
//standardize delay times, shrink delay times over time
//store highscore


//prototypes
bool drive_it(int t);
bool gas_it(int t);
bool shift_it(int t);

//pins
int wheelPin = 0;
int togPin = 10;
int stompPin = 9;
int seedPin = 1;

//consts 
int highScore = 99;
int time = 5;



void setup() {
  //set up ports
  pinMode(wheelPin, INPUT); //POT
  pinMode(togPin, INPUT_PULLUP); //TOGGLE
  pinMode(stompPin, INPUT_PULLUP); //STOMP

  //set up I2C
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  
  // set up mp3
  Serial.begin(9600);
  mp3.begin();
  mp3.setSynchronous(true);
  mp3.volumeMax();

  //seed random number
  randomSeed(analogRead(seedPin));
  EEPROM.write(1, 0);

}


void loop() {

  //start game
  bool startGame = false;
  while (!startGame)
  {
    //play mp3 to start
    double switchPin = digitalRead(togPin);
    lcd.print("Shift gears");
    lcd.setCursor(0, 1);
    lcd.print("to start!");
    lcd.setCursor(0, 0);
    
    delay(2000); //flip switch to start game? 
    lcd.clear();
    delay(2000);  //flip switch in this delay - add LCD prompt? 
    startGame = (switchPin != digitalRead(togPin)); 
  }
  int gameTime = time;

  //delay(1000);
  //lcd.print("Starting engine! Ready...");
  delay(1000);
  lcd.clear();
  
  int score = 0;
  bool success = false;
  while (score <=highScore)
  {
    int task = (int)random(1,4); 
    switch (task)
    {
      case 1:
        lcd.print("Gas it");
        mp3.playTrack(1);
        success = gas_it(gameTime);
        break;
      case 2:
        lcd.print("Shift it");
        mp3.playTrack(2);
        success = shift_it(gameTime);
        break;
      case 3:
        lcd.print("Steer it");
        mp3.playTrack(3);
        success = drive_it(gameTime);
        break;
    }
    lcd.clear();
    delay(1000);
    
    if(success)
    {
      score++;
      lcd.print(String("Point! Score: ") +  String(score));
      delay(1000);
      lcd.clear();
      //print("Point! Score: %d", score);
      gameTime *= 0.95;
      if(score == highScore)
      {
        lcd.print("You win!");
        delay(1000);
        lcd.clear();
        break;
      }
    }
    else
    {
      lcd.print("You lose!! </3");
      delay(1000);
      lcd.clear();
      mp3.playTrack(4);
      //if lose, check if high score is written
      unsigned int temp = EEPROM.read(1);
      //score = local score for instance
      // high score = 99
      if(score > temp)
      {
        EEPROM.update(1, score);
      }
      break;
    }
  }
 
  //delay(2000);
  //lcd.clear();
}


//ACTION 1: DRIVE IT: POTENTIOMETER
bool drive_it(int gameTime){
  double last_volt = analogRead(wheelPin);
  delay(gameTime);
  return (abs(last_volt - analogRead(wheelPin)) > 100);
}


//ACTION 2: SHIFT IT: TOGGLE SWITCH
bool shift_it(int gameTime){
  int last_state = digitalRead(togPin);
  delay(gameTime);
  return (last_state != digitalRead(togPin));
}


//ACTION 3: GAS IT: BUTTON PRESS 
bool gas_it(int gameTime){
  int last_state = digitalRead(stompPin);
  delay(gameTime);
  return (last_state != digitalRead(stompPin));
  
}
