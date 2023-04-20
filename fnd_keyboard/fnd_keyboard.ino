// sys lib
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// my lib.h
#include "my_arduino_lib_v2_0.h"
#include "my_fnd_lib.h"

#define x10_en  18 //3 ==> A4 Pin
#define x1_en   19 //2 ==> A5 Pin

#define x1_dp   13
#define x10_dp  12

#define bit_set(ADDRESS, BIT) (ADDRESS |= (1<<BIT)) // bit hi 
#define bit_clr(ADDRESS, BIT) (ADDRESS &= ~(1<<BIT)) // bit low
#define bit_chk(ADDRESS, BIT) (ADDRESS & (1<<BIT))  // bit chak : MCU Method bit check
#define bit_tg(PORT, BIT) (PORT ^= (1<<BIT))  //bit �

#define d_out(pin, value) digitalWrite(pin, value)
#define d_in(pin) digitalRead(pin) 

#define ON  1
#define OFF 0
#define _ON  0
#define _OFF 1

char scan = 0;
char cnt  = 0; // 0xff 다음은 0

void fnd_dis_2(unsigned char dis) 
{
   scan++;
   scan > 2 ? scan = 1: scan++;

   switch(scan)
   {
     case 1: //x10
          d_out(x1_en, _OFF); // x1 off
          PORTB = dis/10;
          d_out(x10_en, _ON); // x10 on
      break;
          d_out(x10_en, _OFF); // x1 off
          PORTB = dis%10;
          d_out(x1_en, _ON); // x10 on      
     case 2: //x1

   }
}

// H/W Font 동기식 2자리
void setup() {

  DDRB  = 0xff; // out
  DDRC  = 0xff; // out
  PORTB = 0x00;

  d_out(x10_en, _OFF);
  d_out(x1_en, _OFF);

}

void loop() {
  fnd_dis2(cnt);
  cnt++;  
  delay(200);
  if(cnt > 99) cnt = 0;  
}
