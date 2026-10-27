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

// ===== BATTERY MONITOR =====
#define ONS_BAT_PIN      A7     // analog pin that reads the battery (default)
#define ONS_BAT_DIVIDER  2.0    // 10k + 10k voltage divider (halves the voltage)

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

/* ===== BATTERY CLASS ===== */
class Battery {
  public:
    Battery();

    // warningV    : LED flashes normally at or below this voltage
    // lowV        : LED flashes fast at or below this voltage
    //               also 100% motor speed = this voltage (motor runs 0V to lowV)
    // batPin      : analog pin that reads the battery
    // ledPin      : LED pin used for the warning
    // enabled     : true = battery feature ON, false = OFF (motor runs 0V to full battery)
    // calibration : multiply the reading to match your multimeter
    void setup(float warningV = 7.4, float lowV = 7.0,
               uint8_t batPin = ONS_BAT_PIN, uint8_t ledPin = ONS_LED2,
               bool enabled = true, float calibration = 1.0);

    void update();        // reads battery + flashes LED (Move calls this by itself)
    float voltage();      // battery voltage in V
    void print();         // prints the voltage to Serial (only when you call it)
    bool isOn();          // is the battery feature ON?
    float scale();        // lowV / battery voltage (0 to 1), used by Move

  private:
    float readRaw();

    float _warningV;
    float _lowV;
    uint8_t _batPin;
    uint8_t _ledPin;
    float _calibration;
    bool _enabled;

    float _batteryV;
    unsigned long _lastRead;
    unsigned long _lastBlink;
    bool _ledState;
    bool _blinking;
};

/* ===== MOTOR CLASS ===== */
class Move {
  public:
    Move();

    void begin();

    void attachBattery(Battery* b);   // used by the board class, you don't call this

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

    Battery* _battery;
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
    Battery battery;

    Ultrasonic ultrasonic;
    IR_TSOP ir;
    OnechipPID pid;

};

#endif
