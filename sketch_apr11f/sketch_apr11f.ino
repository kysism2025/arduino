#include <IRremote.h>

int IRsensor = A1;
IRrecv irrecv(IRsensor);
decode_results results; // 수신한 데이터를 저장할 변수


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    Serial.println(results.value,HEX);
    irrecv.resume();
  }

}
