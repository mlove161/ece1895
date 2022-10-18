#include <MD_YX5300.h>

const uint8_t ARDUINO_RX = 0; // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 1; // connect to RX of MP3 Player module

MD_YX5300 mp3(Serial);

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  mp3.begin();
  mp3.setSynchronous(true);
  mp3.volumeMax();
  mp3.playTrack(001);
}

void loop() {
  // put your main code here, to run repeatedly:

}
