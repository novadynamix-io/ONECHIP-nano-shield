/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates basic LED control using the
   OneChip Nano Shield library. The onboard LEDs are turned
   ON and OFF repeatedly with a short delay.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include <OnechipNanoShield.h>

// Create an object to access all OneChip Nano Shield functions
OnechipNanoShield Nova;

void setup() {

  // Initialize the OneChip Nano Shield
  // This configures all required pins and modules
  Nova.setup();

}

void loop() {

  // Turn both onboard LEDs ON
  Nova.led1.on();
  Nova.led2.on();

  delay(500);  // wait for 500 milliseconds

  // Turn both onboard LEDs OFF
  Nova.led1.off();
  Nova.led2.off();

  delay(500);  // wait for 500 milliseconds

}