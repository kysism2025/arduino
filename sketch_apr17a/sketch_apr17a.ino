#include "c:/mylib/my_arduino_lib.h"
#include "c:/mylib/my_fnd_lib.h"

// Binary 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
const int arr1[10] = {
                0B00111111, 0B00000110, 0B01011011, 0B01001111, 0B01100110, 
                0B01101101, 0B01111101, 0B00000111, 0B01111111, 0B01100111
              };

// 16진수 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
const int arr2[10] = {
                0x3f,0x06,0x5b,0x4f,0x66,
                0x6d,0x7d,0x27,0x7f,0x6f
              };              


void setup() {
    DDRD = 0xff;
}

void loop() {
    int i = 0;
    for(i = 0; i < 10; i++) {
      PORTD = arr2[i];
      delay(500);
    }
}
