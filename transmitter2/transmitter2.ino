#include <LiquidCrystal_I2C.h>
#define ON  1
#define OFF 0
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to the I2C address of your LCD module

int SwitchPin = 5;

void setup()
{
    pinMode(SwitchPin, INPUT);
    Serial.begin(9600);
    lcd.init(); // initialize the lcd
    lcd.backlight(); // turn on backlight
    lcd.print("Push the button:");
    lcd.setCursor(0, 1);
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
