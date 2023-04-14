#define LED_0 0  // D0 Pin, TORTD.0
#define LED_1 1
#define LED_2 2
#define LED_3 3
#define LED_4 4
#define LED_5 5  // D5 Pin, TORTD.5
#define LED_6 6
#define LED_7 7  // D7 Pin, TORTD.7

#define d_out(pin, value) digitalWrite(pin, value);

#define bit_set(ADDRESS, BIT) (ADDRESS|=(1<<BIT)) // bit high
#define bit_clr(ADDRESS, BIT) (ADDRESS&=~(1<<BIT))// bit low
#define bit_chk(ADDRESS, BIT) (ADDRESS&(1<<BIT))  // bit check
#define bit_tg(PORT, BIT)     (PORT^=(1<<BIT))    // bit 토글

unsigned char cnt = 0;
unsigned char sbinary = 0x01;
unsigned char ebinary = 0x80;
unsigned char max = 255;

void byte_out(unsigned char data){
  d_out(LED_0, data%2);       // bit 0 = LSB(최하위핀)
  d_out(LED_1, data/2%2);     // bit 1
  d_out(LED_2, data/4%2);     // bit 2
  d_out(LED_3, data/8%2);     // bit 3
  d_out(LED_4, data/16%2);    // bit 4
  d_out(LED_5, data/32%2);    // bit 5
  d_out(LED_6, data/64%2);    // bit 6
  d_out(LED_7, data/128%2);   // bit 7 = MSB(최상위핀)
  Serial.print(String(data%2)    + ' ' + \
               String(data/2%2)  + ' ' + \
               String(data/4%2)  + ' ' + \
               String(data/8%2)  + ' ' + \
               String(data/16%2) + ' ' + \
               String(data/32%2) + ' ' + \
               String(data/64%2) + ' ' + \
               String(data/128%2)+ '\n');
}

/*
	아두이노 AVR 코딩 
    (
       입력용 : DDRA,  DDRB,  DDRC,  DDRD, 
       출력용 : PORTA, PORTB, PORTC, PORTD
    )
    ※ DDRn, PORTn: 
       I/O 포트의 입출력을 담당하는 레지스터의 입출력 방향을 지정하는 명령어
    
    ※ DDR : "Data Direct Register"
    
    ※ 핀의 기능 설정 : DDRx레지스터는 PORTx의 핀 방향을 결정한다.
                      DDxn비트가 0이면 Pxn핀은 입력으로 동작하고
                                1이면 Pxn핀은 출력으로 동작한다.
                                
                                
                                
    ---------------------------------------------------------
       DDxn        PORTxn     I/O   풀업저항         설명
    ---------------------------------------------------------
        0             0       입력      X       hi-Z
        0             1       입력      i       풀업 저항에 의해 입력 "1"
        1             0       출력      x       출력 "0"      
        1             1       출력      x       출력 "1"
    ---------------------------------------------------------
    
    ※ 10진수 - 16진수 - 2진수 변환표
    https://dgblossom99.tistory.com/30
*/     

void setup()
{
  // 실습1
  // pinMode : 입출력 방향을 결정
  // pinMode(LED_1,  OUTPUT);
  // pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN : 13
  
  // 실습2                     (8비트 데이터 앞의 B는 불리언(Boolean))
  //                            76543210  // Digital 핀번호                                 
  // DDRD = 0x40 = 64(10진수) = B01000000; // 입출력레지스터
  
  // 실습3 아두이노 코딩
  
  /*
  pinMode(LED_0,  OUTPUT);
  pinMode(LED_1,  OUTPUT);
  pinMode(LED_2,  OUTPUT);
  pinMode(LED_3,  OUTPUT);
  pinMode(LED_4,  OUTPUT);
  pinMode(LED_5,  OUTPUT);
  pinMode(LED_6,  OUTPUT);
  pinMode(LED_7,  OUTPUT);
  */
  
  // D: 입력
  // 실습4  마이크로프로세스 코딩
  DDRD = 0xff;
  
  //
  // DDxn = 0; 입력핀으로!!
  // DDxn = 1; 출력핀으로!!
  PORTD = 0x00; // 초기화
  cnt = 0;
  //Serial.begin(9600);
}


int arr1[8] = {0B00000001, 0B00000010, 0B00000100, 0B00001000, 0B00010000, 0B00100000, 0B01000000, 0B10000000};
int arr2[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int arr3[8] = {0B10000001, 0B01000010, 0B00100100, 0B00011000, 0B00011000, 0B00100100, 0B01000010, 0B10000001};
int arr4[8] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};
 

// D(생략) : 10진수, O : 16진수, B : 2진수
void loop()
{
  // 테스트3
  /*
  sbinary <<= 1;
  ebinary >>= 1;
  PORTD = sbinary;
  PORTD = ebinary;
  delay(1000);
  if(sbinary == 0x08) sbinary = 0b00000001;
  if(ebinary == 0x10) ebinary = 0b10000000;
  */

  // 테스트2
  /*
  if(cnt % 2 == 1) PORTD = !cnt;
  cnt++;
  _delay_ms(1000);
  */
  /*
  if(cnt % 2 == 1) PORTD = max - cnt;
  cnt++;
  _delay_ms(1000);
  */
  //PORTD = 0x00; 
  //delay(1000);

  // 테스트1 : 차례대로 램프 켜기
  PORTD = arr4[cnt];
  cnt++;
  if(cnt == 8) cnt = 0;
  delay(1000);
  
  
  // 실습6 MCU Bit
  //PORTD = ~PORTD; // 전체 깜빡이기
  //bit_tg(PORTD, LED_7);
  /*
  bit_set(PORTD, LED_0); //  bit high
  bit_clr(PORTD, LED_4); //  bit low
  bit_tg(PORTD,  LED_7);  //  토클
  d_out(LED_2, HIGH);
  delay(500);
  bit_set(PORTD, LED_4);
  d_out(LED_2, LOW);
  _delay_ms(500);
  */

  
  // 실습5 MCU Byte
  /*
  PORTD = cnt;
  _delay_ms(200);
  cnt++;
  */
  
  
  // 실습4
  // 아두이노 Byte제어
  // 짝수 카운터
  /*
  byte_out(cnt);
  cnt++;
  if(cnt > 255) cnt = 0;
  delay(500);
  */
    
  
  // 실습3
  /* 아두이노 Bit제어
  digitalWrite(LED_0, HIGH);
  digitalWrite(LED_5, HIGH); 
  digitalWrite(LED_2, LOW); 
  delay(1000);
  digitalWrite(LED_2, HIGH);
  delay(1000);
  */
  
  
  // 실습2
  /*
  PORTD = 0B00000001; //0xff; // 0x40; // B01000000; //0x40;
  _delay_ms(500);
  PORTD = B00000000; //0x00;
  _delay_ms(500);
  */
  
  /*
  // 실습1
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_1, HIGH); // digitalWrite(핀번호, 값 = HIGH(1), LOW(0)))
  delay(1000);               // 1 ~ 65535
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_1, LOW);
  delay(1000); 
  */
}