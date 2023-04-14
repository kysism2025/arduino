void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  Serial.println("photoSeneor" + String(value));

  if(value > 900) {
    digitalWrite(11, HIGH); // 빛이 어두우면 가로등을 켠다.
    digitalWrite(12, HIGH); // 빛이 어두우면 가로등을 켠다.
    digitalWrite(13, HIGH); // 빛이 어두우면 가로등을 켠다.
  }else{
    digitalWrite(11, LOW); // 빛이 밝으면 가로등을 끈다.
    digitalWrite(12, LOW); // 빛이 밝으면 가로등을 끈다.
    digitalWrite(13, LOW); // 빛이 밝으면 가로등을 끈다.
  }
}
