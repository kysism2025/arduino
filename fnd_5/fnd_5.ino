const unsigned char fnd_font[] = 
{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,
   // C,    d,    A,    u,    T,    r,   b,  blk
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c, 0x00
};

// fnd maseg display             
#define H   0x0a    // H   "           // index 10
#define L   0x0b    // L   "
#define E   0x0c    // E   "
#define O   0x0d    // o display
#define P   0x0e    // P   " 
#define F   0x0f    // F display       // index 15
#define C   0x10    // C   "
#define D   0x11    // d   "
#define A   0x12    // A   "  
#define U   0x13    // u   "
#define T   0x14    // t   "           // index 20
#define R   0x15    // r   "    
#define b   0x16    // b   "
#define BLK 0x00    // fnd blk display // index 23

#define bit_set(ADDRESS, BIT) (ADDRESS |= (1<<BIT))  // bit hi 
#define bit_clr(ADDRESS, BIT) (ADDRESS &= ~(1<<BIT)) // bit low
#define bit_chk(ADDRESS, BIT) (ADDRESS & (1<<BIT))   // bit chak
#define tbi(PORT, BIT) (PORT ^= (1<<BIT))  //bit 토글

// macro func
#define d_out(port, val) digitalWrite(port, val)
#define d_in(pin)        digitalRead(pin)

// fnd scan define
#define x1000  11
#define x100   10
#define x10    9
#define x1     8 

#define up_key 16
#define dn_key 17
#define run_key 18
#define mode_key 19


char scan = 0b00000001;
int t_loop = 0;
char key_buf;

struct fg
{
  char tg_flag;
  char run_flag;
  char key_flag;
  char rx_end_flag;
}flag = {0,0,0,0};

struct counter
{
  unsigned char cnt8;
  int cnt16;
  char mode_cnt;
}cnt = {0, 0, 0};


char key_rd_byte()
{
  char buf = 0;
  Serial.println("called key_rd_byte()");                                      
  if((PINC & 0b00111100) != 0b00111100) // 0x3c ( A2, A3, A4, A5핀이 전체 1인 경우)
  {
    Serial.println('k');
    buf = (PINC & 0b00111100);
    while((PINC & 0b00111100) != 0b00111100) // 버튼이 눌러진 경우
    {
      Serial.println('Y');
      fnd_dis(cnt.cnt16); // 숫자표시
    }

    flag.key_flag = 1;
    Serial.println("buf:" + buf);
  }
  return buf;
}


void key_chk(){
  
  char k;
  flag.key_flag = 0;
  Serial.println('c');
/*                             |
  	         X   X    A5   A4  |  A3   A2  A1  A0  
  	         0   0    1     1  |   1    1   0   0
                               |
A2연결(D16)   0   0    1     1  |   1    0   0   0    (0x38)
A3연결(D17)   0   0    1     1  |   0    1   0   0    (0x34)
A4연결(D18)   0   0    1     0  |   1    1   0   0    (0x4c) 
A5연결(D19)   0   0    0     1  |   1    1   0   0    (0x1c)
*/
  
  switch(key_buf) {
	case 0x38: // up key = d16
    	Serial.println("called 0x38");
    	((flag.run_flag == 0) && (cnt.mode_cnt == 1 || cnt.mode_cnt == 4)) ? cnt.cnt16++: 1; k = 1 ;
    	break;
    
    case 0x34: // dn key = d17
    	Serial.println("called d17");
    	((flag.run_flag == 0) && (cnt.mode_cnt == 1)) ? cnt.cnt16--: k = 1;
    	break;

    case 0x2c: // run key = d18
    	Serial.println("called d18");
    	flag.run_flag == 0 ? flag.run_flag = 1: flag.run_flag = 0;
    	break;

    case 0x1c: // mode key = d19
    	Serial.println("called d19");
    	cnt.mode_cnt > 4 ? cnt.mode_cnt = 1 : cnt.mode_cnt++;
    	break;
    
  }
}

void fnd_dis(unsigned int dis_buf)
{

  // 0되면 이면 전류가 흐르기때문에 의도했던것과 반대로 글씨가 표시됨
  // 그래서, inverse됨!
  PORTB = ~scan; 

  PORTD = 0x00;
  
  switch(scan)
   {
     case 0b00000001:  //x1
    	  d_out(x10, 1);	 
          //PORTD = fnd_font[cnt%10];
          (flag.tg_flag == 1) ? 
            	PORTD = fnd_font[cnt.cnt16%10] | 0x80 :     // 숫자 + Dot표시
               		PORTD = fnd_font[cnt.cnt16%10] & 0x7f;  // 숫자만 표시 (Dot 제외) 
		  d_out(x1, 0);
          break;     

     case 0b00000010:  //x10
    	  d_out(x100, 1);
    	  //PORTD = fnd_font[cnt.cnt16%100/10];
          (flag.tg_flag == 1) ? 
            PORTD = fnd_font[cnt.cnt16%100/10] : // 10의 자리표시
    			fnd_font[BLK];                   // 0으로 표시함으로써 깜빡임처리
    	  d_out(x10, 0);
          break;     

     case 0b00000100:  //x100
    	  d_out(x1000, 1);
      	  PORTD = fnd_font[cnt.cnt16%1000/100] | 0x80;
    	  d_out(x100, 0);
          break;     
     
     case 0b00001000:  //x1000
    	  d_out(x1, 1);
          PORTD = fnd_font[cnt.cnt16/1000];
    	  d_out(x1000, 0);
          break;     
   } 

   scan <<= 1;
   if(scan == 0b00010000) scan = 0b00000001;  
}

// 빨리 표시되는 것을 방지하기 위해 delay 처리
int time_cnt(int loop_nb, int val) {
  delay(1);
  t_loop++;

  if(t_loop > loop_nb) {
    t_loop = 0;
    val++;
  }
  return val;
}

void up_cnt_func() {
  cnt.cnt16 = time_cnt(200, cnt.cnt16);
  fnd_dis(cnt.cnt16);
  Serial.println("called up_cnt_func()");
}

void time_func() {
	Serial.println("called time_func()");
}

void gugudan_func() {
	Serial.println("called gugudan_func()");
}

void dn_cnt_func() {
	Serial.println("called dn_cnt_func()");
}

void setup()
{
  DDRD = 0xff; // fnd data
  DDRB = 0xff; // scan pulse
  DDRC = 0xff; // input mode
  DDRB = 0xff; // pullup en
  
  Serial.begin(9600);
}

void loop()
{
  
  // 눌러진 스위치의 값 읽기
  key_buf = key_rd_byte(); 
  
  // 받아온 키값에 따라 digit + 또는 -, Flag값, Mode 값의 변경
  if(flag.key_flag == 1) key_chk();
  
  if(flag.run_flag == 1){
    switch(cnt.mode_cnt){
      case 1: up_cnt_func();  break; 
      case 2: time_func();    break; 
      case 3: gugudan_func(); break; 
      case 4: dn_cnt_func();  break; 
    }
  }

  fnd_dis(cnt.cnt16);
  
  //=================================
  // 숫자가 빨리 Display되는 것을 막음
  //=================================
  delay(1);
  t_loop++;
  if(t_loop > 200)
  {
   t_loop = 0; 
   cnt.cnt16++;
    
    // Dot 깜빡임 처리를 위해 Flag를 반전!!
   (flag.tg_flag == 0) ? flag.tg_flag = 1 : flag.tg_flag = 0;
  }
}
