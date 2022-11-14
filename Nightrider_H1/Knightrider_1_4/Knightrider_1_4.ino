

int LED[8] = {5 ,6 , 7, 8, 9, 10, 11, 12};

//Für den Lauf der LED's
int knightLight = 0; 
int knightCounter = 1;

unsigned long lastDebounceTime = 0;            
unsigned long debounceDelay = 10;

void setup() {
  for (int i = 0; i <= 7; i ++) {
    pinMode(LED[i], OUTPUT);
  }

  cli();            //stoppt alle Interrupts

  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;


  TCCR0A |= (1 << WGM02);                 //Timer auf mode 4
  TCCR0B |= (1 << CS00) | (1 << CS02);    //Cs00 und CS02 für Prescaler 1024 Bit
  OCR0A = 156;                            //ausgerechnete Wert eingesetzt
  TIMSK0 |= (1 << OCIE0A);                
  sei();                                  //Lässt Interrupts zu
}

ISR(TIMER0_COMPA_vect) {
  unsigned long currentMillis = millis();
  if ((currentMillis - lastDebounceTime) > debounceDelay){
   
  lastDebounceTime = currentMillis; 
  digitalWrite(LED[knightLight], LOW);  //vorherige LED aus
  knightLight = knightLight + knightCounter;

  if (knightLight > 7) {
    knightLight = 0;
  }
    digitalWrite(LED[knightLight], HIGH);
  }
}

void loop() {

}
