//--########  Bibliotecas, setups e variáveis fixas   ########---

 // Sersor temperatura
#define DHTPIN A1
#define DHTTYPE DHT11
#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);
 // Sersor temperatura
 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <Servo.h>
Servo s; // Variável Servo
#define SERVO 6 // Porta Digital 6 PWM


// Variáveis usadas no medidos de temperatura
float h, t; //umidade e temperatura
char buff[4];
String string, stringt = "", stringh = "";
// Variáveis usadas no medidos de temperatura

int i         = 0;   //CONTADOR PADRÃO, NÃO MEXER
int qtd       = 0;   //CONTADOR PADRÃO, NÃO MEXER
int y; //Variável pra controlar CURSOR do display
char tecla; // Verifica tecla teclado
int usado = 2; //0=desativado,1=usado,2=desativado Verifica senha de 1 vez
unsigned long tempoaberto;
unsigned long hr = 0, m = 0, seg = 0;
String feed;
unsigned long a = 0, b = 0; // Variável pra ir usando por aí
int senhalocal;  //Utilizada para conferir se senha está correta.
unsigned long tempo, tempolim = 0, tempo_desabilitado = 0; // Contadores de tempo utilizados
unsigned long tempototal; //Tempo total de execução
unsigned long base = 0; // Variável utilizada em contadores ( base = millis() - tempototal )
unsigned long  valortotal = 0; // onde a senha é somada
int z         = 0;
int x         = 1; //Variavel p controlar se display ta ligadao, começa sempre ligado
//--########  Bibliotecas, setups,contadores e variáveis fixas   ########---



//--##Pinos leds e etc.... ##--
int verde     = 24;
int amarelo   = 44;
int vermelho  = 28;
int botao1    = 30;
int botao2    = 22;
int botao3    = 38;
int botao4    = 42;
int inicio    = 1;
int sensorPin = 8;
int luzfundo = 9; //CONTROLADOR DE LUZ DE FUNDO
//--##Pinos leds e etc.... ##--


//--------################ Controle da posição da fechadura ################-------
int aberto                    = 76;// Posição do servo para porta aberta
int fechado                   = 130; // Posição do servo para porta fechada
//--------################ Controle da posição da fechadura ################-------


//Variáveis controláveis:

unsigned long senha                     = 56651;  // Isso memo : 1-2-1-3-1-3-2-1    1=+7 | 2=^2  | 3= *2
unsigned long senhadesabilitar          = 200704;    //Senha de 8 digitos p/ desabilitar sistema 1-2-1-3-3-2-3-3
unsigned long senha_uma_vez             = 369485291;   //Senha que funciona só uma vez 1-2-3-2-1-3-2-1
unsigned long senha_dos_brother         = 7063;            // Senha dos brow : 1-1-1-3-2-3-3-1
 

int somatempobotao    = 700; // Ao entrar na senha, quanto tempo a mais soma antes de sair e voltar p/ o menu. Milisegundos

int tempo_abrir_entrar_fechar = 2; // Ao digitar senha correta ou abrir porta, quanto tempo deixar a porta aberta sem já tentar trancar. Segundos.
int tempo_abrir               = 2; // Mesma coisa da de cima, mas sem segundos

int segundospiscando = 10;// Tempo que o vermelho fica piscando quando erra alguma senha. Segundos

/* ------##### FUNÇÕES UTILIZÁVEIS ######-------
int verifica_se_porta_ta_fechada(Tempo que ela deve ficar fechada para fechar; Por quanto tempo fica dentro da função verificando) -> Retorna um int: 1 = Porta está fechada; 0 = Porta está aberta







*/
void setup()
{
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  pinMode(botao3, INPUT);
  pinMode(botao4, INPUT);
  pinMode(luzfundo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(sensorPin, INPUT);
  dht.begin();
  Serial.begin(9600);
  s.attach(SERVO);
  s.write(aberto);
  lcd.begin(16, 2);
  digitalWrite(luzfundo, HIGH);
}



void loop()
{
  int verificacao_interna =0;
  if (inicio == 1)
  {
    inicio = 0;
    boot();
  }
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(vermelho, LOW);
  if (digitalRead(sensorPin) == LOW)
  { 
    z = 0;
    portafechada();
  }
  while (digitalRead(sensorPin) == HIGH) //PORTA ABERTA
  {
    if(verificacao_interna=0)
    {
      s.write(aberto);//ABRIR PORTA
      verificacao_interna=1;
    }
    
    lcd.noBlink();
    lcd.clear();
    lcd.home();
    lcd.print("PORTA ABERTONA");
    lcd.setCursor(0, 1);
    lcd.print("FECHA SA PORRA");
    unsigned long tempo_fechada = 0;
      digitalWrite(verde, HIGH);
      digitalWrite(amarelo, HIGH);
      digitalWrite(vermelho, HIGH);
     if(verifica_se_porta_ta_fechada(150,500)==1)
     {
      verificacao_interna=1;
      portafechada();
     }
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, LOW);
     if(verifica_se_porta_ta_fechada(150,500)==1)
     {
      verificacao_interna=1;
      portafechada();
     }
   }
    verificacao_interna=1;
    loop();
}



void boot()
{
  s.write(aberto);//ABRIR PORTA
    if(digitalRead(sensorPin) == LOW)
  {
    s.write(fechado);
  }
  lcd.home();
  lcd.noBlink();
  lcd.print("Boquera SA.");
  lcd.setCursor(0, 1);
  lcd.print("Tenta nao");
  for (i = 0; i < 5; i++)
  {
    digitalWrite(vermelho, HIGH);
    delay(250);
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, HIGH);
    delay(250);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, HIGH);
    delay(250);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
    delay(250);
    digitalWrite(amarelo, LOW);
  }
  return;
}
void portafechada()
{
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);
  s.write(fechado);
  valortotal = 0;
  z=0;
  qtd = 0;
  while (1)
  {
    if (z == 0)
    {
      tempolim = (20000) + (millis());
      lcd.clear();
      lcd.home();
      lcd.noBlink();
      lcd.print("Porta trancada");
      lcd.setCursor(0, 1);
      lcd.print("E ae? Ql fita?");
      z = 1;
    }
   /* Trexo de tratamentos para os comandos do programa do PC 
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
      feed="Desabilitado";
      Serial.println(feed);
      tecla=='p';
      desabilitado();
    }
    if(tecla=='c')
    {
      feed="Abrindo ae";
       Serial.println(feed);
      tecla='p';
      abrir();
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
   Fim tratamentos programa PC */
  
    valortotal = 0;
    qtd = 0;
    digitalWrite(vermelho, HIGH);
    if (tempolim <= millis())
    {
      apagadisplay();
    }
    if (digitalRead(botao3) == HIGH)
    {
      y = 0;
      digitalWrite(verde, HIGH);
      delay(1000);
      digitalWrite(verde, LOW);
      menu();
    }
    if (digitalRead(botao4) == HIGH)
    {
      abrir();
    }
    if (digitalRead(botao1) == HIGH || digitalRead(botao2) == HIGH)
    {
      lcd.clear();
      lcd.home();
      lcd.print("Tenta ae fio:");
      tempolim = millis() + 4000;
      delay(200);
      digitalWrite(vermelho, LOW);
      digitalWrite(amarelo, HIGH);

      digitarsenha();
      if (senhalocal == 1)
      {
        lcd.print("Tudo irmaooo");
        lcd.setCursor(0, 1);
        lcd.print("Entra ae czao");
        digitalWrite(verde, HIGH); // acende o verde
        digitalWrite(amarelo, LOW);
        digitalWrite(vermelho, LOW);
        delay(100);
        s.write(aberto);
        z = 0;
        for (i = 0; i < tempo_abrir; i++)
        {
          lcd.setCursor(14, 1);
          lcd.print(i);
          delay(1000);
        }
        loop();
      }
      loop();
    }
  }
}

void apagadisplay()
{ x = 1;
  tempolim=millis()+20000;
  while (x == 1)
  {
    digitalWrite(luzfundo, LOW);
    if(tempolim<millis())
    {
      digitalWrite(vermelho,LOW);
    }
    if (digitalRead(botao1) == HIGH || digitalRead(botao2) == HIGH || digitalRead(botao3) == HIGH)
    {
      digitalWrite(vermelho,HIGH);
      z = 0;
      x = 0;
    }
    if (digitalRead(botao4) == HIGH)
    {
      digitalWrite(vermelho,HIGH);
      abrir();
    }
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
      feed="Desabilitado";
      Serial.println(feed);
      tecla=='p';
      desabilitado();
    }
    if(tecla=='c')
    {
      feed="Abrindo ae";
       Serial.println(feed);
      tecla='p';
      abrir();
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
  delay(200);
  digitalWrite(luzfundo, HIGH);
  loop();
}

void menu()
{

  tempolim = (7000 + millis());
  int i = 0;
  int opcao = 1;
  int q = 0;
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 1);
  lcd.print("Ant  Prox Selec");
  while (i == 0)
  {
    lcd.setCursor(0, 0);
    if (opcao == 1)
    {
      lcd.print("1 - Temperatura ");
    }
    else if (opcao == 2)
    {
      lcd.print("2 - Desabilitar ");
    }
    else if (opcao == 3)lcd.print("3-Senha de 1 Vez");
    else if (opcao == 4)lcd.print("4 - Tempo Total ");
    else if (opcao == 5)lcd.print("5 - As faiada   ");
    else if (opcao == 6)lcd.print("6 - HOMEEE      ");

    delay(400);
    while (q == 0)
    {

      if (tempolim <= millis())
      {
        loop();
      }
      if (digitalRead(botao2) == HIGH)
      {
        q = 1;
        tempolim += 3000;
        if (opcao != 6)
        {
          opcao += 1;
        }
        else
        {
          opcao -= 5;
        }
      }
      if (digitalRead(botao1) == HIGH)
      {
        q = 1;
        tempolim += 3000;
        if (opcao != 1)
        {
          opcao -= 1;
        }
        else
        {
          opcao += 5;
        }
      }
      if (digitalRead(botao3) == HIGH)
      {
        if (opcao == 1)
        {
          temperatura();
        }
        else if (opcao == 2)
        {
          desabilitar();
        }
        else if (opcao == 3)
        {
          vertempoportaaberta();
        }
        else if (opcao == 4)
        {
          vertempototal();
        }
        else if (opcao == 5)
        {
          portaabrirsemsenha();
        }
        else if (opcao == 6)
        {
          delay(400);
          loop();
        }
      }
    }
    q = 0;
  }
  loop();
}


void temperatura()
{
  lcd.clear();
  delay(500);
  tempolim = 10000 + millis();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print("Temp.:");
  lcd.setCursor(0, 1);
  lcd.print("Umidade:");
  while (1)
  {
    if (tempolim <= millis())
    {
      loop();
    }
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    lcd.setCursor(6, 0);
    lcd.println(t);
    lcd.setCursor(11,0);
    lcd.print(" C ");
    lcd.setCursor(9, 1);
    lcd.print(h);
    lcd.setCursor(14,1);
    lcd.print("% ");
    if (digitalRead(botao1) == HIGH)
    {
      delay(250);
      break;
    }
  }
  loop();
}
void desabilitar()
{
  delay(500);
  tempolim = 7000 + millis();
  lcd.clear();
  lcd.home();
  lcd.print("Desab. sistema?");
  lcd.setCursor(0, 1);
  lcd.print("Sim         Nao");

  while (1)
  {
    if (tempolim <= millis())
    {
      loop();
    }
    if (digitalRead(botao1) == HIGH)
    {
      delay(500);
      break;
    }
    if (digitalRead(botao3) == HIGH)
    {
      delay(300);
      menu();
    }
  }
  delay(500);
  tempolim = 7000 + millis();
  tempo_desabilitado = 1;
  lcd.clear();
  lcd.home();
  lcd.print("Desab. por: ");
  lcd.setCursor(13, 0);
  lcd.print(tempo_desabilitado);
  lcd.setCursor(15, 0);
  lcd.print("h");
  lcd.setCursor(0, 1);
  lcd.print("+     conf     -");
  while (1)
  {
    if (tempolim <= millis())
    {
      loop();
    }
    if (digitalRead(botao1) == HIGH)
    {
      delay(500);
      tempolim+=1000;
      tempo_desabilitado += 1;
      lcd.setCursor(13, 0);
      lcd.print(tempo_desabilitado);
    }
    if (digitalRead(botao3) == HIGH && tempo_desabilitado >= 2)
    {
      tempolim+=1000;
      delay(300);
      tempo_desabilitado -= 1;
      lcd.setCursor(13, 0);
      lcd.print(tempo_desabilitado);
    }
    if (digitalRead(botao2) == HIGH)
    {
      break;
    }
  }
  while (1)
  {
    y = 0;
    lcd.clear();
    lcd.home();
    lcd.print("senha adm.:");
    lcd.setCursor(y, 1);
    lcd.blink();
    tempolim = millis() + 10000;
    delay(200);
    valortotal = 0;
    qtd = 0;
    while (1)
    {
      tempo = millis();
      if (tempo > tempolim)
      {
        digitalWrite(amarelo, LOW);
        z = 0;
        lcd.noBlink();
        break;
      }
      if (digitalRead(botao1) == HIGH)
      {
        lcd.setCursor(y, 1);
        lcd.print("*");
        y += 1;
        delay(350);
        valortotal += 7;
        qtd = qtd + 1;
        tempolim += somatempobotao;
      }
      if (digitalRead(botao2) == HIGH)
      {
        lcd.setCursor(y, 1);
        lcd.print("*");
        y += 1;
        delay(350);
        valortotal = valortotal * valortotal;
        qtd = qtd + 1;
        tempolim += somatempobotao;
      }
      if (digitalRead(botao3) == HIGH)
      {
        lcd.setCursor(y, 1);
        lcd.print("*");
        y += 1;
        delay(350);
        valortotal = valortotal * 2;
        qtd = qtd + 1;
        tempolim += somatempobotao;
      }
      if (valortotal == senhadesabilitar)
      {
        desabilitado();
      }
      if (qtd >= 8 && valortotal != senhadesabilitar)
      {
        lcd.noBlink();
        digitalWrite(amarelo, LOW);
        lcd.clear();
        lcd.home();
        lcd.print("ERRADO SA FITA");
        for (i = 0; i < 4; i++)
        {
          digitalWrite(vermelho, HIGH);
          delay(500);
          digitalWrite(vermelho, LOW);
          delay(500);
        }
        lcd.clear();
        z = 0;
        loop();
      }
    }
  }

}
void desabilitado()
{
   lcd.noBlink();
   digitalWrite(verde, HIGH);
   digitalWrite(amarelo, LOW);
   digitalWrite(vermelho, LOW);
   delay(100);
   s.write(aberto);
   tempo = millis()/1000;
  z=0;
  lcd.clear();
  lcd.home();
  lcd.print("Desabilitado");
  tempolim = 7000 + millis();;
  if(tempo_desabilitado == 0)
  {
    tempo_desabilitado=24;
  }
  tempo_desabilitado = tempo_desabilitado * 3600;
  while (z <= tempo_desabilitado)
  {
    if(Serial.available())
    {
      tecla=Serial.read();
      if(tecla=='b')
      {
        feed="Sistema ta desativado ja fei";
       Serial.println(feed);
        tecla='p';
      }
      if(tecla=='f')
      {
        feed="Sistema Reativo, cola mais concorrencia";
        Serial.println(feed);
        digitalWrite(luzfundo,HIGH);
        tecla='p';
        delay(500);
        loop();
      }
    }
    if (tempolim < millis())
    {
      digitalWrite(luzfundo, LOW);
      digitalWrite(verde,LOW);
    }
    z = (millis() / 1000) - tempo;
    if (digitalRead(botao1) == HIGH)
    {
      delay(500);
      digitalWrite(luzfundo, HIGH);
      tempolim = 7000 + millis();;
      lcd.clear();
      lcd.home();
      lcd.print("Reabilitar??");
      lcd.setCursor(0, 1);
      lcd.print("Sim         Nao");
      while (1)
      {
        if (digitalRead(botao1) == HIGH)
        {
          delay(500);
          loop();
        }
        if (digitalRead(botao3) == HIGH)
        {
          delay(500);
          lcd.clear();
          lcd.home();
          lcd.print("Desabilitado");
          tempolim = 7000 + millis();;
          break;
        }
        if (tempolim < millis())
        {
          lcd.clear();
          lcd.home();
          lcd.print("Desabilitado");
          tempolim = 7000 + millis();;
          break;
        }
      }
    }
  }
  tempo_desabilitado=0;
  digitalWrite(luzfundo, HIGH);
  digitalWrite(verde,HIGH);
  loop();
}
void abrirumavez()
{


  lcd.noBlink();
  lcd.clear();
  lcd.home();
  lcd.print("Atencao caraio!");
  lcd.setCursor(0, 1);
  lcd.print("Leia q ja abre");
  delay(4000);
  lcd.clear();
  lcd.home();
  lcd.print("Entra e sai");
  lcd.setCursor(0, 1);
  lcd.print("E rapido, pq");
  delay(4000);
  lcd.clear();
  lcd.home();
  lcd.print("Vai ta contando");
  lcd.setCursor(0, 1);
  lcd.print("Qto tempo q fico");
  delay(4000);
  lcd.clear();
  lcd.home();
  lcd.print("Dentro do meu");
  lcd.setCursor(0, 1);
  lcd.print("quarto");
  delay(4000);
  digitalWrite(amarelo, LOW);
  digitalWrite(vermelho, LOW);
  s.write(aberto);
  digitalWrite(verde, HIGH);
  while (1)
  {
    if (digitalRead(sensorPin) == HIGH)
      break;
  }
  lcd.clear();
  lcd.home();
  lcd.print("fico no quarto:");
  base = millis();
  while (digitalRead(sensorPin) == HIGH)
  {
    exibirhoras(millis() - base);
  }
  tempoaberto = millis() - base;
  s.write(fechado);
  lcd.clear();
  lcd.home();
  lcd.print("Ficou:");
  lcd.setCursor(0, 1);
  exibirhoras(tempoaberto);

  delay(5000);
  loop();
}
void vertempoportaaberta()
{
  tempolim = 7000 + millis();
  lcd.clear();
  lcd.home();
  if (usado == 1)
  {
    lcd.print("Senha usada bixo");
    lcd.setCursor(0, 1);
    lcd.print("Por:");
    lcd.setCursor(5, 1);
    exibirhoras(tempoaberto);
    lcd.setCursor(15, 1);
    lcd.print(">>");
    tempolim = millis();
    while (1)
    {
      if (tempolim + 15000 <= millis())
      {
        loop();
      }
      if (digitalRead(botao3) == HIGH)
      {
        break;

      }
    }
    reabilitarsenha();
  }
  else if (usado == 0)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Ngm uso senha pa");
    delay(4000);
    menu();
  }
  else
  {
    lcd.clear();
    lcd.home();
    lcd.print("Senha ta");
    lcd.setCursor(0, 1);
    lcd.print("Desabilitada");
    delay(3000);
    reabilitarsenha();
  }
}

void abrir()
{
  digitalWrite(luzfundo, HIGH);
  digitalWrite(vermelho, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(verde, HIGH);
  lcd.clear();
  lcd.home();
  lcd.print("Abrino");
  lcd.setCursor(14, 1);
  s.write(aberto);
  for (i = 0; i <= tempo_abrir_entrar_fechar; i++)
  {
    lcd.setCursor(14, 1);
    lcd.print(i);
    delay(1000);
  }
  loop();
}
unsigned long exibirhoras(unsigned long tempo)
{
  int dia;
  seg = (tempo / 1000);
  hr = (seg / 3600);
  m = (seg / 60);
  dia = (seg/86400000);
  if (seg >= 60)
  {
    seg = seg%60;
    lcd.setCursor(7, 1);
    lcd.print(" ");
  }
  lcd.setCursor(0, 1);
  if(hr>24)
  {
    hr=0;
  }

if(dia<9)
{
  lcd.print("0"); lcd.setCursor(1, 1); lcd.print(dia); lcd.setCursor(2, 1); lcd.print("d ");
}
else
{
  lcd.print("0"); lcd.setCursor(4, 1); lcd.print(dia); lcd.setCursor(5, 1); lcd.print(":");
}

  
  lcd.setCursor(5, 1);
  if(hr < 24)
  {
    lcd.print("0"); lcd.setCursor(6, 1); lcd.print(hr); lcd.setCursor(7, 1); lcd.print(":");
  }
  else
  {
    lcd.print(hr);lcd.setCursor(7, 1); lcd.print(":");
  }
  
  if (m > 9)
  {
    lcd.setCursor(8, 1); lcd.print(m); lcd.setCursor(10, 1); lcd.print(":");
    if (seg <= 9)
    {
      lcd.setCursor(11, 1); lcd.print("0"); lcd.setCursor(12, 1); lcd.print(seg);
    }
    else
    {
      lcd.setCursor(11, 1); lcd.print(seg);
    }
  }
  else
  {
    lcd.setCursor(8, 1); lcd.print("0"); lcd.setCursor(9, 1); lcd.print(m); lcd.setCursor(10, 1); lcd.print(":");
    if (seg <= 9)
    {
      lcd.setCursor(11, 1); lcd.print("0"); lcd.setCursor(12, 1); lcd.print(seg);
    }
    else
    {
      lcd.setCursor(11, 1); lcd.print(seg);
    }
  }
  delay(1000);

}
void digitarsenha()
{
  qtd = 0;
  y = 0;
  valortotal = 0;
  lcd.setCursor(y, 1);
  lcd.blink();
  int ultimo_botao_apertado = 5;
  while (1)
  {
    if (millis() > tempolim)
    {
      digitalWrite(amarelo, LOW);
      z = 0;
      lcd.noBlink();
      loop();
    }
    if (digitalRead(botao1) == HIGH && ultimo_botao_apertado != 1)
    {
      lcd.setCursor(y, 1);
      lcd.print("*");
      y += 1;
      ultimo_botao_apertado = 1;
      valortotal += 7;
      qtd = qtd + 1;
      tempolim += somatempobotao;
    }
    if (digitalRead(botao2) == HIGH && ultimo_botao_apertado != 2)
    {
      lcd.setCursor(y, 1);
      lcd.print("*");
      y += 1;
      ultimo_botao_apertado = 2;
      valortotal = valortotal * valortotal;
      qtd = qtd + 1;
      tempolim += somatempobotao;
    }
    if (digitalRead(botao3) == HIGH && ultimo_botao_apertado != 3)
    {
      lcd.setCursor(y, 1);
      lcd.print("*");
      y += 1;
      ultimo_botao_apertado = 3;
      valortotal = valortotal * 2;
      qtd = qtd + 1;
      tempolim += somatempobotao;
    }
    if (digitalRead(botao4) == HIGH)
    {
      lcd.clear();
      lcd.home();
      lcd.print("To saino");
      lcd.setCursor(0, 1);
      lcd.print("tenta n ladrao");
      delay(150);
      digitalWrite(verde, HIGH); // acende o verde
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, LOW);
      delay(100);
      s.write(aberto);
      delay(tempo_abrir_entrar_fechar); //Delay suficiente para abrir a porta, entrar e fechar porta
      loop();
    }
    if (valortotal == senha)
    {

      lcd.noBlink();
      lcd.clear();
      lcd.home();
      senhalocal = 1;
      return;
    }
    if (valortotal == senha_uma_vez)
    {
      if (usado == 0)
      {
        usado = 1;
        abrirumavez();
      }
      else if (usado == 2)
      {
        lcd.noBlink();
        digitalWrite(amarelo, LOW);
        lcd.clear();
        lcd.home();
        lcd.print("senha ta");
        lcd.setCursor(0, 1);
        lcd.print("desabilitada");
        delay(4000);
        lcd.clear();
        z = 0;
        loop();
      }
      else
      {
        lcd.noBlink();
        digitalWrite(amarelo, LOW);
        lcd.clear();
        lcd.home();
        lcd.print("senha ja usada");
        lcd.setCursor(0, 1);
        lcd.print("so lamento fei");
        for (i = 0; i < segundospiscando; i++)
        {
          digitalWrite(vermelho, HIGH);
          delay(500);
          digitalWrite(vermelho, LOW);
          delay(500);
        }
        lcd.clear();
        z = 0;
        loop();
      }
    }
    if (qtd >= 8 && valortotal != senha && valortotal != senha_uma_vez)
    {

      lcd.noBlink();
      digitalWrite(amarelo, LOW);
      lcd.clear();
      lcd.home();
      //lcd.print("ta errado esse");
      lcd.print(valortotal);
      lcd.setCursor(0, 1);
      lcd.print("Aqui n");
      for (i = 0; i < segundospiscando; i++)
      {
        digitalWrite(vermelho, HIGH);
        delay(500);
        digitalWrite(vermelho, LOW);
        delay(500);
      }
      lcd.clear();
      z = 0;
      loop();
    }
  }
}
void reabilitarsenha()
{
  lcd.clear();
  lcd.home();
  lcd.print("Reabilit. senha?");
  lcd.setCursor(0, 1);
  lcd.print("Ahm");
  lcd.setCursor(6, 1);
  lcd.print("To d boa");
  tempolim = millis();
  while (1)
  {
    if (tempolim + 10000 <= millis())
    {
      loop();
    }
    if (digitalRead(botao1) == HIGH)
    {
      y = 0;
      lcd.clear();
      lcd.home();
      lcd.print("senha adm.:");
      lcd.setCursor(y, 1);
      lcd.blink();
      tempolim = millis() + 10000;
      delay(200);
      valortotal = 0;
      qtd = 0;
      while (1)
      {
        tempo = millis();
        if (tempo > tempolim)
        {
          digitalWrite(amarelo, LOW);
          z = 0;
          lcd.noBlink();
          break;
        }
        if (digitalRead(botao1) == HIGH)
        {
          lcd.setCursor(y, 1);
          lcd.print("*");
          y += 1;
          delay(350);
          valortotal += 7;
          qtd = qtd + 1;
          tempolim += somatempobotao;
        }
        if (digitalRead(botao2) == HIGH)
        {
          lcd.setCursor(y, 1);
          lcd.print("*");
          y += 1;
          delay(350);
          valortotal = valortotal * valortotal;
          qtd = qtd + 1;
          tempolim += somatempobotao;
        }
        if (digitalRead(botao3) == HIGH)
        {
          lcd.setCursor(y, 1);
          lcd.print("*");
          y += 1;
          delay(350);
          valortotal = valortotal * 2;
          qtd = qtd + 1;
          tempolim += somatempobotao;
        }
        if (valortotal == senhadesabilitar)
        {
          lcd.noBlink();
          lcd.clear();
          lcd.home();
          lcd.print("Reabilitada");
          digitalWrite(verde, HIGH); // acende o verde
          digitalWrite(amarelo, LOW);
          digitalWrite(vermelho, LOW);
          delay(4000);
          z = 0;
          usado = 0;
          loop();
        }
        if (qtd >= 8 && valortotal != senhadesabilitar)
        {
          lcd.noBlink();
          digitalWrite(amarelo, LOW);
          lcd.clear();
          lcd.home();
          lcd.print("ERRADO SA FITA");
          for (i = 0; i < 4; i++)
          {
            digitalWrite(vermelho, HIGH);
            delay(500);
            digitalWrite(vermelho, LOW);
            delay(500);
          }
          lcd.clear();
          z = 0;
          loop();
        }
      }
    }
    if (digitalRead(botao3) == HIGH)
    {
      delay(300);
      loop();
    }

  }
}
void vertempototal()
{
  lcd.clear();
  lcd.home();
  lcd.print("Ligado faz");
  base = 0;
  for (i = 0; i < 5; i++)
  {
    exibirhoras(millis());
  }
  loop();
}
void portaabrirsemsenha()
{
  lcd.clear();
  lcd.home();
  lcd.print("Fazendo esse");
  lcd.setCursor(0, 1);
  lcd.print("ainda");
  delay(3000);
  loop();
}


int verifica_se_porta_ta_fechada(long tempofechada,long porqtotempoverificams)
{
  tempolim = porqtotempoverificams+millis();
  unsigned long tempo_total = 0;
  int conclusao = 0; // 1 = fechada 0= aberta
  while(tempolim>millis())
  {
    if(digitalRead(sensorPin) == LOW)
    {
      conclusao=1;
      unsigned long tempo_inicio = millis();
      while((millis()-tempo_inicio)<tempofechada)
      {
        if(digitalRead(sensorPin)== HIGH)
        {
          conclusao=0;
        }
      }
      if(conclusao==1)
      {
        portafechada();
      }
    }
  }
  return conclusao;
}
