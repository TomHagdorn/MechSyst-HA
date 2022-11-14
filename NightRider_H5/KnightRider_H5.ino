#include <SPI.h>

int shiftPin = 10;  //Zum Reinschieben der Daten mit SH_CP des 74HC595
int storePin = 9;   //Übertragen auf Ausgabepin mit ST_CP
int dataPin = 8;    //wo die Daten hinsollen
int pot=A0;


int counter = 0;
unsigned long  currentTime=0;
unsigned long  previousTime=0;
//Maximum value for potenziometer is 1023
int pMax = 523;
int delayTime;



byte AussenNachInnen[] =
{
  B10000001, B01000010, B00100100, B00011000,
  B00100100, B01000010, B10000001
};


void setup() {
  pinMode(storePin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  
  

}

void loop()
{
  unsigned long currentTime = millis();


  byte LED = B10000000;

  // die letzte LED bleibt an
  for (int i = 0; i <= 7; i++)
  {
    // 
    int potvalue = analogRead(pot);
    // Ausgaberegister ausschalten
    digitalWrite(storePin, 0);
    // Print the value of the potentiometer
    Serial.println(potvalue);

    // Bits von rechts in das Register schieben
    shiftOut(dataPin, shiftPin, LSBFIRST, LED);

    // Ausgaberegister einschalten
    digitalWrite(storePin, 1);


    LED = LED >> 1;
    previousTime=currentTime;
    delayTime = 500 - (potvalue / pMax) * 400;
    //print the delay time
    Serial.println(delayTime);
    delay(delayTime);
    
  }
  
}