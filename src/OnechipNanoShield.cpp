#include "OnechipNanoShield.h"
#include <IRremote.h>

/* ===== LED CLASS IMPLEMENTATION ===== */

LED::LED(uint8_t pin) {
  _pin = pin;
}

void LED::on() {
  digitalWrite(_pin, HIGH);
}

void LED::off() {
  digitalWrite(_pin, LOW);
}


//========= BTN CLASS IMPLEMENTATION ====

BTN::BTN(uint8_t pin) {
 _pin = pin;
}

bool BTN::read(){
  return digitalRead(_pin)==LOW;
}


/* ===== MOVE  ===== */

Move::Move() {}

void Move::begin() {
  pinMode(ONS_L_IN1, OUTPUT);
  pinMode(ONS_L_IN2, OUTPUT);
  pinMode(ONS_L_PWM, OUTPUT);

  pinMode(ONS_R_IN1, OUTPUT);
  pinMode(ONS_R_IN2, OUTPUT);
  pinMode(ONS_R_PWM, OUTPUT);

  STOP();
}

uint8_t Move::speedToPWM(uint8_t s) {
  if (s == 0) return 0;
  return map(s, 0, 100, 22, 225);
}

void Move::setLeft(int speed) {
  if (speed > 0) {
    digitalWrite(ONS_L_IN1, HIGH);
    digitalWrite(ONS_L_IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(ONS_L_IN1, LOW);
    digitalWrite(ONS_L_IN2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(ONS_L_IN1, LOW);
    digitalWrite(ONS_L_IN2, LOW);
  }
  analogWrite(ONS_L_PWM, speedToPWM(speed));
}

void Move::setRight(int speed) {
  if (speed > 0) {
    digitalWrite(ONS_R_IN1, HIGH);
    digitalWrite(ONS_R_IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(ONS_R_IN1, LOW);
    digitalWrite(ONS_R_IN2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(ONS_R_IN1, LOW);
    digitalWrite(ONS_R_IN2, LOW);
  }
  analogWrite(ONS_R_PWM, speedToPWM(speed));
}

void Move::TURN(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, -100, 100);
  rightSpeed = constrain(rightSpeed, -100, 100);

  setLeft(leftSpeed);
  setRight(rightSpeed);
}

void Move::FORWARD(uint8_t speed) {
  TURN(speed, speed);
}

void Move::BACKWARD(uint8_t speed) {
  TURN(-speed, -speed);
}

void Move::LEFT(uint8_t speed, uint8_t radius) {
  radius = constrain(radius, 0, 100);

  if (radius == 0) {
    // On-the-spot spin
    TURN(-speed, speed);
  } else {
    // Differential steering
    int L = speed * (radius / 100.0);
    int R = speed;
    TURN(L, R);
  }
}

void Move::RIGHT(uint8_t speed, uint8_t radius) {
  radius = constrain(radius, 0, 100);

  if (radius == 0) {
    // On-the-spot spin
    TURN(speed, -speed);
  } else {
    // Differential steering
    int L = speed;
    int R = speed * (radius / 100.0);
    TURN(L, R);
  }
}


void Move::SLOWLEFT(uint8_t speed) {
  TURN(0, speed);
}

void Move::SLOWRIGHT(uint8_t speed) {
  TURN(speed, 0);
}

void Move::STOP() {
  TURN(0, 0);
}

// ===== PID CLASS IMPLEMENTATION ===

OnechipPID::OnechipPID(float kp, float ki, float kd, float dt) {
  Kp = kp;
  Ki = ki;
  Kd = kd;
  this->dt = dt;

  error = 0;
  prevError = 0;
  integral = 0;
  derivative = 0;
  pidOutput = 0;
}

void OnechipPID::setting(float kp, float ki, float kd) {
  Kp = kp;
  Ki = ki;
  Kd = kd;
}

void OnechipPID::setTimeStep(float dt) {
  this->dt = dt;
}

void OnechipPID::reset() {
  error = 0;
  prevError = 0;
  integral = 0;
  derivative = 0;
  pidOutput = 0;
}

float OnechipPID::correction(float target, float currentValue) {

  // ---- ADD THIS GUARD ----
  if (dt <= 0) return pidOutput;
  // -----------------------

  error = target - currentValue;

  integral += error * dt;

  // ---- ADD THIS LINE HERE ----     // MAY HAVE TO CHANGE THE LIMITS CURRENTLY SET TO -100 TO 100 FOR SPEED
  integral = constrain(integral, -100, 100);
  // ---------------------------


  derivative = (error - prevError) / dt;

  pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);

  prevError = error;

  return pidOutput;
}


/* ===== ULTRASONIC CLASS IMPLEMENTATION ===== */

Ultrasonic::Ultrasonic() {
  _echo = 0;
  _trig = 0;
}

void Ultrasonic::setup(uint8_t echoPin, uint8_t trigPin) {
  _echo = echoPin;
  _trig = trigPin;

  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);

  digitalWrite(_trig, LOW);   // keep trig low initially
}

float Ultrasonic::distCM() {
  long duration;

  // Send 10µs trigger pulse
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  // Measure echo pulse
  duration = pulseIn(_echo, HIGH, 30000); // 30ms timeout (~5m)

  // Convert to centimeters
  float distance = duration * 0.0343 / 2;

  return distance;
}

/* ===== IR TSOP IMPLEMENTATION ===== */

IR_TSOP::IR_TSOP() {
  _pin = 0;
}

void IR_TSOP::setup(uint8_t pin) {
  _pin = pin;
  IrReceiver.begin(_pin, ENABLE_LED_FEEDBACK);
}

bool IR_TSOP::available() {
  return IrReceiver.decode();
}

uint16_t IR_TSOP::read() {
  uint16_t cmd = IrReceiver.decodedIRData.command;
  IrReceiver.resume();
  return cmd;
}


/* ===== ONECHIP NANO SHIELD IMPLEMENTATION ===== */

// This constructor permanently links your PCB pins
OnechipNanoShield::OnechipNanoShield()
  : led1(ONS_LED1),   // LED1 is physically on this pin
    led2(ONS_LED2),   // LED2 is physically on this pin
    btn1(ONS_BTN1),   // BTN1 is physically on this pin
    btn2(ONS_BTN2),   // BTN2 is physically on this pin
    pid(1.0, 0.0, 0.0, 0.01) 
{
}

void OnechipNanoShield::setup() {
  pinMode(ONS_LED1, OUTPUT);
  pinMode(ONS_LED2, OUTPUT);
  pinMode(ONS_BTN1, INPUT_PULLUP);
  pinMode(ONS_BTN2, INPUT_PULLUP);

  // Make sure LEDs start OFF
  digitalWrite(ONS_LED1, LOW);
  digitalWrite(ONS_LED2, LOW);

    move.begin();  
}
