/**
 * @file
 * 
 * Serial driver for a two DOF plot arm. Should run on any Arduino; tested with Teensy 2.0.
 */

#include <Servo.h>

Servo j1; // Shoulder joint
Servo j2; // Elbow joint

// variables to store the servo position
int pos = 0;
int _phi1 = 0;
int _phi2 = 0;

// Speed limiter: will not accept a change in position greater than this
int max_dphi = 2;

void setup() {
  j1.attach(9);  // attaches the servo on pin 9 to the servo object
  j2.attach(10);  // attaches the servo on pin 10 to the servo object
}

/**
 * Attempts to perform a joint-space move.
 * 
 * @return True on success.
 */
bool goto_angles(int phi1, int phi2) {
  if(abs(_phi1 - phi1) > max_dphi || abs(_phi2 - phi2) > max_dphi) {
    return false;
  }
  j1.write(_phi1);
  j2.write(_phi2);
  return true; 
}

void loop() {
  for (pos = 0; pos <= 30; pos += 1) {
    if(goto_angles(pos, pos)) {
      _phi1 = pos;
      _phi2 = pos;
    }
    delay(50);
  }
  for (pos = 30; pos >= 0; pos -= 1) {
    if(goto_angles(pos, pos)) {
      _phi1 = pos;
      _phi2 = pos;
    }
    delay(50);
  }
}

