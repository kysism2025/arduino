// System Lib
#include <stdio.h>
#include <string.h>
#include <stdio.h>

// My Lib
#include "c:/mylib/my_arduino_lib.h"

// 32bit base (라즈, ARM프로세서)
int cnt = 0;  // short int 

char d_buf[1000];

volatile char rx_end_flag = 0;
volatile char rx_cnt = 0;
volatile unsigned char rx_buf[20];

void com_chk() {
  rx_end_flag = 0;
  sprintf(d_buf, "%s", rx_buf);
  Serial.println(d_buf);
  
  PORTD = rx_buf[0]; // 그대로 들어옴
  
  // (d_buf[0] & 0x0f); // 비트연산처리됨!!
  // 4 ==> 0x34
  // 8 ==> 0x38
  // 0x34 ==> 0011 0100
  // 0x0f ==> 0000 1111 &연산
  // ---------------------
  //          0000 0100   ==> 3번핀에 신호가 들어옴!!
  
  // 0x38 ==> 0011 1000
  // 0x0f ==> 0000 1111 &연산
  // ---------------------
  //          0000 1000  ==> 4번핀에 신호가 들어옴!!
  

   
  memset(rx_buf, 0, sizeof(char)*20);
}

void setup() {
  Serial.begin(9600);

  DDRD = 0xff;

  // rx_buf 메모리를 0으로 초기화하는데 20byte까지만 초기화 한다.
  memset(rx_buf, 0, sizeof(char)*20);
}

// 1. memset
// void * memset ( void * ptr, int value, size_t num );
// memmove(ptr, 값, 메모리공간 크기)
// 메모리 블록을 채운다.  ptr로 시작하는 메모리 주소로부터 num 개의 바이트를 value 값으로 채운다. 

// 2. memmove
// void * memmove ( void * destination, const void * source, size_t num );
// memmove(복사받을 메모리공간, 복사할 메모리공간, 메모리공간 크기)
// 복사 받을 메모리 공간에 복사할 메모리 공간을 복사할 크기만큼 복사한다.

void loop() {

  if(rx_end_flag == 1) com_chk();

  // cnt++;
  // PORTD = cnt;
  // sprintf(d_buf, "Counter=%4dEA\n", cnt);
  // Serial.write(d_buf);
  _delay_ms(50);

}

/* 시리얼 수신 ISR */
// 인터럽트 : 이벤트가 발생해야 호출함!!!
void serialEvent() {
  
  // volatile키워드를 사용안해도 무방하지만 인터럽트 사용시 형식상 
  unsigned char buf;

  // 실습 8
  buf = Serial.read();

  Serial.println(Serial.read());

  if(buf == '\n') {
  //  if(buf == 0x0a) {
      rx_end_flag = 1;
      rx_cnt = 0;

  }else{
      rx_buf[rx_cnt] = buf;
      rx_cnt++;
  }
}


