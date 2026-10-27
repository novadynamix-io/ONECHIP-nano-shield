#include <OnechipNanoShield.h>

OnechipNanoShield nova;

// ===== TEST PLAN: motor speed 100 -> 50 -> 10, 5 seconds each, then repeat =====
const int speeds[3] = {100, 50, 10};
const unsigned long STEP_TIME = 5000;    // 5 seconds for each speed

int step = 0;
unsigned long stepStart = 0;
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(9600);                    // the library never starts Serial, you do it here
  nova.setup();

  // ---------- 1) nova.battery.setup(...) ----------
  // nova.battery.setup(warningV, lowV, batPin, ledPin, enabled, calibration);
  //
  //   warningV    : 7.4  -> LED flashes normally at or below this voltage
  //   lowV        : 7.0  -> LED flashes fast at or below this voltage
  //                         and speed 100 = 7.0V (motor runs 0V to 7.0V)
  //   batPin      : A7   -> pin that reads the battery
  //   ledPin      : 13   -> LED used for the warning
  //   enabled     : true -> battery feature ON, false -> OFF (motor runs 0V to full battery)
  //   calibration : 1.0  -> change it until print() matches your multimeter
  nova.battery.setup(7.4, 7.0, A7, 13, true, 1.0);

  // You can also write only the first two numbers, the rest use default values:
  // nova.battery.setup(7.4, 7.0);

  // To test with the battery feature OFF, use false:
  // nova.battery.setup(7.4, 7.0, A7, 13, false, 1.0);

  // ---------- 2) nova.battery.isOn() ----------
  Serial.print("Battery feature ON? ");
  Serial.println(nova.battery.isOn() ? "YES" : "NO");

  stepStart = millis();
}

void loop() {
  // ----- change the speed every 5 seconds (no delay, so the battery check keeps running) -----
  if (millis() - stepStart >= STEP_TIME) {
    stepStart = millis();
    step = (step + 1) % 3;               // 0 -> 1 -> 2 -> 0 ...
    Serial.print("--- New speed: ");
    Serial.println(speeds[step]);
  }

  // Move commands call the battery check by themselves (this is the "background" part)
  nova.move.FORWARD(speeds[step]);

  // ----- print every 500 ms -----
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();

    // ---------- 3) nova.battery.print() ----------
    // prints "Battery: 7.85 V" only when you call it
    nova.battery.print();

    // ---------- 4) nova.battery.voltage() ----------
    // gives the battery voltage as a number
    float v = nova.battery.voltage();

    // ---------- 5) nova.battery.scale() ----------
    // lowV / battery voltage: below 1.0 means the code is lowering the motor PWM
    float s = nova.battery.scale();

    Serial.print("Speed: ");
    Serial.print(speeds[step]);
    Serial.print("   Voltage: ");
    Serial.print(v, 2);
    Serial.print(" V   Scale: ");
    Serial.println(s, 3);
  }

  // ---------- 6) nova.battery.update() ----------
  // Not needed here because nova.move.FORWARD() already calls it.
  // Use it only if your loop sometimes does NOT call any nova.move command,
  // so the warning LED can still flash:
  // nova.battery.update();
}
