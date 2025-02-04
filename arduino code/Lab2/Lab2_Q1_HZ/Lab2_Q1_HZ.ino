// pin/variable definition
#define BUTTON_1 3
#define BUTTON_2 2
#define RLED 5
#define GLED 4
#define BLED 7

int gButton1Count = 0;
int gbutton2Count = 0;
int gFlagCheck = 0;

void setup() {
  // put your setup code here, to run once:
  // pin mode setup/interrupt setup
  Serial.begin(9600);
  pinMode(RLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1),isr_button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2),isr_button2,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  // if statement resetting checks/messing w/ LEDs
  if (gFlagCheck == 1){
    if (gButton1Count > gbutton2Count){
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED,LOW);
    digitalWrite(BLED, LOW);
    Serial.println("Red LED active.");
  }else if(gButton1Count == gbutton2Count){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED,LOW);
    digitalWrite(BLED, HIGH);
    Serial.println("Blue LED active.");
  }else if(gButton1Count < gbutton2Count){
    digitalWrite(RLED, LOW);
    digitalWrite(GLED,HIGH);
    digitalWrite(BLED, LOW);
    Serial.println("Green LED active.");
  }
    gFlagCheck = 0;
  }
}
// interrupts for button inputs
void isr_button1st(){
  gButton1Count +=1;
  gFlagCheck = 1;
}
void isr_button2nd(){
  gbutton2Count +=1;
  gFlagCheck = 1;
}