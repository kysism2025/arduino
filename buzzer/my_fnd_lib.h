/*
 * my_fnd.h
 *
 *  Created on: Oct 27, 2022
 *      Author: tj-bu
 */

#ifndef __MY_FND_LIB__
#define __MY_FND_LIB__

// K-공통
const unsigned char fnd_font[] =
{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,
   // C,    d,    A,    u,    T,    r,   b,  blk
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c, 0x00
};

// fnd maseg display
#define H   0x0a    // H   "            ==> index : 10
#define L   0x0b    // L   "
#define E   0x0c    // E   "
#define O   0x0d    //o display
#define P   0x0e    // P   "
#define F   0x0f    // F display        ==> index : 15
#define C   0x10    // C   "
#define D   0x11    // d   "
#define A   0x12    // A   "
#define U   0x13    // u   "
#define T   0x14    // t   "            ==> index : 20 
#define R   0x15    // r   "
#define b   0x16    // b   "            
#define BLK 0x17    // fnd blk display  ==> index : 23 

#define X100000  8
#define X10000   9

#define X1000    10
#define X100     11
#define X10      12
#define X1       13

extern char tg_flag = 0;
char scan = 0; // int8_t


fnd_time(char min_, char sec_)
{
  scan++;
  if(scan > 4) scan = 1;

  switch(scan)
  {
    case 1:
             // x1000 display
             d_out(X1, _OFF);
             byte_out(fnd_font[min_/10]);
             d_out(X1000, _ON);
       break;
       
    case 2:
             // x100 display
             d_out(X1000, _OFF);
             byte_out(fnd_font[min_%10] | 0x80); // dp on (���� �� ��ǥ��)                                   
             d_out(X100, _ON);
       break;
    
     case 3:
             // x10 display
             d_out(X100, _OFF);
             byte_out(fnd_font[sec_/10]);             
             d_out(X10, _ON);
       break;
       
     case 4:
             // x1 display
             d_out(X10, _OFF);
             (tg_flag == 1) ? byte_out(fnd_font[sec_%10] | 0x80) : byte_out(fnd_font[sec_%10] & 0x7f); 
             d_out(X1, _ON);
             
             /*
             
                1. ���� �ڿ� �� ǥ�� 
             	     1000 0000 (0x80) DOT                  
			     OR  0000 0110 (0x06) ����1 
			    ----------------------------------------
				     1000 0110 (0x86) ����1�� DOT�� ���ÿ� ǥ��
					 
				
				2. 1�� ��(.)�� ǥ���� �� (.) �����̱� 
					 1000 0110 (0x86) ����1�� DOT�� ���ÿ� ǥ�õ� ���� 
				AND	 0111 1111 (0x7F) ����ũó��
				----------------------------------------
				  	 0000 0110 (0x06) ����1��ǥ��!!      	    
				     
				     
             */
       break;
  } 

}

void fnd_dis_4(unsigned int dis)
{
  scan++;
  if(scan > 4) scan = 1;

  switch(scan)
  {
    case 1:
             // x1000 display
             d_out(X1, _OFF);
             byte_out(fnd_font[dis/1000]);
             d_out(X1000, _ON);
       break;
       
    case 2:
             // x100 display
             d_out(X1000, _OFF);
             if(tg_flag == 1) byte_out(fnd_font[dis%1000/100] | 0x80); // dp on
             else byte_out(fnd_font[dis%1000/100] & 0x7F); // dp OF                
             //(tg_flag ==1) ?  :
             d_out(X100, _ON);
       break;
    
     case 3:
             // x10 display
             d_out(X100, _OFF);
             if(tg_flag == 0) byte_out(fnd_font[dis%100/10]);
             else byte_out(fnd_font[BLK]);   // fnd_font[BLK] ==> 0x00
             d_out(X10, _ON);
       break;
       
     case 4:
             // x1 display
             d_out(X10, _OFF);
             byte_out(fnd_font[dis%10]);
             d_out(X1, _ON);
       break;
  } 
}

void fnd_dis_6(long d_buf)
{
  scan++;
  if(scan > 7) scan = 1;

  switch(scan)
  {
   case 1: // x100000
         d_out(X1, _OFF); //fnd off
         PORTD = fnd_font[d_buf/100000];
         d_out(X100000, _ON); //fnd ON
      break;

  case 2: // x10000
         d_out(X100000, _OFF); //fnd off
         PORTD = fnd_font[d_buf%100000/10000];
         d_out(X10000, _ON); //fnd ON
      break;

  case 3: // x1000
         d_out(X10000, _OFF); //fnd off
         PORTD = fnd_font[d_buf%10000/1000];
         d_out(X1000, _ON); //fnd ON
      break;   

  case 4: // x100
         d_out(X1000, _OFF); //fnd off
         PORTD = fnd_font[d_buf%1000/100];
         d_out(X100, _ON); //fnd ON
      break;  

  case 5: // x10
         d_out(X100, _OFF); //fnd off
         PORTD = fnd_font[d_buf%100/10];
         d_out(X10, _ON); //fnd ON
      break;  

  case 6: // x1
         d_out(X10, _OFF); //fnd off
         PORTD = fnd_font[d_buf%10];
         d_out(X1, _ON); //fnd ON
      break;           
  }
}

#endif /* INC_MY_FND_LIB_H_ */
