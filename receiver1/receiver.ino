#include <Servo.h>

#define VALUE   5
#define ON  1
#define OFF 2

Servo sv1;
Servo sv2;

void setup()
{
    sv.attach(7);    //servo motor
    sv.attach(6);    //servo motor
    pinMode(A0, INPUT); //light sensor
       
    Serial.begin(9600);
}

void ServoMove(int angle)
{
    sv1.write(angle);
    sv2.write(angle);
}

void loop()
{
    int light = analogRead(A0);
    int sign = Serial.read();
   
    Serial.println(light, sign);

    if ((sign == ON) | (light > VALUE))
    {
        ServoMove(90);
    }
    else if(sign == OFF)
    {
        ServoMove(0);
    }
    else
      ServoMove(0);
}
