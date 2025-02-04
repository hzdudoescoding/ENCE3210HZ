// pin definition
#define RLED 5
#define GLED 4
#define BLED 7
#define BUTTON 2
#define gTime 250 //ms

volatile int gFlagCheck = 0;

void setup() {
  // put your setup code here, to run once:
  // pinmode code/interrupt setups
  Serial.begin(9600);
  pinMode (RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED,OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON),isr_button,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  // primary code, only set off by interrupt listed below
  if (gFlagCheck == 0){
   digitalWrite(RLED, LOW);
   digitalWrite(GLED,LOW);
   digitalWrite(BLED,LOW);
  }else if (gFlagCheck == 1){
    
    Serial.println("Red");
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW); 
    digitalWrite(BLED,LOW);  
    delay(ggTime);

    Serial.println("Red, Green");
    digitalWrite(GLED,HIGH);
    delay(gTime);

    Serial.println("Red, Green, Blue");
    digitalWrite(BLED,HIGH);
    delay(gTime);

    Serial.println("Green, Blue");
    digitalWrite(RLED, LOW);
    delay(gTime);

    Serial.println("Blue");
    digitalWrite(GLED, LOW);
    delay(gTime);

    Serial.println("RB");
    digitalWrite(RLED, HIGH);
    delay(gTime);
// flag reset upon second button push
  }else if (gFlagCheck == 2){
    gFlagCheck = 0;
  }

}
void isr_button(){
//if button pushed, start code
  if (digitalRead(BUTTON)){
    gFlagCheck += 1;
  }
}