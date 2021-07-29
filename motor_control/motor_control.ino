// using L298N motor controller

#include "Motor.h"

#ifndef FULL_SPEED
#define FULL_SPEED 255
#endif

#ifndef SPEED_GRADIENT
#define SPEED_GRADIENT 3   // cannot be zero
#endif

#define ena 5
#define in1 6
#define in2 7

#define in3 8
#define in4 9
#define enb 10

// create motor objects
Motor motorA(ena, in1, in2);
Motor motorB(enb, in3, in4);

void setup() {
  motorA.stop();
  motorB.stop();
  delay(100);  // delay
}

void loop() {
  // move motors forward
  motorA.forward(FULL_SPEED);
  motorB.forward(FULL_SPEED);
  delay(1000);  // delay

  // stop motors
  motorA.stop();
  motorB.stop();
  delay(1000);  // delay

  // move motors backward
  motorA.backward(FULL_SPEED);
  motorB.backward(FULL_SPEED);
  delay(1000);  // delay

  // stop motors
  motorA.stop();
  motorB.stop();
  delay(1000);  // delay
}
