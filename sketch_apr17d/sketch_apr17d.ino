// char tg_flag = 0;

#include "c:/mylib/my_arduino_lib.h"
#include "c:/mylib/my_fnd_lib.h"

uint16_t cnt = 0;  // unsigned char
uint16_t t_loop = 0;

struct clock
{
  int t_loop;
  char hour;
  char min;
  char sec;
};

struct clock time = {0, 1, 24, 30};

void setup() {
  DDRB  = 0xff;
  PORTB = 0xff;
  DDRD  = 0xff;
  Serial.begin(115200); // 9600
}

void loop() {
  // 실습4
  _delay_ms(1);
  time.t_loop++;
  
  if(time.t_loop > 1000) {
    time.t_loop = 0;
    time.sec++;

    tg_flag == 0? tg_flag = 1 : tg_flag = 0;

    if(time.sec > 59){ //1 Min
      time.sec = 0;
      time.min++;

      if(time.min > 59) { // 1 Hour
          time.min = 0;
          time.hour++;

          if(time.hour > 23){
            time.hour = 0;
          }
      }
    }
  }
  //fnd_dis_4(((time.min/10)*1000) + ((time.min%10)*100) + ((time.sec/10)*10) + (time.sec%10));
  //fnd_dis_4(fnd_time(time.min, time.sec));
//
  // 실습3
  delay(1);
  /*
  t_loop++;
  if(t_loop > 10)
  {
    t_loop = 0;
    cnt++;
    tg_flag = ~tg_flag;
    //tg_flag == 0 ? tg_flag = 1: tg_flag = 0;
  }
  */
  cnt++;
  fnd_dis_4(cnt);
  

 // 실습2
 //PORTD = fnd_font[cnt];  // mcu 방식
//  byte_out(fnd_font[cnt]); // arduino 방식
//  cnt++;
//  if(cnt > 9) cnt = 0;
//  Serial.println((cnt %10 + 0x30)-48);
//  delay(500);
 
// 실습1
//   PORTD = 0x06;
//  delay(500);
// PORTD = 0x38;  // L
// delay(500);
// PORTD = 0x66;
// delay(500);
}