/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates how to read the onboard push
   buttons of the OneChip Nano Shield and display their
   state on the Serial Monitor.

   When a button is pressed or released, its state is printed
   through UART.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include <OnechipNanoShield.h>

// Create an object to access OneChip Nano Shield functions
OnechipNanoShield Nova;

void setup() {

  // Initialize the OneChip Nano Shield
  Nova.setup();

  // Start serial communication for debugging
  Serial.begin(9600);

  // Print startup message
  Serial.println("Onechip Nano Shield Test");

}

void loop() {

  // Read button states
  bool b1 = Nova.btn1.read();   // Button 1 state
  bool b2 = Nova.btn2.read();   // Button 2 state

  // Print Button 1 status
  Serial.print("Button 1: ");
  Serial.print(b1 ? "PRESSED" : "RELEASED");
  Serial.print("   |   ");

  // Print Button 2 status
  Serial.print("Button 2: ");
  Serial.println(b2 ? "PRESSED" : "RELEASED");

  // Small delay for readability in Serial Monitor
  delay(300);

}