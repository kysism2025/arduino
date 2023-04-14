#include <IRremote.h>
int input_pin = 2;
IRrecv irrecv(input_pin);
decode_results signals;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&signals)){

    Serial.println(signals.value.HEX);

    Serial.println(signals.bits.DEC);

    irrecv.resume();

  }
}
