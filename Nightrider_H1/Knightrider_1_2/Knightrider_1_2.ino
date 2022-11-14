

int LED[8] = {2,3,4,5 ,6 , 7, 8, 9};  //LED's an den Pins 2-9
int Regler = A0;  //Poti an Pin A0

//für Potentiometer
int Reglerwert = 0; //Variable für den Reglerwert



int knightLight = 0;  //Variable für die LED
int knightCounter = 1;  //Variable für die Richtung


unsigned long lastDebounceTime = 0;        //Zeit in Millisekunden             
unsigned long debounceDelay = 1;  //Verzögerung in Millisekunden

void setup() {
 
  for (int i = 0; i <= 7; i ++)
  {
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();   //Zeit in Millisekunden  

 
  Reglerwert = analogRead(Regler);  //Reglerwert wird ausgelesen
  if (Reglerwert >= 1 && Reglerwert <= 1000) {  //Wenn der Reglerwert zwischen 1 und 1000 ist
    debounceDelay = Reglerwert; //Verzögerung wird auf den Reglerwert gesetzt
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay){  //Wenn die Zeit seit dem letzten Durchlauf größer als die Verzögerung ist
   
      
    lastDebounceTime = currentMillis; 
    digitalWrite(LED[knightLight], LOW);  
    knightLight = knightLight + knightCounter;

    
    if (knightLight > 7) {
      knightLight = 0;
    }
    digitalWrite(LED[knightLight], HIGH);
  }
}
