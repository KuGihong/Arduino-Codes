#include <ros.h> //아두이노에서 ros를 사용할 수 있게 해주는 헤더파일
#include <std_msgs/Float64.h> //메시지를 위한 헤더파일

ros::NodeHandle nh; //publisher, subscriber 사용 및 노드 시리얼 통신 위해 노드핸들 필요
std_msgs::Float64 Distance; //Distance라는 이름의 메시지를 Float64 형태로 설정
ros::Publisher chatter("ultrasonic",&Distance); //토픽 이름 chatter로 설정, 메시지 인스턴스에 대한 참조를 포함하는 발행자 객체 만듦

const int trigPin = 6;
const int echoPin = 7;

long duration;
float distance;

void setup() 
{
  nh.initNode(); //노드 핸들 초기화
  nh.advertise(chatter); //chatter토픽 publish
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(115200); 
}

void loop() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // convert time to distance
  // Divide by 1000000 (convert microseconds to seconds)
  // Divide by 2 for distance there and back
  // Multiply by speed of sound 34300cm/s
  distance = (float)duration / 1000000 / 2 * 34300; // in cm
  
  Distance.data=distance; //위에서 계산한 거리값을 Distance 데이터에 저장
  chatter.publish(&Distance); //chatter 발행자가 'chatter' 토픽으로 str_msg를 publish하도록 함
  nh.spinOnce(); //콜백함수 호출을 위한 함수, 메시지 수신 대기
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  delay(500);
}
