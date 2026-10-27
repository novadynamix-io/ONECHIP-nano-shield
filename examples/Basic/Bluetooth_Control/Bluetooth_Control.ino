/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates Bluetooth communication using
   the HC-05 module connected to the OneChip Nano Shield.

   The HC-05 is connected to a dedicated hardware serial
   port on the shield.

   Incoming Bluetooth commands are read and processed by
   a command handler function, allowing control of LEDs
   or other robot actions.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include "OnechipNanoShield.h"

// Create library object
OnechipNanoShield Nova;

// Use hardware serial for HC-05 communication
// The OneChip Nano Shield provides a dedicated serial
// connection for the HC-05 module
#define BT Serial

void setup() {

  // Start Bluetooth communication (HC-05 default baud rate)
  BT.begin(9600);

  // Start USB serial for debugging / monitoring
  Serial.begin(9600);

  // Initialize the OneChip Nano Shield
  Nova.setup();
}

void loop() {

  // Check if data is received from Bluetooth
  if (BT.available()) {

    // Read incoming command
    char cmd = BT.read();

    // Print received command to Serial Monitor
    Serial.println(cmd);

    // Send command to handler function
    handleCommand(cmd);
  }
}


// ------------------------------------------------------------
// COMMAND HANDLER
// ------------------------------------------------------------

/*
   handleCommand(cmd)

   Processes Bluetooth commands received from the HC-05 module.

   Parameter:
   cmd → Character command received from Bluetooth.

   You can add robot control logic inside each case
   to perform actions such as moving motors, turning LEDs
   on/off, or controlling sensors.

   Example:
   'a' → LED1 ON
   'b' → LED1 OFF
   'c' → LED2 ON
   'd' → LED2 OFF
*/

void handleCommand(char cmd) {

  switch (cmd) {

    // Turn LED1 ON
    case 'a':
      Nova.led1.on();
      break;

    // Turn LED1 OFF
    case 'b':
      Nova.led1.off();
      break;

    // Turn LED2 ON
    case 'c':
      Nova.led2.on();
      break;

    // Turn LED2 OFF
    case 'd':
      Nova.led2.off();
      break;

    // Move forward command (user logic can be added)
    case 'U':
      
      break;

    // Move backward command
    case 'D':
      
      break;

    // Turn left command
    case 'L':
      
      break;

    // Turn right command
    case 'R':
      
      break;

    // Stop command
    case '0':
      
      break;

    // Unknown command
    default:
      
      break;
  }
}