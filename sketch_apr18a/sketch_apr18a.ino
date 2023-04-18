#include "c:/mylib/my_arduino_lib.h"
#include "c:/mylib/my_fnd_lib.h"

uint16_t cnt = 0;  // unsigned char
uint16_t t_loop = 0;

#define UP_KEY   0x0e
#define DN_KEY   0x0d
#define RUN_KEY  0x0b
#define MODE_KEY 0x07

#define UP_KEY1   14
#define DN_KEY1   15
#define RUN_KEY1  16
#define MODE_KEY1 17

char run_flag = 0;
char gu = 1;
char dan = 1;
char d_buf;
char mul;

struct clock
{
  int t_loop;
  char hour;
  char min;
  char sec;
};

struct k_in
{
  char key_buf;  // key data
  char key_flag; // confirm key input
  char key_d;    // 
  char mode_cnt; // 1:up, 2:구구단, 3:시계, 4: 홀수 down
};

struct clock time = {0, 1, 24, 30};
struct k_in key   = {0, 0, 0, 0};

char key_rd_byte() 
{
  char buf;

  if((PINC & 0x0f) != 0x0f)
  {
    buf = PINC & 0x0f;   
    while((PINC & 0x0f) != 0x0f){
      fnd_dis_4(cnt);
      delay(1);
    }
        
    key.key_flag = 1;
    Serial.print(cnt);
  }

  return buf;   
}

void key_bit(){
  char buf = 0;

  if(d_in(UP_KEY1) == 0)   buf = 0x0e;
  if(d_in(DN_KEY1) == 0)   buf = 0x0d;
  if(d_in(RUN_KEY1) == 0)  buf = 0x0b;
  if(d_in(MODE_KEY1) == 0) {
    buf = 0x07;
  }else{
    buf = 0;
  }

  // (d_in(UP_KEY1) == 0) ? buf = 0x0e;
  // (d_in(DN_KEY1) == 0) ? buf = 0x0d;
  // (d_in(RUN_KEY1) == 0) ? buf = 0x0b;
  // (d_in(MODE_KEY1) == 0) ? buf = 0x07: buf = 0;
  
  if(buf != 0) key.key_flag = 1;
  return buf;
}

void key_chk()
{
  key.key_flag = 0;

  switch(key.key_buf)
  {
    case UP_KEY:  // 0x0e
      if(run_flag ==0 ) cnt++;
      break;
  
    case DN_KEY:  // 0x0d       
      if( run_flag==0 ) cnt--;
      break;       

    case RUN_KEY: // 0x0b
         (run_flag == 0) ? run_flag = 1 : run_flag = 0;
      break;

    case MODE_KEY: // 0x07
         key.mode_cnt++;
         if(key.mode_cnt > 4) key.mode_cnt = 0;
      break;
  }
}

void gugudan() {
  _delay_ms(1);

  //run_flag = 0;
  /*
  time.t_loop++;
  if(time.t_loop > 100)
   {
    time.t_loop = 0;
    if(dan > 9) {
       (dan > 9)? dan = 1: dan++;
       gu = 1;
    } 
    gu++;
    mul = dan * dan;
  }
  */
  //fnd_dis_4(dan*1000 + gu*100 + mul);

  //sprintf(d_buf, "%d x %d = %d\n", dan, gu, mul);
  //Serial.println(d_buf);
  Serial.println("gugudan");
}

void setup() {

  DDRB  = 0xff;
  PORTB = 0xff;
  DDRD  = 0xff;
  Serial.begin(115200); // 9600

/* 아두이노
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
*/
  DDRC  = 0x00;  // 입력으로 사용
  PORTC = 0xff;  // 풀업저항
}

// void up_cnt()
// {
  
//   run_flag = 0;
//   _delay_ms(1);
//   time.t_loop++;
//   if(time.t_loop > 100)
//    {
//     time.t_loop = 0;
//     cnt++; 
//   }
//   Serial.println(cnt);
//   //fnd_dis_4(cnt);
// } 

void up_cnt()
{
  run_flag = 0;
  do{
      _delay_ms(1);
      time.t_loop++;
      if(time.t_loop > 100)
      {
        time.t_loop = 0;
        cnt++; 
      }
      Serial.println(cnt);
      fnd_dis_4(cnt);
      key.key_buf = key_rd_byte();
      if(key.key_flag == 1) break;

  }while(key.key_flag == 0);

  // for(; cnt <= 9999;){
  //   delay(1);
  //   time.t_loop++;
  //   if(time.t_loop > 100) {
  //     time.t_loop = 0;
  //     cnt++;
  //   }
  //   // fnd_dis_4(cnt);
  //   key.key_buf = key_rd_byte();
  //   if(key.key_flag == 1) break;
  // }
} 


void loop() {

  // 실습5
  if(key.key_flag == 0) key_rd_byte(); //key.key_buf = key_bit();
  if(key.key_flag == 1) key_chk();

  if(run_flag == 1)
  {
    switch(key.mode_cnt){
      case 1: up_cnt(); break;
      case 2: gugudan(); break;
      //case 3: ttime(); break;
      //case 4: odd_dn_cnt(); break;
    }
  }else{
    fnd_dis_4(cnt);
  }

  // 실습4
  /*
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
  */
  //fnd_dis_4(((time.min/10)*1000) + ((time.min%10)*100) + ((time.sec/10)*10) + (time.sec%10));
  //fnd_dis_4(fnd_time(time.min, time.sec));
//
  // 실습3
  //delay(1);
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
  //fnd_dis_4(cnt);
  

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