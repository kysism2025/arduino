#include <LiquidCrystal_I2C.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_arduino_lib_v2_0.h"

#define bz 2


LiquidCrystal_I2C lcd(0x27, 16, 2); // Chip의 Address 아누이노 사이트 참조

int cnt = 0;
int cnt2 = 0;
char st[] = "LCD Test";
char buf[30];
char buf1[30];
char buf2[30];

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();  

  pinMode(2, OUTPUT);
  d_out(bz, 0);

  // lcd.setCursor(0, 1);
  // lcd.print("Up Cnt = ");

  // lcd.setCursor(7,1);
  // lcd.printstr(st);
}

void one_line_clr(char nb) {
  lcd.setCursor(0, nb);
  lcd.print("                ");
}

void one_char_clr(char x, char y) {
  lcd.setCursor(x, y);
  lcd.print(' ');
}

void xy_print(char x, char y, char* buf) {
    lcd.setCursor(x, y);
    lcd.printstr(buf);
}

// void xy_print(char x, char y, String buf) {
//     lcd.setCursor(x, y);
//     lcd.print(buf);
// }

// void xy_print(char x, char y, char* buf) {  
//   lcd.setCursor(x,y);
//   for(int i = 0; i < len; i++){
//     lcd.print(*(buf + i));
//   }
// }

// void xy_print(char x, char y, char* buf) {  
//   lcd.setCursor(x,y);
//   while(*buf != '\0'){
//     lcd.print(*buf);
//     buf++;
//   }
// }


void loop() {

  // lcd.write(cnt/1000 + 0x30);
  // lcd.write(cnt%1000/100 + 0x30);
  // lcd.write(cnt%100/10 + 0x30);
  // lcd.write(cnt%10 + 0x30);

  lcd.setCursor(0, 0);
  lcd.print("cnt=");
  lcd.setCursor(6, 0);
  // sprintf(buf1, "cnt=%4d", cnt);
  // lcd.print(buf1);
  lcd.write(cnt/1000 + 0x30);
  lcd.write(cnt%1000/100 + 0x30);
  lcd.write(cnt%100/10 + 0x30);
  lcd.write(cnt%10 + 0x30);
  
  lcd.setCursor(0, 1);
  lcd.print("cnt=");
  lcd.setCursor(6, 1);
  cnt2 = 9999-cnt;
  lcd.write(cnt2/1000 + 0x30);
  lcd.write(cnt2%1000/100 + 0x30);
  lcd.write(cnt2%100/10 + 0x30);
  lcd.write(cnt2%10 + 0x30);

  xy_print(0, 0, "Song");
  //xy_print(0, 0, "Song", 4);

  // one_line_clr(0);
  // one_char_clr(0, 0);
  //  for(int i = 0; i < 2; i++) {
  //    for(int j = 0; j < 16; j++) {
  //       lcd.setCursor(j, i);
  //       lcd.write(0x20);
  //    }
  //    delay(400);
  //  }
   
  // for(int k = 0; k <= 9; k++) {
  //   lcd.scrollDisplayLeft();
  //   delay(150);
  // }

  // for(int k = 0; k < 16; k++) {
  //   lcd.scrollDisplayRight();
  //   delay(150);
  // }

  // sprintf(buf2, "cnt=%4d", cnt2);
  // lcd.print(buf2);  
  // lcd.print(9999-cnt);

  cnt++;
  delay(400);
  // 실습2-6
  // lcd.setCursor(10, 0);
  // lcd.write(cnt/1000 + 0x30);
  // lcd.write(cnt%1000/100 + 0x30);
  // lcd.write(cnt%100/10 + 0x30);
  // lcd.write(cnt%10 + 0x30);
  // delay(400);
  // cnt++;

  // lcd.setCursor(0, 1);
  // sprintf(buf, "cnt = %4d", cnt);
  // lcd.print(buf);

  // lcd.setCursor(5, 0);
  // lcd.print("LCD OK!!!");

  // // 실습2-5 커서 깜빡이기
  // lcd.setCursor(5, 0);
  // lcd.cursor();
  // delay(800);
  // lcd.noCursor();
  // delay(800);

  // lcd.clear();
  // while(1){} // 무한 반복으로 깨끗하세 처리
  // lcd.home();

  // lcd.setCursor(5,1);
  // lcd.rightToLeft();
  // lcd.print("song");
  // delay(800);

  // lcd.leftToRight();
  // lcd.print("song");

  // delay(800);

  // 실습2-4 좌우로 움직이기
  // for(int k = 0; k <= 9; k++) {
  //   lcd.scrollDisplayLeft();
  //   delay(150);
  // }

  // for(int k = 0; k <= 10; k++) {
  //   lcd.scrollDisplayRight();
  //   delay(150);
  // }

  // 실습2-3
  // 10의 자리 커서의 깜빡임
  // lcd.setCursor(12, 0);
  // lcd.cursor_on();
  // lcd.setBacklight(1);
  // delay(400);
  // cnt++;
  // lcd.cursor_off();
  // lcd.setBacklight(0);
  // delay(400);  

  // 표시되는 전체 글자의 깜빡임
  // lcd.setCursor(12, 0);
  // lcd.noDisplay();
  // delay(400);
  // cnt++;
  //  lcd.display();
  // delay(400);  
  
  // 실습2-2
  // 100자리 커서 깜빡임
  // lcd.setCursor(10, 0);
  // lcd.blink_on();
  // delay(400);
  // lcd.blink_off();
  // delay(400);


  // 실습2-1
  // 1000단위 숫자 증가
  // lcd.setCursor(10, 0);
  // lcd.print(cnt/1000); // + 0x30);
  // lcd.print(cnt%1000/100); // + 0x30);
  // lcd.print(cnt%100/10); // + 0x30);
  // lcd.print(cnt%10);// + 0x30);
  // delay(400);
  // cnt++;

  // 실습1
  // lcd.setCursor(2,0);
  // lcd.print("Hello @#$");
  // lcd.setCursor(6,1);
  // lcd.print("Count");
}
