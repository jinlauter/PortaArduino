#include <Servo.h>
 
#define SERVO 7 // Porta Digital 6 PWM
 
Servo s; // Variável Servo
int pos = 0; // Posição Servo
int on_off_servo = 50;

 
void setup ()
{
  pinMode(on_off_servo, OUTPUT);
  digitalWrite(on_off_servo, HIGH);
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(pos); // Inicia motor posição zero
  Serial.println("0");
  //digitalWrite(on_off_servo, LOW);
  
}
 
void loop()
{
  delay(500);
  digitalWrite(on_off_servo, HIGH);
  //fechar
  s.write(130);
  Serial.println("130");
  //digitalWrite(on_off_servo, LOW);
  delay(1000);
  digitalWrite(on_off_servo, HIGH);
  //abrir
  s.write(30);
  Serial.println("30");
  //digitalWrite(on_off_servo, LOW);
  delay(3000);
  
}
