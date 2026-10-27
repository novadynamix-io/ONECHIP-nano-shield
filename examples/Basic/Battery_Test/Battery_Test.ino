#include <OnechipNanoShield.h>

OnechipNanoShield nova;

float calibration = 1.0;        // starts at 1.0, the calibration step below fixes it
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(9600);
  nova.setup();

  // warning voltage 7.4V, low voltage 7.0V, battery pin A7, LED pin 13, feature ON, calibration
  nova.battery.setup(7.4, 7.0, A7, 13, true, calibration);

  // ----- calibration: type the multimeter reading in the Serial Monitor -----
  float meter = 0;
  while (meter < 3 || meter > 9) {
    Serial.println("Type multimeter battery reading (example 8.00), then press Enter:");
    while (!Serial.available());
    meter = Serial.parseFloat();
    while (Serial.available()) Serial.read();      // clear the Enter key
  }

  // new calibration = old calibration x (multimeter / shown voltage)
  calibration = calibration * (meter / nova.battery.voltage());
  nova.battery.setup(7.4, 7.0, A7, 13, true, calibration);

  Serial.print("Calibration = ");
  Serial.println(calibration, 4);                  // use this number in your own code
}

void loop() {
  nova.battery.update();                           // keeps the warning LED flashing

  if (millis() - lastPrint >= 500) {
    lastPrint = millis();

    nova.battery.print();                          // "Battery: 7.85 V"
    // float v = nova.battery.voltage();           // same voltage, as a number

    Serial.print("Scale: ");
    Serial.print(nova.battery.scale(), 3);         // lowV / battery voltage (max 1.0)
    Serial.print("   Calibration: ");
    Serial.println(calibration, 4);
  }
}
