#include <Wire.h>

void setup() {
  Wire.begin();
}

void loop() {
  // DANGER 진동 발생
  Wire.beginTransmission(4); // 슬레이브 주소 4로 전송 시작
  Wire.write("DANGER"); // "DANGER"라는 문자열 전송
  Wire.endTransmission(); // 전송 종료  
  delay(2000); // 10초 대기

  // 진동 중단 전송
  Wire.beginTransmission(4); // 슬레이브 주소 4로 전송 시작
  Wire.write("\n"); // 개행문자 전송
  Wire.endTransmission(); // 전송 종료
  delay(2000); // 10초 대기
}
