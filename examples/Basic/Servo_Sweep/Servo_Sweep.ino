/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates how to control multiple servo
   motors using an Arduino. Six servos are connected to
   analog pins A0–A5 (14–19) and move together from
   0° to 180° and back repeatedly.

   This can be used to test servo connections for robotic
   arms, grippers, or multi-joint mechanisms.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include <Servo.h>

// Create Servo objects to control six servos
Servo S1;
Servo S2;
Servo S3;
Servo S4;
Servo S5;
Servo S6;

// Variable to store the servo position
int angle = 0;

void setup() {

  // Attach servos to pins (A0–A5 correspond to 14–19)
  S1.attach(14);
  S2.attach(15);
  S3.attach(16);
  S4.attach(17);
  S5.attach(18);
  S6.attach(19);

}

void loop() {

  // ----------- MOVE SERVOS FROM 0° TO 180° -----------

  // Gradually increase angle
  for (angle = 0; angle <= 180; angle += 1) {

    // Move all servos to the same angle
    S1.write(angle);
    S2.write(angle);
    S3.write(angle);
    S4.write(angle);
    S5.write(angle);
    S6.write(angle);

    // Wait for servo to reach the position
    delay(15);
  }

  // ----------- MOVE SERVOS FROM 180° BACK TO 0° -----------

  // Gradually decrease angle
  for (angle = 180; angle >= 0; angle -= 1) {

    // Move all servos to the same angle
    S1.write(angle);
    S2.write(angle);
    S3.write(angle);
    S4.write(angle);
    S5.write(angle);
    S6.write(angle);

    // Wait for servo to reach the position
    delay(15);
  }

}