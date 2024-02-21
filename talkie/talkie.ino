
#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"

Talkie voice;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200); 
    unsigned long startTime = millis();
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    while (millis() - startTime < 4000);
#endif
    // Just to know which program is running on my Arduino
    voice.say(sp4_READY);
}

void loop() {
  // put your main code here, to run repeatedly:
    voice.say(spPAUSE2);
    voice.say(sp2_DANGER);
    voice.say(spPAUSE2);
    voice.say(sp4_WARNING);
    voice.say(sp4_WARNING);

}
