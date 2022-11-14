
int LED[8] = {2, 3, 4, 5 ,6 , 7, 8, 9, };
int buttonPin = 1;


int knightLight = 0; 
int knightCounter = 1;


int buttonState;
int lastButtonstate = LOW;


unsigned long lastDebounceTime = 0;            
unsigned long debounceDelayLED = 100;


void setup() {
  
  for (int i = 0; i <= 7; i ++)
  {
    pinMode(LED[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();     
  int reading = digitalRead(buttonPin);

  if ((currentMillis - lastDebounceTime) > debounceDelayLED){
   
    lastDebounceTime = currentMillis; 
    digitalWrite(LED[knightLight], LOW);  //vorherige LED aus
    knightLight = knightLight + knightCounter;

    if (knightLight > 7 && knightCounter == 1) {
      knightLight = 0;
    }

    if (knightLight < 0 && knightCounter == -1) {
      knightLight = 7;
    }
    if (reading == HIGH) {
      buttonState = reading; 
      if (knightCounter == 1) {
        knightCounter = -1;
      } 
      else {
        knightCounter = 1;
      }     
    }
    digitalWrite(LED[knightLight], HIGH);
  }
}
