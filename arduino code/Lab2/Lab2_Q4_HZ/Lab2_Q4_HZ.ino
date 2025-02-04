//global variables & pinmodes
#define BUTTON 2
int x[10]={1,2,3,4,5,6,7,8,9,10};
int y[10] = {};
volatile int gFlag;
void setup() {
  // put your setup code here, to run once:
  //pinmode setup & interrupts
  Serial.begin(9600);
  pinMode(BUTTON,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON),isr_button,CHANGE);
}
void loop() {
  // put your main code here, to run repeatedly:
  // flag check to filter array
  if (gFlag == 1){
    // setup for filtering
    for (int n=0;n<10;n++){
      y[n] = 2 * x[n]-x[n-1];
      Serial.println(y[n]);
    }
    // reset gFlag
    gFlag = 0;
  }
}
  //interrupt to turn on flag for button
void isr_button(){
  if (digitalRead(BUTTON)){
    gFlag= 1;
  }
}