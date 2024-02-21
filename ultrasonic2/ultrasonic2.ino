const int trigger = 6;
const int echo = 7;

long timeElapsed = 0;
long distance = 0;

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
    distance = timeElapsed * 170 / 10000; // in cm

    Serial.print(distance);
    Serial.println("cm");

    delay(500);
}
