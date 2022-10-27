#include <MD_YX5300.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

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
bool drive_it();
bool gas_it();
bool shift_it();

//pins
int wheelPin = 0;
int togPin = 13;
int stompPin = 9;
int seedPin = 1;

//consts 
int highScore = 10;


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
    
    //delay(1000); //flip switch to start game
    startGame = (switchPin != digitalRead(togPin)); 
  }

  //delay(1000);
  //lcd.print("Starting engine! Ready...");
  delay(1000);
  lcd.clear();
  
  int score = 0;
  bool success = false;
  while (score <=10)
  {
    int task = (int)random(1,4); 
    switch (task)
    {
      case 1:
        lcd.print("Gas it");
        success = gas_it();
        break;
      case 2:
        lcd.print("Shift it");
        success = shift_it();
        break;
      case 3:
        lcd.print("Steer it");
        success = drive_it();
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
      if(score == highScore)
      {
        lcd.print("You win!");
        delay(1000);
        lcd.clear();
      }
    }
    else
    {
      lcd.print("You lose!! </3");
      delay(1000);
      lcd.clear();
      break;
    }
  }
 
  //delay(2000);
  //lcd.clear();
}


//ACTION 1: DRIVE IT: POTENTIOMETER
bool drive_it(){
  double last_volt = analogRead(wheelPin);
  delay(5000);
  return (abs(last_volt - analogRead(wheelPin)) > 100);
}


//ACTION 2: SHIFT IT: TOGGLE SWITCH
bool shift_it(){
  int last_state = digitalRead(togPin);
  delay(5000);
  return (last_state != digitalRead(togPin));
}


//ACTION 3: GAS IT: BUTTON PRESS 
bool gas_it(){
  int last_state = digitalRead(stompPin);
  delay(5000);
  return (last_state != digitalRead(stompPin));
  
}
