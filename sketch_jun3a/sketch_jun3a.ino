const int CH1 = 2; // pööramine
const int CH2 = 3; // edasi/tagasi

const int ENA = 5;
const int ENB = 6;
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

void setup() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int ch1 = pulseIn(CH1, HIGH, 30000);
  int ch2 = pulseIn(CH2, HIGH, 30000);

  if (ch1 < 900 || ch2 < 900) {
    stopMotors();
    return;
  }

  int throttle = ch2 - 1500;
  int steering = ch1 - 1500;

  // surnud tsoon keskel
  if (abs(throttle) < 80) throttle = 0;
  if (abs(steering) < 80) steering = 0;

  int leftSpeed  = throttle + steering;
  int rightSpeed = throttle - steering;

  leftSpeed = map(constrain(leftSpeed, -500, 500), -500, 500, -255, 255);
  rightSpeed = map(constrain(rightSpeed, -500, 500), -500, 500, -255, 255);

  driveMotor(leftSpeed, ENA, IN1, IN2);
  driveMotor(rightSpeed, ENB, IN3, IN4);
}

void driveMotor(int speed, int en, int in1, int in2) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(en, speed);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(en, -speed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(en, 0);
  }
}

void stopMotors() {
  driveMotor(0, ENA, IN1, IN2);
  driveMotor(0, ENB, IN3, IN4);
}