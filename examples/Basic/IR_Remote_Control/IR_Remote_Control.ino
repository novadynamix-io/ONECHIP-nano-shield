/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates how to control the robot using
   an IR remote and a TSOP IR receiver with the OneChip Nano
   Shield.

   The program reads commands from the IR remote and performs
   actions such as moving the robot or controlling onboard LEDs.

   NOTE:
   IR remotes from different manufacturers send different
   hexadecimal command values. You must first read the values
   printed on the Serial Monitor and then assign those values
   to the commands according to the buttons on your remote.

   Hardware Required:
   • TSOP IR Receiver Module
   • IR Remote Control

   ------------------------------------------------------------
   IMPORTANT NOTE:

   When using the TSOP IR receiver, PWM on some pins may not
   work correctly due to timer usage.

   If you are controlling motors while using IR Remote, it is
   recommended to run motors at 100% speed.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include "OnechipNanoShield.h"

// Create library object
OnechipNanoShield Nova;

void setup() {

  // Initialize OneChip Nano Shield
  Nova.setup();

  /*
     Initialize IR Receiver

     Function:
     ir.setup(PIN)

     Parameter:
     PIN → Digital pin where the TSOP IR receiver output is connected
  */
  Nova.ir.setup(0);   // TSOP signal pin

  // Start Serial Monitor for debugging and reading IR codes
  Serial.begin(9600);
}

void loop() {

  /*
     Check if an IR command has been received.

     Function:
     ir.available()

     Returns:
     true  → if a command has been received
     false → if no command is available
  */
  if (Nova.ir.available()) {

    /*
       Read the received IR command.

       Function:
       ir.read()

       Returns:
       Hexadecimal command value sent by the remote button.
    */
    int cmd = Nova.ir.read();

    // Print received command value to Serial Monitor
    Serial.println(cmd);

    /*
       Map received IR command values to robot actions.

       NOTE:
       The values below correspond to a specific remote.
       You should modify these values according to the
       codes printed by your own remote.
    */

    // LED controls
    if (cmd == 0x07) Nova.led1.on();
    if (cmd == 0x16) Nova.led1.off();
    if (cmd == 0x15) Nova.led2.on();
    if (cmd == 0x19) Nova.led2.off();
  }
}