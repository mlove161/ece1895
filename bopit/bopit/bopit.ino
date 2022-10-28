#include <MD_YX5300.h>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>

MD_YX5300 mp3(Serial);
LiquidCrystal_I2C lcd(0x27, 16, 2); //address, char width, height
const uint8_t ARDUINO_RX = 0;  // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 1; // connect to RX of MP3 Player module


//TODO: 
//randomize 3 function calls
//specify to user which command to execute
//add start condition
//add lose/end game function
//add win condition
//add score
//standardize delay times, shrink delay times over time


//prototypes
void drive_it();
void gas_it();
void shift_it();

//pins
int potPin = 0;
int togPin = 13;
int stompPin = 13;


void setup() {
  //set up ports
  pinMode(potPin, INPUT); //POT
  pinMode(togPin, INPUT_PULLUP); //TOGGLE
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
}


void loop() {
  /*//mp3.playTrack(001);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  //delay(2000);*/
  
  lcd.clear();
  delay(1000);

  lcd.print("start");
  delay(1000);
  lcd.clear();
  
  //drive_it();
  //shift_it();
  gas_it();

  delay(2000);
  lcd.clear();
}


//ACTION 1: DRIVE IT: POTENTIOMETER
void drive_it(){
  double last_volt = analogRead(potPin);
  delay(5000);

  //0-1023
  if(abs(last_volt - analogRead(potPin)) > 100){
      lcd.print("winner");
   }
   else{
      lcd.print("loser");
   }  
}


//ACTION 2: SHIFT IT: TOGGLE SWITCH
void shift_it(){
  
  int last_state = digitalRead(togPin);
  delay(5000);
  
  if(last_state == HIGH){
    if(digitalRead(togPin) == LOW){
      lcd.print("winner");
    }
    else{
      lcd.print("loser");
    }
  }
  else{
    if(digitalRead(togPin) == HIGH){
      lcd.print("winner");
    }
    else{
      lcd.print("loser");
    }
  }
}


//ACTION 3: GAS IT: BUTTON PRESS 
void gas_it(){
  int last_state = digitalRead(stompPin);
  delay(5000);
  
  if(last_state == HIGH){
    if(digitalRead(stompPin) == LOW){
      lcd.print("winner");
    }
    else{
      lcd.print("loser");
    }
  }
  else{
    if(digitalRead(stompPin) == HIGH){
      lcd.print("winner");
    }
    else{
      lcd.print("loser");
    }
  }
  
}