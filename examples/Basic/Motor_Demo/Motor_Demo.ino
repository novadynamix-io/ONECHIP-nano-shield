/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates different robot motion
   commands available in the OneChip Nano Shield library.

   The robot performs forward motion, backward motion,
   curved turns, smooth car-like turns, and advanced
   differential wheel control.


   NOTE:
   All motion functions in this library use speed values
   in the range of 0 to 100 (percentage), NOT the standard
   Arduino PWM range of 0 to 255.


   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include "OnechipNanoShield.h"

// Create library object
OnechipNanoShield Nova;

void setup() {

  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize OneChip Nano Shield
  Nova.setup();

  Serial.println("Nova Robot Motion Demo");

}

void loop() {

  // ---------------- BASIC MOTION ----------------

  // Move forward at full speed
  Nova.move.FORWARD(100);
  delay(2000);

  // Move backward at 50% speed
  Nova.move.BACKWARD(50);
  delay(2000);


  // ---------------- CURVED TURNS ----------------

  // Left turn with radius control
  // Parameters: speed %, turn radius %
  Nova.move.LEFT(25, 0);   // speed = 25%, radius = 0%
  delay(2000);

  // Right turn with radius control
  Nova.move.RIGHT(60, 20); // speed = 60%, radius = 20%
  delay(2000);


  // ---------------- SMOOTH CAR-LIKE TURNS ----------------

  // Smooth left turn (car-like motion)
  // One pair of wheels stops while the other moves
  Nova.move.SLOWLEFT(60);
  delay(1500);

  // Smooth right turn (car-like motion)
  // One pair of wheels stops while the other moves
  Nova.move.SLOWRIGHT(60);
  delay(1500);


  // ---------------- ADVANCED TURN CONTROL ----------------

  /*
     Universal Motion Controller

     TURN(left_speed, right_speed)

     Direct control of left and right wheel motors.

     Parameter Range:
     -100 to 100

     Positive values  → Forward direction
     Negative values  → Reverse direction

     This allows many types of motion:
     • Smooth turns
     • Sharp turns
     • Reverse motion
     • In-place rotation

     Examples:
     (50, 50)    → move forward
     (-50, -50)  → move backward
     (0, 60)     → smooth right turn
     (-70, 70)   → spin in place
  */

  // Spin turn using raw TURN
  Nova.move.TURN(-70, 70);   // spin left (Left speed, Right speed)
  delay(1500);

  // Soft turn using raw TURN
  Nova.move.TURN(70, 0);     // soft right turn
  delay(1500);


  // ---------------- STOP ROBOT ----------------

  Nova.move.STOP();
  delay(3000);

}