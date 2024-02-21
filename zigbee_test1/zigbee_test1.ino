#include <Arduino.h>

const unsigned long interval = 2000; // 2초 (단위: 밀리초)
unsigned long previousMillis = 0;

void setup()
{  
    Serial1.begin(9600);
}

void loop()
{
  char sendData[20]; // 최대 문자열 길이를 설정해야 함
  String A = "Hello";
  float B = 3.17;

  unsigned long currentMillis = millis(); // 현재 시간 추적

  // 일정 시간(interval)마다 데이터 전송
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // 이전 시간 업데이트

    sprintf(sendData, "%s, %.2f", A.c_str(), B); // 문자열 합침
    Serial1.print(sendData); // Serial1.write() 대신 Serial1.print() 사용
  }

  // 이후에 다른 작업 처리 가능
  // ...

}
