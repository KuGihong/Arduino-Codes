#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <ros.h>
#include <heart_rate_msg/heart_rate.h>

MAX30105 particleSensor;

const byte RATE_SIZE = 3;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
float beatAvg;

ros::NodeHandle nh;
heart_rate_msg::heart_rate heartRateMsg;
ros::Publisher heartRatePub("heart_rate_topic", &heartRateMsg);

void setup()
{
  Serial.begin(57600);
  Serial.println("Initializing...");
  Wire.begin();

  // Initialize sensor
  if (!particleSensor.begin(Wire1, I2C_SPEED_FAST))
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x1F);
  particleSensor.setPulseAmplitudeGreen(0);

  // Setup heartbeat message field names
  heartRateMsg.beat_avg = 0.0;
  heartRateMsg.ir_value = 0.0;
  heartRateMsg.beat_status = "";
  nh.initNode();
  nh.advertise(heartRatePub);
}

void loop()
{
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
      heartRateMsg.beat_avg = beatAvg;
    }
  }

  // Update beat_status based on beatAvg
  if (beatAvg >= 40 && beatAvg <= 60) {
    heartRateMsg.beat_status = "WARNING";
    Wire.beginTransmission(4);
    Wire.write("WARNING");
    Wire.endTransmission();
  } else if (beatAvg >= 60 && beatAvg <= 100) {
    heartRateMsg.beat_status = "NORMAL";
    Wire.beginTransmission(4);
    Wire.write("\n");
    Wire.endTransmission();
  } else {
    heartRateMsg.beat_status = "DANGER";
    Wire.beginTransmission(4);
    Wire.write("DANGER");
    Wire.endTransmission();
  }

  // Handle case when finger is not detected
  if (irValue < 50000){
    heartRateMsg.beat_status = "NoFinger";
    Wire.beginTransmission(4);
    Wire.write("\n");
    Wire.endTransmission();
  }

  // Publish the heart rate message
  heartRateMsg.header.stamp = nh.now();
  heartRateMsg.ir_value = (float)irValue;
  heartRatePub.publish(&heartRateMsg);

  nh.spinOnce();
}
