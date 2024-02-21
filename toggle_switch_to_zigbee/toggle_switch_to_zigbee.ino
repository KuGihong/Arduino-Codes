#include <Arduino.h>

int dirState = 0;           // DirectionState  DC모터의 정/역 회전방향

void setup()
{
  pinMode(8, INPUT_PULLUP); // Direction(토글 스위치와 D8핀 연결)_내부 풀업 저항 사용
  Serial.begin(9600);
}

void loop()
{
  dirState = digitalRead(8);
  if (dirState == HIGH){
    Serial.println(dirState);
  }
}
