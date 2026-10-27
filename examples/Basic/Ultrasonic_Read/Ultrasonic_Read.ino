/*
   ------------------------------------------------------------
   OneChip Nano Shield Library Example
   ------------------------------------------------------------

   Author  : Shourya Jain
   Company : Nova Dynamics

   Description:
   This example demonstrates how to use an ultrasonic
   distance sensor with the OneChip Nano Shield.

   The program continuously measures the distance to an
   object and prints the value to the Serial Monitor.
   If an object comes closer than 20 cm, the onboard LED1
   turns ON as an indicator.

   GitHub:
   https://github.com/novadynamics-io
   ------------------------------------------------------------
*/

#include "OnechipNanoShield.h"

// Create library object
OnechipNanoShield Nova;

void setup() {

  // Start serial communication for monitoring distance values
  Serial.begin(9600);

  // Initialize OneChip Nano Shield (LEDs + Buttons)
  Nova.setup();

  /*
     Connect Ultrasonic Sensor

     Parameters:
     ultrasonic.setup(ECHO_PIN, TRIG_PIN)

     Echo -> Pin 19
     Trig -> Pin 18
  */
  Nova.ultrasonic.setup(19, 18);

  Serial.println("Nova Shield Ultrasonic Demo");
}

void loop() {

  // Read distance from ultrasonic sensor in centimeters
  float distance = Nova.ultrasonic.distCM();

  // Print measured distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an object is closer than 20 cm, turn LED1 ON
  // Otherwise keep it OFF
  if (distance < 20 && distance > 0) {
    Nova.led1.on();
  } 
  else {
    Nova.led1.off();
  }

  // Small delay for stable readings
  delay(300);
}