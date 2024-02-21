#define UTIME 200

#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"
Talkie voice;

String morsecode[]=
{
  "-----", ".----", ".---", "...--", "....-", //0 ~ 4
  ".....", "-....", "--...", "---..", "----.",  //5 ~ 9
  "", "", "", "", "", "", "", //: ; < = > ? @
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",  //A ~ G
  "....", "..", ".---", "-.-", ".-..", "--", "-.",  //H ~ N
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",  //O ~ U
  "...-", ".--", "-..-", "-.--", "--..",  //V ~ Z
};

void setup() 
{
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  unsigned long startTime = millis();
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
  while (millis() - startTime < 4000);
#endif
  // Just to know which program is running on my Arduino
  voice.say(sp4_READY);  
}

void loop() 
{
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    Morse(data);
  }
}

void Morse(String input)
{
  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == ' ')
    {
      delay(UTIME*7);   
      continue;
    }
    
    String code = morsecode[input[i]-'0'];
    int vibration = 0;
    
    for(int j = 0; j< code.length(); j++)
    {
      
      if(code[j] == '.')
      {
        vibration = UTIME;
      }
      else if(code[j] == '-')
      {
        vibration = UTIME * 3;
      }
        voice.say(sp2_DANGER);
        digitalWrite(11, HIGH); //start vibration
        delay(vibration);
        voice.say(sp2_DANGER);
        digitalWrite(11, LOW);
        voice.say(sp2_DANGER);
        delay(UTIME);
    }
    Serial.println(code);
  }
    
}
