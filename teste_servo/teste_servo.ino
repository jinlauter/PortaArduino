#include <Servo.h>
 
#define SERVO 6 // Porta Digital 6 PWM
 
Servo s; // Variável Servo
int pos; // Posição Servo
int onoff = 25;

 
void setup ()
{
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
  Serial.println("0");
  pinMode(onoff, OUTPUT);
  digitalWrite(onoff, HIGH);
}
 
void loop()
{
  //fechar
  s.write(130);
  Serial.println("130");
  delay(3000);
  //abrir
  s.write(77);
  Serial.println("77");
  delay(3000);
  
}
