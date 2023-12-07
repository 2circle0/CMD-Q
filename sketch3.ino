#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Wire.begin(); // Wire 라이브러리를 초기화
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("<CMDQ>");
  lcd.setCursor(2, 1);
  lcd.print("Post-itMaker");
}

void loop() 
{
  // 기능 추가시 사용
}
