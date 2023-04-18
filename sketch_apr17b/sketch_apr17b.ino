#include "c:/mylib/my_arduino_lib.h"
#include "c:/mylib/my_fnd_lib.h"

uint8_t cnt = 0; // unsigned char

void setup() {
    DDRB = 0xff; // 8, 9번핀 추가함으로써 정의 추가
    DDRD = 0xff;
    Serial.begin(115200);
}

void loop() {
    // 실습2
    //PORTD = fnd_font[cnt]; // mcu방식
    byte_out(fnd_font[cnt]); // arduino 방식
    cnt++;
    if(cnt > 9) cnt = 0;
    
    Serial.println((cnt%10 + 0x30) -48);
    delay(500);
}
