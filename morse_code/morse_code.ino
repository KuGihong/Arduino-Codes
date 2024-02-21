#include <Arduino.h>
#include <ros.h>
#include <std_msgs/String.h>
#define UTIME 200

String morsecode[] =
{
  "-----", ".----", ".---", "...--", "....-", //0 ~ 4
  ".....", "-....", "--...", "---..", "----.",  //5 ~ 9
  "", "", "", "", "", "", "", //: ; < = > ? @
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",  //A ~ G
  "....", "..", ".---", "-.-", ".-..", "--", "-.",  //H ~ N
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",  //O ~ U
  "...-", ".--", "-..-", "-.--", "--..",  //V ~ Z
};

void morseCallback(const std_msgs::String& msg);

ros::NodeHandle nh;
ros::Subscriber<std_msgs::String> sub("morse_code", &morseCallback);

void morseCallback(const std_msgs::String& msg)
{
  String input = msg.data;
  Morse(input);
}

void Morse(String input)
{
  for (int i = 0; i < input.length(); i++)
  {
    if (input[i] == ' ')
    {
      delay(UTIME * 7);
      continue;
    }

    char c = input[i];
    if (c >= '0' && c <= '9')
    {
      String code = morsecode[c - '0'];

      for (int j = 0; j < code.length(); j++)
      {
        if (code[j] == '.')
        {
          digitalWrite(3, HIGH); // Start vibration
          delay(UTIME);
          digitalWrite(3, LOW);
        }
        else if (code[j] == '-')
        {
          digitalWrite(3, HIGH); // Start vibration
          delay(UTIME * 3);
          digitalWrite(3, LOW);
        }

        delay(UTIME); // Pause between dots and dashes
      }

     // Serial.println(code);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(3, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
}
