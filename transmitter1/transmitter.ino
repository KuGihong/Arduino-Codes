#define ON 1
#define OFF 2

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
int SwitchPin = 5;

void setup()
{
    pinMode(SwitchPin, INPUT);
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("Push the button:");
    lcd.setCursor(0, 2);
    lcd.print("Drop a grenade");
}

void loop()
{
    if(digitalRead(SwitchPin) == HIGH)  //If switch on, Serial message will send "ON"
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Drop the grenade");
        lcd.setCursor(4, 1);
        lcd.print("Complete");
        Serial.write(ON);
    }
    else
    {
        Serial.write(OFF);
    }
}