// System Lib
#include <stdio.h>
#include <string.h>
#include <stdio.h>

// My Lib
#include "c:/mylib/my_arduino_lib.h"

// 32bit base (라즈, ARM프로세서)
int cnt = 0;  // short int 

char origin[] = "BlockDMask\n";
char dest[100];
char d_buf[1000];

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  sprintf(d_buf, "Counter=%4dEA\n", cnt);
  strncpy(dest, origin, sizeof(origin));

  Serial.write(d_buf);
  Serial.write(dest);

  _delay_ms(500);
  cnt++;
  
}
