/*
 제목    : I2C_LCD에 문자열 출력하기
 내용   : I2C_LCD에 원하는 문자열을 표시해 봅니다.  
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
// I2C_LCD의 I2C주소와 가로, 세로 크기를 정해줍니다.
// '0x27'에 위에서 찾은 I2C 주소를 넣어주세요.(0x3F 또는  0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// 특수문자를 만들어줍니다.
byte customChar[] = {
  B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100
};
 
void setup()
{
  // I2C_LCD를 초기화 해줍니다.
  lcd.init();
 
  // I2C_LCD의 백라이트를 켜줍니다.
  lcd.backlight();
 
  // 위에서 만든 특수문자를 0번 배열에 저장합니다.
  lcd.createChar(0, customChar);
 
  // I2C_LCD에 "Hello, world!"라는 메세지를 첫번째줄 첫번째칸에 출력합니다.(0, 0)
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
 
 
  // I2C_LCD에 위에서 만든 특수문자를 두번째줄 첫번째칸에 출력합니다.(0, 1)
  lcd.setCursor(0, 1);
  lcd.write(0);
}
 
void loop()
{
}