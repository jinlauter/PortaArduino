int sensorPin = 8;


void setup() {
  
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  // put your setup code here, to run once:

}

void loop() {
  if(digitalRead(sensorPin) == 0)
  {
    Serial.println(digitalRead(sensorPin));
  }

  // put your main code here, to run repeatedly:

}
