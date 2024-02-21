const int trigger = 6;
const int echo = 5;

long timeElapsed = 0;
float distance = 0;

void setup() {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(115200);
}

void loop() {
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
    distance = (float)timeElapsed / 1000000 / 2 * 34300; // in cm

    writeFloat(distance);
    
    delay(500);
}

void writeFloat(float data){
  byte buf[4];
  union {
    float a;
    unsigned char bytes[4];
  } thing;
  thing.a = data;
  memcpy(buf, thing.bytes, 4);
  Serial.write(buf, sizeof(buf));
}
