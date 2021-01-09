
int verde     = 24;
int amarelo   = 44;
int vermelho  = 28;
void setup()
{
      pinMode(verde,OUTPUT);
  pinMode(amarelo,OUTPUT);
  pinMode(vermelho,OUTPUT);
}



void loop()
{ 
  
digitalWrite(verde,HIGH);
delay(1000);
digitalWrite(verde,LOW);
digitalWrite(amarelo,HIGH);
delay(1000);
digitalWrite(amarelo,LOW);
digitalWrite(vermelho,HIGH);
delay(1000);
digitalWrite(vermelho,LOW);
digitalWrite(amarelo,HIGH);
delay(1000);
digitalWrite(amarelo,LOW);
 
 
  
  
}
