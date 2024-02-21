#include <Servo.h>

#define ON  1
#define OFF 0

Servo sv;

void setup()
{
    sv.attach(7);    //servo motor
    //pinMode(A0, INPUT); //light sensor
        
    Serial.begin(9600);
}

void loop()
{
    //int light = analogRead(A0);
    int msg = Serial.read();
    
    if (msg == ON)
    {
        sv.write(90);
        delay(2000);
    }
    else if(msg == OFF)
    {
        sv.write(0);
        delay(2000);
    }
    else
      sv.write(0);
}
