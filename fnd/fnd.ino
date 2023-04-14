
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int8_t tg_flag = 0; // char 와 같음

#include "my_arduino_lib.h"
#include "my_fnd_lib.h"
#include "my_key_lib.h"


long cnt = 123456;  // unsigned char 와 같음
int t_loop = 0;
char tg_flag2 = 0;

struct ck
{
  int time_loop;
  char hour;
  int8_t min;
  char sec;
}time = {0, 16, 0, 0};

struct chk{
  char key_flag;
  char redy_flag;
  int bit_flag;
  char byte_flag;
  unsigned int kb_flag;
  char key_d[10];
  float dk_flag;
}flag = {0,0,0,0,0};

unsigned char key_buf;

char key_bit_in()
{
  char buf = 0;
  // bit 방식일기 = arduino Mode
  //if(digitalRead(UP_key) == 0) 
  Serial.println(digitalRead(DN_key));
  
  if(digitalRead(UP_key) == 1)
   {
     Serial.println("Up Key Input");
     flag.key_flag = 1;
   }
  return buf;
}

char key_byte_in()
{
  // byte 방식읽기 = MCU Mode
  char buf = 0;

  return buf;
}

void key_chk()
{
  // 키 판단
  flag.key_flag = 0;

  switch(key_buf)
  {
    case 0x01: // up Key
          cnt++;
          break;
  }
}

void setup() {
  DDRD = 0xff;  // fnd data out
  DDRB = 0xff;  // scan pulse out
  
  // mcu 방식
  DDRC  = 0x00; // 입력포트 설정
  PORTD = 0xff; // 풀업저항 활성화
/*
  // Arduino 방식
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
*/

  Serial.begin(9600); 
}

void loop() {
  
  key_buf = key_bit_in();
  if(flag.key_flag == 1) key_chk();
   fnd_dis(cnt);

   delay(1000);
/*
  // 실습2
  delay(1);
  time.time_loop++;
  if(time.time_loop >= 1000) //1sec
  {
    time.time_loop = 0;
    time.sec++;
    
    (tg_flag == 0) ? tg_flag = 1 : tg_flag = 0; // sec
    (tg_flag2 ==0) ? tg_flag2 = 1 : tg_flag2 = 1; // hour, min

    if(time.sec > 59) // 1min
    {
       time.sec = 0;
       time.min++;
       if(time.min > 59) // 1hour chk sum
        {
          time.min = 0;
          time.hour++;
          if(time.hour > 23) time.hour = 0;
        }
    }
  }  
  fnd_time(time.hour, time.min, time.sec);
*/
  
  /*
   // 실습1
  delay(1);
  t_loop++;
  if(t_loop > 300)
  {
    t_loop = 0;
    cnt++;
    //tg_flag = ~tg_flag;
    //if(tg_flag == 0) tg_flag = 1;
    //else tg_flag = 0;
    (tg_flag == 0) ? tg_flag = 1 : tg_flag = 0;
  }
   fnd_dis(cnt);
  */
  
  delay(1);
}
