//pin definition/variable setup
#define RLED 5
#define GLED 4
#define BLED 7
#define BUTTON_1 2
#define BUTTON_2 3
#define TIME 500

// arrays used for calculation
int gArray1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gArray2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int gArray3[10];
// button push counter
int gCounter = 0;
// button press checks
volatile int button1Flag = 0;
volatile int button2Flag = 0;

void setup() {
  // put your setup code here, to run once:
  // serial startup code/interrupt setup
  Serial.begin(9600);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_button1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2),isr_button2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button1Flag == 1){
    delay(TIME);
    gCounter += 1;
    if (gCounter == 1) {
// LED indicators
      Serial.print("Counter: ");
      Serial.println(gCounter);
      Serial.println("Enabling red LED.");
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED,LOW);
      digitalWrite(BLED, LOW);
    } else if (gCounter == 2) {
      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("Enabling green LED.");
      digitalWrite(RLED, LOW);
      digitalWrite(GLED,HIGH);
      digitalWrite(BLED, LOW);
    } else if (gCounter == 3) {
      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("Enabling blue LED.");
      digitalWrite(RLED, LOW);
      digitalWrite(GLED,LOW);
      digitalWrite(BLED, HIGH);
    } else {
      gCounter = 0;
      Serial.print("Counter: ");
      Serial.println(gCounter);      
      Serial.println("Disabling all LEDs.");
      digitalWrite(RLED, LOW);
      digitalWrite(GLED,LOW);
      digitalWrite(BLED, LOW);
      delay(TIME);
    }
    button1Flag = 0;
  }
// calculation flag
  if (button2Flag == 1) {
    Serial.println("Calculating...");
    Serial.println("Disabling all LEDs.");
    digitalWrite(RLED, LOW);
    digitalWrite(GLED,LOW);
    digitalWrite(BLED, LOW);
    delay(TIME);
// calculation loop for all indexes of arrays
    for (int i = 0; i < 10; i++) {
      if (gCounter == 1) { 
        gArray3[i] = gArray1[i] + gArray2[i];
      } else if (gCounter == 2) { 
        gArray3[i] = gArray1[i] - gArray2[i];
      } else if (gCounter == 3) {
        gArray3[i] = gArray1[i] * gArray2[i];
      }
    }
    Serial.println("Enabling all LEDs.");
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED,HIGH);
    digitalWrite(BLED, HIGH);
    delay(TIME);

    for (int i = 0; i < 10; i++) {
      Serial.print("array3");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(gArray3[i]);
      }
  button2Flag = 0;
  }
}
// interrupt for first button reading
void isr_button1(){
  if (digitalRead(BUTTON_1)){
    button1Flag= 1;
  }
}
// interrupt for second button reading
void isr_button2(){
  if (digitalRead(BUTTON_2)){
    button2Flag= 1;
  }
}