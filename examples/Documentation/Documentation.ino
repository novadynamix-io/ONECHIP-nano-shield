/*
   ------------------------------------------------------------
   OneChip Nano Shield Library
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics
   
   Description:
   Arduino library designed for the OneChip Nano Shield.
   It simplifies controlling motors, sensors, LEDs, buttons,
   and wireless modules using easy and structured functions.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/


// ---------------- PIN MAPPING TABLE ----------------

/*
| Arduino Pin | Connected Component | Status |
|-------------|---------------------|--------|
| D0          | HC-05 TX            | Used   |
| D1          | HC-05 RX            | Used   |
| D2          | Push Button 2       | Used   |
| D3          | Push Button 1       | Used   |
| D4          | —                   | Free   |
| D5          | —                   | Free   |
| D6          | TB6612FNG M2S       | Used   |
| D7          | TB6612FNG M2A       | Used   |
| D8          | TB6612FNG M2B       | Used   |
| D9          | TB6612FNG M1A       | Used   |
| D10         | TB6612FNG M1B       | Used   |
| D11         | TB6612FNG M1S       | Used   |
| D12         | LED1                | Used   |
| D13         | LED2                | Used   |
| A0 – A7     | Analog Inputs       | Free   |
*/


/*
   ------------------------------------------------------------
   DISCLAIMER
   ------------------------------------------------------------

   The following code is provided only as a reference to
   demonstrate the available functions in the OneChip
   Nano Shield library.

   IT IS NOT INTENDED TO BE COMPILED OR UPLOADED DIRECTLY
   AS A WORKING PROGRAM.

   The purpose of this snippet is to help users understand
   how to access different modules such as LEDs, buttons,
   motors, and sensors using the library.

   Refer to the "examples" folder in the GitHub repository
   for complete and runnable Arduino sketches.
   ------------------------------------------------------------
   
   NOTE:
   All motion functions in this library use speed values
   in the range of 0 to 100 (percentage), NOT the standard
   Arduino PWM range of 0 to 255.
   ------------------------------------------------------------
*/


// Example Usage of Library Functions

#include <OnechipNanoShield.h>

OnechipNanoShield Nova;

void setup() {

  Nova.setup();                 // Initialize OneChip Nano Shield

  // Setup ultrasonic sensor (Trigger Pin, Echo Pin)
  Nova.ultrasonic.setup(19, 18);

  // ---------------- PID CONTROLLER ----------------
  // Configure PID gains (Proportional, Integral, Derivative)
  Nova.pid.setting(4.0, 0.0, 1.5);

  // Set PID calculation timestep (seconds)
  // Example: 0.05 = 50 ms control loop
  Nova.pid.setTimeStep(0.05);

}

void loop(){

  // Read push buttons
  Nova.btn1.read();
  Nova.btn2.read();

  // LED control
  Nova.led1.on();
  Nova.led1.off();

  Nova.led2.on();
  Nova.led2.off();

  // Basic robot movements
  Nova.move.FORWARD(100);       // speed = 100%
  Nova.move.BACKWARD(50);       // speed = 50%

  // Turning with speed and radius
  Nova.move.LEFT(25, 0);        // speed = 25%, radius = 0%
  Nova.move.RIGHT(60, 20);      // speed = 60%, radius = 20%

  // Smooth turning 
  // One side wheels stop while the other side moves
  Nova.move.SLOWLEFT(60);       // speed = 60%
  Nova.move.SLOWRIGHT(60);

  // Universal Motion Controller : Advanced Level 
  // Direct wheel control (Left speed, Right speed)
  // Range: -100% to 100%
  // Positive values → forward direction
  // Negative values → reverse direction
  // Allows smooth turns, sharp turns, reverse motion, or in-place rotation

  // Examples:
  // (50, 50)    → move forward
  // (-50, -50)  → move backward
  // (0, 60)     → smooth right turn
  // (-70, 70)   → spin in place
  Nova.move.TURN(-70, 70); 

  // Stop robot
  Nova.move.STOP();

  // Ultrasonic distance reading
  Nova.ultrasonic.distCM();


  // ---------------- PID CALCULATION ----------------
  // Computes PID correction value
  // Parameters: (targetValue, currentValue)
  // Returns positive or negative correction output
  Nova.pid.correction(20, Nova.ultrasonic.distCM());

}

/*IT IS NOT INTENDED TO BE COMPILED OR UPLOADED DIRECTLY
AS A WORKING PROGRAM.*/