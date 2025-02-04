
// define buttons and LEDs
#define BUTTON1 2
#define RLED 4 
#define GLED 5

#define TIMER1_COMPARE_VALUE 62500   // for 1 Hz
#define TIMER2_COMPARE_VALUE 16000   // for 10 Hz 

volatile unsigned int counter = 0;  // shared variable

// setup 
void setup() {
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);

  Serial.begin(9600);

  // 1hz task timer
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = TIMER1_COMPARE_VALUE;
  TCCR1B |= (1 << WGM12);  // CTC mode
  TCCR1B |= (1 << CS12);   // prescaler 256
  TIMSK1 |= (1 << OCIE1A); // enable Timer1 interrupt
  
  // 10hz task setup
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = TIMER2_COMPARE_VALUE;
  TCCR2A |= (1 << WGM21);  // CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // prescaler 1024
  TIMSK2 |= (1 << OCIE2A); // enable Timer2 interrupt

  interrupts(); // interrupts enabled
}

// Timer1 ISR (1hz task, incrementing)
ISR(TIMER1_COMPA_vect) {
  digitalWrite(GLED, !digitalRead(GLED)); // toggling Green LED
  counter++;  // increment main counter
}

// timer2 ISR (10Hz task)
ISR(TIMER2_COMPA_vect) {
  if (digitalRead(BUTTON1) == LOW) {
    digitalWrite(RLED, LOW); // red LED on if button pressed
  } else {
    digitalWrite(RLED, HIGH);  // red LED off otherwise
  }
}

// main loop
void loop() {
  static unsigned long lastPrintTime = 0;
  
  if (millis() - lastPrintTime >= 3000) { // every 3 seconds
    lastPrintTime = millis();
    Serial.print("Counter value: ");
    Serial.println(counter);
  }
}
