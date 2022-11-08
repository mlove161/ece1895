#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// address could be 0x27 also

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("hello world");
}

void loop() {
  // put your main code here, to run repeatedly:

}
