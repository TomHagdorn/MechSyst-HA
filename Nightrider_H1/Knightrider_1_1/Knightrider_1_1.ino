int LED[8] = {5 ,6 , 7, 8, 9, 10, 11, 12};


int knightLight = 0; 
int knightCounter = 1;

unsigned long lastDebounceTime = 0;           
unsigned long debounceDelayLED = 100;


void setup() {
  for (int i = 0; i <= 7; i ++)
  {
    pinMode(LED[i], OUTPUT); //LED's als Ausgang
  }
}

void loop() {
  unsigned long currentMillis = millis();   //Zeit in Millisekunden  
  //Wenn die Zeit seit dem letzten Durchlauf größer als die Verzögerung ist
  if ((currentMillis - lastDebounceTime) > debounceDelayLED){ 
   
    
    lastDebounceTime = currentMillis; //Zeit wird aktualisiert
    digitalWrite(LED[knightLight], LOW);  //vorherige LED aus
    knightLight = knightLight + knightCounter;  //LED wird um eins erhöht

    
    if (knightLight > 7 && knightCounter == 1) {    //Wenn die LED 7 erreicht hat neu starten
      knightLight = 0;
    }
    
    digitalWrite(LED[knightLight], HIGH); //LED einschalten
  }
}
