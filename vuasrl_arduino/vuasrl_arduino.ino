#include <Arduino.h>

#include <ros.h>
#include <std_msgs/Float64.h>

#include <Servo.h> 
#include <std_msgs/String.h>
#include <ackermann_msgs/AckermannDrive.h>
#include "math.h"

ros::NodeHandle nh;

std_msgs::Float64 right_distance;
std_msgs::Float64 left_distance;

ros::Publisher chatter_right("right_ultrasonic", &right_distance);
ros::Publisher chatter_left("left_ultrasonic", &left_distance);

const int trigger1 = 13;
const int echo1 = 12;
const int trigger2 = 10;
const int echo2 = 9;
long timeElapsed = 0;
long rightDist = 0;
long leftDist = 0;

float PWM = 100;
int servoPin = 8;  // Servo pinNum
int Motor_F = 5;  // DC Motor pin (Front)
int Motor_B = 4;  // DC Motor pin (Back)
int NEUTRAL_STEERING_ANGLE = 90;
int MIN_STEERING_ANGLE = 14;
int MAX_STEERING_ANGLE = 166;
float MIN_THROTTLE = 20;
float MAX_THROTTLE= 110;

Servo steeringServo;
void ackermannCallback(const ackermann_msgs::AckermannDrive & msg);

ros::Subscriber<ackermann_msgs::AckermannDrive> ackermannSubscriber("/ackermann/cmd_vel", & ackermannCallback);
ros::NodeHandle nodeHandle;

void ackermannCallback(const ackermann_msgs::AckermannDrive & msg)
{  
  int steering_angle = msg.steering_angle * (180 / M_PI) + 90;
  int vel = abs(510*msg.speed);

  if (steering_angle < MAX_STEERING_ANGLE)
    digitalWrite(Motor_F, HIGH);
    digitalWrite(Motor_B, LOW);
    analogWrite(5, vel);    

  if (steering_angle > MIN_STEERING_ANGLE and steering_angle > MAX_STEERING_ANGLE)
    digitalWrite(Motor_F, HIGH);
    digitalWrite(Motor_B, LOW);
    analogWrite(5, vel);

  if (steering_angle > MAX_STEERING_ANGLE)
    digitalWrite(Motor_F, HIGH);
    digitalWrite(Motor_B, LOW);
    analogWrite(5, vel);

  if (steering_angle < MIN_STEERING_ANGLE)
    digitalWrite(Motor_F, HIGH);
    digitalWrite(Motor_B, LOW);
    analogWrite(5, vel);

  if (steering_angle < MIN_STEERING_ANGLE)
    steering_angle = MIN_STEERING_ANGLE;

  if (steering_angle > MAX_STEERING_ANGLE)
    steering_angle = MAX_STEERING_ANGLE;
    
  steeringServo.write(steering_angle);
  Serial.print(steering_angle);
}

void setup() {
    pinMode(trigger1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trigger2, OUTPUT);
    pinMode(echo2, INPUT);
    Serial.begin(115200);
    nh.initNode();
    nh.advertise(chatter_right);
    nh.advertise(chatter_left);
    
    pinMode(Motor_F, OUTPUT);
    pinMode(Motor_B, OUTPUT);  
    steeringServo.attach(8);
    nh.subscribe(ackermannSubscriber);
  
  steeringServo.write(NEUTRAL_STEERING_ANGLE);
}

void ultrasonic(const int trigger, const int echo, long& distance) {
    // Clear trigger
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);

    // send 10 microseond trigger
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    // time to get echo
    timeElapsed = pulseIn(echo, HIGH);

    // convert time to distance
    // Divide by 1000000 (convert microseconds to seconds)
    // Divide by 2 for distance there and back
    // Multiply by speed of sound 34300cm/s
    distance = timeElapsed * 170 / 10000; // in cm
}

void loop() {
    ultrasonic(trigger1, echo1, rightDist); 
    
    right_distance.data = (double) rightDist; //위에서 계산한 거리값을 Distance 데이터에 저장
    chatter_right.publish(&right_distance); //chatter 발행자가 'chatter' 토픽으로 str_msg를 publish하도록 함
    nh.spinOnce(); //콜백함수 호출을 위한 함수, 메시지 수신 대기
    
    ultrasonic(trigger2, echo2, leftDist);
    
    left_distance.data = (double) leftDist; //위에서 계산한 거리값을 Distance 데이터에 저장
    chatter_left.publish(&left_distance); //chatter 발행자가 'chatter' 토픽으로 str_msg를 publish하도록 함
    //nh.spinOnce(); //콜백함수 호출을 위한 함수, 메시지 수신 대기
        
    if(!nh.connected()){
      steeringServo.write(NEUTRAL_STEERING_ANGLE);
      }  
    nh.spinOnce();
    delay(1000);
}
