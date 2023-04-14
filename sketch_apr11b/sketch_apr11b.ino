int noisePin = A0;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(noisePin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(noisePin);
  Serial.println("value:" + String(value) + "\n");

  if(value <55) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }else{
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(3000);
  }
  delay(50);
}
