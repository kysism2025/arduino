// System Lib
#include <stdio.h>
#include <string.h>
#include <stdio.h>

// My Lib
#include "c:/mylib/my_arduino_lib.h"


// 32bit base (라즈, ARM프로세서)
int cnt = 0;  // short int 

char dest[100];
char d_buf[1000];

void setup() {
  Serial.begin(9600);
}

void loop() {

  cnt++;
  PORTD = cnt;
  sprintf(d_buf, "Counter=%4dEA\n", cnt);
  Serial.write(d_buf);
  _delay_ms(500);
}

/* 시리얼 수신 ISR */
// 인터럽트 : 이벤트가 발생해야 호출함!!!
void serialEvent() {
  unsigned char buf;

  // 실습 폴링방식 수신처리 loop back
  if(Serial.available() > 0) {
     Serial.println(Serial.readString()); // LOW레벨로 읽음
  }
}