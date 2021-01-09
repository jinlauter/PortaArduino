int botao1   = 42;

void setup ()
{ 
  Serial.begin(9600);
  pinMode(botao1, INPUT); 
}
 
void loop()
{
  if(digitalRead(botao1) == HIGH)
  {
    Serial.println("aperto");
  }
   else
   {
    Serial.println("deu bom não"); 
   }
  
}
