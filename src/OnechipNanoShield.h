#ifndef ONECHIP_NANOSHIELD_H
#define ONECHIP_NANOSHIELD_H


#include <Arduino.h>

/* ===== ONECHIP NANO SHIELD : PIN MAP ===== */
/* These numbers MUST match your PCB schematic */

// LEDs connected on the board
#define ONS_LED1   12
#define ONS_LED2   13

//BUTTONS connected on the board
#define ONS_BTN1  3
#define ONS_BTN2  2

// ===== MOTOR DRIVER PINS =====
#define ONS_L_PWM   6
#define ONS_L_IN1   7
#define ONS_L_IN2   8

#define ONS_R_PWM   11
#define ONS_R_IN1   10
#define ONS_R_IN2   9

/* ===== LED CLASS ===== */
class LED {
  public:
    LED(uint8_t pin);
    void on();
    void off();
  private:
    uint8_t _pin;
};


/* ===== BTN CLASS ===== */
class BTN{
  public:
   BTN(uint8_t pin);
   bool read();
  private:
    uint8_t _pin;
};

/* ===== MOTOR CLASS ===== */
class Move {
  public:
    Move();

    void begin();

    void FORWARD(uint8_t speed);
    void BACKWARD(uint8_t speed);

    void LEFT(uint8_t speed, uint8_t radius);
    void RIGHT(uint8_t speed, uint8_t radius);

    void SLOWLEFT(uint8_t speed);
    void SLOWRIGHT(uint8_t speed);

    void STOP();

    void TURN(int leftSpeed, int rightSpeed);   // -100 to +100

  private:
    uint8_t speedToPWM(uint8_t s);
    void setLeft(int speed);
    void setRight(int speed);
};



/* ===== ULTRASONIC CLASS ===== */
class Ultrasonic {
  public:
    Ultrasonic();                  // Empty constructor
    void setup(uint8_t echoPin, uint8_t trigPin);   // Select pins
    float distCM();                // Read distance in cm

  private:
    uint8_t _echo;
    uint8_t _trig;
};

/* ===== IR TSOP CLASS ===== */
class IR_TSOP {
  public:
    IR_TSOP();
    void setup(uint8_t pin);
    bool available();
    uint16_t read();

  private:
    uint8_t _pin;
};


/* ===== PID CLASS ===== */

class OnechipPID {
  public:
    OnechipPID(float kp, float ki, float kd, float dt);

    void setting(float kp, float ki, float kd);
    void setTimeStep(float dt);
    void reset();

    float correction(float target, float currentValue);

  private:
    float Kp, Ki, Kd;
    float dt;

    float error;
    float prevError;
    float integral;
    float derivative;

    float pidOutput;
};

/* ===== MAIN BOARD CLASS ===== */
class OnechipNanoShield {
  public:
    OnechipNanoShield();   // Uses fixed board pins // this is a constructor
    void setup();

    LED led1;
    LED led2;

    BTN btn1;
    BTN btn2;

    Move move;

    Ultrasonic ultrasonic;
    IR_TSOP ir;
    OnechipPID pid;

};

#endif
