#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display



int PinRed=7;
int PinYellow=6;
int PinGreen=5;

int PinButton=8;

int inputState = 0;

unsigned long  currentTime=0;
unsigned long  previousTime=0;
unsigned long  Timer =0;


void setup() 
{
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Rot");               // print initaial color to lcd

  pinMode(PinRed,OUTPUT);
  pinMode(PinYellow,OUTPUT);
  pinMode(PinGreen,OUTPUT);
  pinMode(PinButton, INPUT_PULLUP);
  Serial.begin(9600);
  
}

class Ampel
{
  private:
  unsigned long cTime;
  unsigned long  pTime;
  public:
    Ampel(unsigned long& ct, unsigned long& pt):cTime(ct),pTime(pt){} 
    void Rot(); 
    void RotGelb();
    void Gelb();
    void Gruen();

};

void Ampel::Rot()
{
  digitalWrite(PinRed,HIGH);
  digitalWrite(PinYellow,LOW);
  digitalWrite(PinGreen,LOW);
  Serial.println("Rot");


if(digitalRead(PinButton)==HIGH)
{
    if(cTime-pTime>=5000)
    {
      previousTime=currentTime;
      lcd.clear();
      lcd.print("RotGelb");
      ++inputState;

      
    }
  }
}

void Ampel::RotGelb()
{
  
  digitalWrite(PinRed,HIGH);
  digitalWrite(PinYellow,HIGH);
  digitalWrite(PinGreen,LOW);
  Serial.println("Rotgelb");

  
    if(cTime-pTime>=5000)
    {
      previousTime=currentTime;
      lcd.clear();
      lcd.print("Gruen");
      ++inputState;


    }
}

void Ampel::Gelb()
{   
  digitalWrite(PinRed,LOW);
  digitalWrite(PinYellow,HIGH);
  digitalWrite(PinGreen,LOW);
  Serial.println("Gelb");

  
  if(cTime-pTime>=5000)
  {
    previousTime=currentTime;
    lcd.clear();
    lcd.print("Rot");
    inputState=0;

  }
 
}

void Ampel::Gruen()
{
  digitalWrite(PinRed,LOW);
  digitalWrite(PinYellow,LOW);
  digitalWrite(PinGreen,HIGH);
  Serial.println("Gruen");


    if(cTime-pTime>=15000)
  {
    previousTime=currentTime;
    lcd.clear();
    lcd.print("Gelb");
    ++inputState;
  }
}



void loop() 
{
  //print the state of the button
  Serial.println(digitalRead(PinButton));
  Serial.println('Hello World');
  currentTime=millis();
  Ampel Zustand(currentTime,previousTime);

  switch(inputState)
  {
    case 0:
    Zustand.Rot();
    break;
 
    case 1:
    Zustand.RotGelb(); 
    break;

    case 2:
    Zustand.Gruen();
    break;

    case 3:
    Zustand.Gelb();
    break;
  }
}