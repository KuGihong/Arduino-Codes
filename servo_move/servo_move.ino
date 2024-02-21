#include <Arduino.h>
#include <Servo.h>

Servo sv1;
Servo sv2;

const unsigned long interval = 2000; // 2초 (단위: 밀리초)
unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(9600);
  sv1.attach(7);
  sv2.attach(6);  
  sv1.write(115);
  sv2.write(42);
}

void loop()
{
}
