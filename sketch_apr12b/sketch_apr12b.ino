#define LED_1 6

void setup()
{
  // pinMode : 입출력 방향을 결정
  pinMode(LED_1,  OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN : 13
  
  DDRD = 0xff;
}

void loop()
{
  PORTD = 0xff;
  delay(500);
  PORTD = 0x00;
  _delay_ms(500);
  /*
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_1, HIGH); // digitalWrite(핀번호, 값 = HIGH(1), LOW(0)))
  delay(1000);               // 1 ~ 65535
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_1, LOW);
  delay(1000); 
  */
}