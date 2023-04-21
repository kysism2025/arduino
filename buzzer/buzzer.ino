#include <LiquidCrystal_I2C.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "my_arduino_lib_v2_0.h"

#define C 262 // 도
#define D 294 // 레
#define E 330 // 미
#define F 349 // 파
#define G 392 // 솔
#define A 440 // 라 
#define B 494 // 시 
#define bz 2

int tones[] = {
                // 도도솔솔라라솔파파미미레레도
                C,C,F,F,A,A,G,F,F,E,E,D,D,C,
                // 솔솔파파미미레솔솔파파미미레
                G,G,F,F,E,E,D,G,G,F,F,E,E,D,
                // 도도솔솔라라솔파파미미레레도
                C,C,G,G,A,A,G,F,F,E,E,D,D,C,'\0'};

void setup() {
  pinMode(2, OUTPUT);
 // d_out(bz, 1); // 2번핀에 input(+) 소리나게 처리
}

void loop() {
    int cnt = 0;
    while(tones[cnt] != '\0'){
        tone(bz, tones[cnt]);
        delay(500);
        cnt++;
    }
    noTone(bz); // 끄기
}
