const int IN1 = 10, IN2 = 11;
const int SPEED_INCREASE_PIN = 2; // Pin for the speed increase switch
const int SPEED_DECREASE_PIN = 3; // Pin for the speed decrease switch

unsigned int Pluse_A = 0, interval = 500;
unsigned long previousMillis = 0;
long Sp_avg = 0, Sp_result = 0;
int Print_CNT = 0, Sp_CNT = 0, CMD = 0;
float Err, PID_Out, PID_val, m = 0;
float err_P = 0, err_I = 0, err_D = 0, err_B;
float Pv = 0.0003, Iv = 0.00005, Dv = 0.0009;
float Speed = 0, St_Speed = 8000;
int Speed_CMD = 0;
volatile bool speedIncreaseFlag = false;
volatile bool speedDecreaseFlag = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(SPEED_INCREASE_PIN, INPUT); // Set speed increase pin as input
  pinMode(SPEED_DECREASE_PIN, INPUT); // Set speed decrease pin as input
  attachInterrupt(digitalPinToInterrupt(SPEED_INCREASE_PIN), handleSpeedIncrease, FALLING); // Attach interrupt for speed increase switch
  attachInterrupt(digitalPinToInterrupt(SPEED_DECREASE_PIN), handleSpeedDecrease, FALLING); // Attach interrupt for speed decrease switch
  attachInterrupt(0, doEncoderA, RISING);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    Speed_CMD = Serial.parseInt();
  }

  if (speedIncreaseFlag) {
    Speed_CMD += 500;
    speedIncreaseFlag = false;
  }

  if (speedDecreaseFlag) {
    Speed_CMD -= 500;
    speedDecreaseFlag = false;
  }

  Print_CNT++;

  if (Print_CNT > 1000) {
    if (Speed_CMD >= 0)
      Serial.print(Speed), Serial.print("\t"), Serial.print(Speed_CMD), Serial.print("\t"), Serial.println(0);
    if (Speed_CMD < 0)
      Serial.print(Speed * -1), Serial.print("\t"), Serial.print(Speed_CMD), Serial.print("\t"), Serial.println(0);
    Print_CNT = 0;
  }

  EncoderCal();
  PID_Control(abs(Speed_CMD));
  CMD = constrain(int(PID_Out * 255), 0, 255);
  MotorCal(Speed_CMD, CMD);
}

void doEncoderA() {
  Pluse_A++;
}

void PID_Control(float Speed_CMD) {
  err_P = (Speed_CMD / St_Speed) - (Speed / St_Speed);
  err_I = err_I + err_P;
  err_D = err_B - err_P;
  err_B = err_P;
  PID_val = ((err_P * Pv) + (err_I * Iv) + (err_D * Dv));
  PID_Out = constrain(PID_val, 0.0, 1.0);
}

void EncoderCal() {
  unsigned long currentMillis = millis();
  m = float(Pluse_A);
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    Speed = ((60.0 * m) / (float(interval) * 25.0)) * 1000;
    m = 0;
    Pluse_A = 0;
    previousMillis = currentMillis;
  }
}

void MotorCal(int Re, int CMD) {
  analogWrite(9, CMD);
  if (Re > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  if (Re < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

void handleSpeedIncrease() {
  if (!digitalRead(SPEED_INCREASE_PIN)) {
    speedIncreaseFlag = true;
  }
}

void handleSpeedDecrease() {
  if (!digitalRead(SPEED_DECREASE_PIN)) {
    speedDecreaseFlag = true;
  }
}
