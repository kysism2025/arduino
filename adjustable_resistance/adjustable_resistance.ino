#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_arduino_lib_v2_0.h"

#define dvm A0  // 가변저항 14 : Digital Input, A0 : Analog Input
#define cds A1  // 포토센서
#define dim 10  // LED발기 조절
#define ry  11  // Relay의 제어
#define jx  A2  // 조이스틱 X
#define jy  A3  // 조이스틱 Y
#define jsw 12  // 조이스틱 스위치

int ad_buf, ad_buf2, ad_buf3, ad_buf4, ad_volt;
float ad_v, ad_v2;
unsigned char led_buf; // unsigned로 정의 되어야 0~255 제대로 표현

// 출력용
char d_buf1[50];  // 가변저항 아날로그값 VOLT
char d_buf2[50];  // 포토센서값
char d_buf3[50];  // LED조절

void setup() {

  DDRD = 0xff;
  DDRB = 0xff;

  pinMode(A0,  INPUT);    // 가변저항
  pinMode(A1,  INPUT);    // 포토센서
  pinMode(A2,  INPUT);    // 조이스틱X
  pinMode(A3,  INPUT);    // 조이스틱Y
  pinMode(jsw, INPUT_PULLUP);   // 조이스틱Y
  pinMode(ry,  OUTPUT);   // Relay

  // 풀업저항 표현방법
  // DDRC = 0x00;
  // PORTC = 0xff;  

  Serial.begin(9600);
}

void loop() {

  // 가변저항 아날로그값 읽기
  ad_buf  = analogRead(dvm);
  ad_v    = ((5.0/1024) * ad_buf);
  ad_volt = ((int)(ad_v * 1000))/1000;
 
  sprintf(d_buf1, "Ad_Low Data=%4d, Volt=%4dV", ad_buf, ad_volt);
  Serial.print(d_buf1);
  Serial.print(" ");

  byte_out((int)map(ad_buf, 0, 1023, 0, 255));
  led_buf = (int)map(ad_buf, 0, 1023, 0, 255);

  // 가변저항의 크기에 따라 LED발기 조절
  analogWrite(dim, ad_buf);

  // 가변저항에 따라 변하는 값을 조절  
  sprintf(d_buf3, ", LED buff=%4d", led_buf);
  Serial.print(d_buf3);
  Serial.print(" ");

  // 2.5V이상이면  부저를 울리도록 처리
  // 가변저항 값이 1024중 512를 넘는 경우 Buzzer의 소리가 발생하도록 처리, 아닌 경우 소리가 안남
  (ad_buf > 512)? d_out(ry,1) : d_out(ry,0);

  Serial.print(" <<  ");
  Serial.print(jsw);
  Serial.print(" >>  ");

  // 조이스틱 스위치
  (jsw == 0) ? d_out(ry, 1) : d_out(ry, 0);

  // 광센서의 신호를 읽어서 광센서 기본값표시
  ad_buf2 = analogRead(cds);
  sprintf(d_buf2, ", CDS : %d\n", ad_buf2);
  Serial.print(d_buf2);

  ad_buf3 = analogRead(jx);
  Serial.print(" JX = ");
  Serial.print(ad_buf3);
  Serial.print(", ");

  ad_buf4 = analogRead(jy);
  Serial.print(" JY = ");
  Serial.print(ad_buf4);
  Serial.print(", ");

  // Serial.write(ad_volt/1000 + 0x30);
  // Serial.print('.');
  // Serial.write(ad_volt/1000%100 + 0x30);
  // Serial.write(ad_volt%100/10 + 0x30);
  // Serial.write(ad_volt%10+ 0x30);
  // Serial.println('V');
  // delay(500);
  
}
