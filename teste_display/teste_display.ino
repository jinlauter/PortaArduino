#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int i;
int luzfundo=9;//CONTROLADOR DE LUZ DE FUNDO
void setup()
{
    pinMode(luzfundo, OUTPUT);
      digitalWrite(luzfundo,HIGH);
      lcd.begin(16, 2);
      lcd.noBlink();

}



void loop()
{ 
  for(i=0;i<9;i++)
  {
     lcd.clear();
    lcd.home();
    lcd.print("Boquera SA.");
    lcd.setCursor(0,1);
    lcd.print("Tenta nao");
    delay(400);
  }
  
 
 
 
  
  
}
