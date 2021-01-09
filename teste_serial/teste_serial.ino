int usado = 0;
int verde     = 24;
int amarelo   = 44;
int vermelho  = 28;

char tecla;
char buff[4];
String string, stringt = "", stringh = "";
String feed="toma";
void setup() {
  Serial.begin(9600);
  pinMode(verde,OUTPUT);
   pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);
}
void loop() {
if(Serial.available())
{
    tecla = Serial.read();
    if (tecla == 'a')
    {
      if(usado==1 || usado ==2)
      {
        digitalWrite(vermelho, LOW);
        digitalWrite(amarelo, HIGH);
        digitalWrite(verde, HIGH);
        feed="Reativado";
        Serial.println(feed);
        delay(4000);
        tecla = 'p';
        usado = 0;
      }
      else
      {
        feed="Já ta ativadao";
        Serial.println(feed);
      }
      loop();
    }
    if(tecla=='b')
    {
      tecla=='p';
    }
    if(tecla=='c')
    {
      tecla='p';
    }
    if (tecla == 'd')
    {
      if(usado!=2)
      {
        digitalWrite(vermelho, HIGH);
        digitalWrite(amarelo, HIGH);
        digitalWrite(verde, LOW);
        feed="Senha foi Desativada";
        Serial.println(feed);
        delay(4000);
        usado = 2;
        tecla = 'p';
      }
      else
      {
        feed="Ja ta desativado o bang";
        Serial.print(feed);
      }
      loop();
    }
  }
}
    
  
