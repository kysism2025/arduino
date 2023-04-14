

#ifndef __My_serial_LIB__
#define __My_serial_LIB__


#include "io.h"  

void uart_init(void)
{
  UCSR0A = 0x00;  // flag  clr, ��Ƽ���μ��� ���
  UCSR0B = 0x98; //rx,tx en, rx int on
  UCSR0C = 0x06; //n-p,1-stop
  UBRR0H = 0x00;
  UBRR0L = 8; //103; //8mhz, 9600, 103 - 16mhz, 47 = 7.2738mhz, 8:115200
}  

// tx redy chk
char tx_chk(void)
{                
   // uart 0
    if(bit_chk(UCSR0A, 5)) return 1; // UCSR0A, UDRE0 bit chk ==>> �۽��غ�� OK
    else return 0; // NO REDY
}

// 1 byte char tx
void tx_send(unsigned char tx_data)
{
  while(tx_chk() == 0);
  // while(!(UCSRA & 0x20));
  
  if(tx_chk() == 1)  
   {
     UDR0 = tx_data;  // uart 0     
   } 
}

// String Tx
void tx_str(unsigned char *tx_d) 
{   
  //unsigned char buf;         
  // uart 
  while(*tx_d != '\0')
  {
    tx_send(*tx_d);
    tx_d++;
  }
} 




#endif


