#include "c:/mylib/my_arduino_lib.h"

unsigned int cnt = 0;
char arr1[10];
char arr2[10];

void setup() {

  // 하나의 프로그램은 하나의 COM PORT를 점유하고 있어야 함!!!
  // 초당 몇 비트의 속도로 통신을 할지 설정하는 값
  Serial.begin(9600);

  DDRD = 0xff;
}

void loop() {
  
    byte_out(cnt);

    // Serial.print(56);을 실행하면  ‘5’와 ‘6’ 각각의 ASCII 값인 십진수 <53><54>를 전송하고 
    // 수신쪽에서는 십진수 <53>에 해당하는 문자 ‘5’와 <54>에 해당하는 문자 ‘6’을 출력합니다.
    // 실습4 (아두이노 --> 컴퓨터)
    // Serial.print("Song@#%123\n");
    // Serial.print("test2");
    // Serial.println("홍길동");

    // Raw레벨 출력
    // Serial.write : 아두이노 시리얼 모니터는 수신된 데이터를 ASCII 코드의 문자로 변화하여 출력합니다
    Serial.write(cnt/1000 + 48); // 48(10진수)
    //Serial.write('\n');
    Serial.write(cnt%1000/100 + 48);
    //Serial.write('\n');
    Serial.write(cnt%100/10 + 48);
    //Serial.write('\n');
    Serial.write(cnt%10 + 48);
    Serial.write('\n');

    PORTD = cnt;
    cnt++;
    
    _delay_ms(1000);
    //Serial.println( itoa(cnt, arr1, 2));
    //Serial.println(cnt, BIN);
    if(cnt == 255) cnt = 0;
  
}
