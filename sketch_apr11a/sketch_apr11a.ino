 
int segValue[10][8] = {
   {1,1,1,1,1,1,0,0}, //0
   {0,1,1,0,0,0,0,0}, //1
   {1,1,0,1,1,0,1,0}, //2
   {1,1,1,1,0,0,1,0}, //3
   {0,1,1,0,0,1,1,0}, //4
   {1,0,1,1,0,1,1,0}, //5
   {1,0,1,1,1,1,1,0}, //6
   {1,1,1,0,0,0,0,0}, //7
   {1,1,1,1,1,1,1,0}, //8
   {1,1,1,1,0,1,1,0}  //9    
};
int segPin[8]={2,3,4,5,6,7,8,9}; //사용핀{a,b,c,d,e,f,g,dp} 순서대로임
int speakerpin =11;
void setup() {

  for(int i=0;i<=9;i++){
    pinMode(segPin[i], OUTPUT);
  }
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  initLed();
  Serial.begin(9600);
}

void loop() {
  
  int button = digitalRead(12);
  Serial.println(button);
  
  if(button == LOW){
    digitalWrite(13, HIGH);
    tone(speakerpin, 500, 2000);
	  for(int i=0;i<10;i++){
    	for(int j=0;j<8;j++){
       		digitalWrite(segPin[j], segValue[i][j]);        
    	}
    	delay(1000);
  	}    
  }
}

void initLed(){
  
  for(int j=0;j<8;j++){
    digitalWrite(segPin[j], 1);        
  }

}