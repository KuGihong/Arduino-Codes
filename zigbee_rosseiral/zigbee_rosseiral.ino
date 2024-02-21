#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>

const int BUFFER_SIZE = 50;
char buffer[BUFFER_SIZE];
int bufferIndex = 0;
boolean newData = false;
float beatAvg;
String beatStatus;

ros::NodeHandle nh;
std_msgs::Float32 beatAvgMsg;
std_msgs::String beatStatusMsg;
ros::Publisher pubBeatAvg("heart_rate/beat_avg", &beatAvgMsg);
ros::Publisher pubBeatStatus("heart_rate/beat_status", &beatStatusMsg);

void setup() {
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(pubBeatAvg);
  nh.advertise(pubBeatStatus);
}

void loop() {
  // Zigbee 모듈로부터 데이터 수신 및 처리
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
      buffer[bufferIndex] = '\0'; // 문자열 종료를 위한 널 문자 추가
      parseData(buffer); // 수신한 데이터를 처리하는 함수 호출
      bufferIndex = 0; // 버퍼 초기화
      newData = true;
    } else {
      if (bufferIndex < BUFFER_SIZE - 1)
        buffer[bufferIndex++] = receivedChar;
    }
  }

  // 수신한 데이터 활용
  if (newData) {
    // 데이터 처리를 원하는 방식으로 수행합니다.
    // 예를 들어, 데이터를 파싱하여 심박수 값과 상태를 저장합니다.

    // ROS 메시지에 데이터 채우기
    beatAvgMsg.data = beatAvg;
    beatStatusMsg.data = beatStatus.c_str();

    // ROS로 데이터 publish
    pubBeatAvg.publish(&beatAvgMsg);
    pubBeatStatus.publish(&beatStatusMsg);

    nh.spinOnce(); // ROS 노드를 실행하여 데이터를 publish합니다.

    newData = false; // newData 플래그 초기화
  }

  // 추가적인 작업 또는 딜레이 코드를 여기에 추가할 수 있습니다.
}

void parseData(const char* data) {
  // 이 함수를 통해 데이터를 파싱하는 작업을 수행할 수 있습니다.
  // 데이터는 data 매개변수로 전달됩니다.
  // 이 함수를 원하는 방식으로 수정하여 데이터를 처리하시기 바랍니다.

  // 데이터를 저장하는 방법에 따라 아래와 같이 변수에 값을 할당할 수 있습니다.
  char *ptr;
  beatAvg = strtod(data, &ptr);
  beatStatus = ptr;
}
