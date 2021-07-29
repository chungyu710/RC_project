/*
    Motor.cpp - Library for driving a DC motor using an L298N motor controller.
    Created by Chung Yu, July 28, 2021.
*/

#include "Arduino.h"
#include "Motor.h"

#ifndef SPEED_GRADIENT
#define SPEED_GRADIENT 10   // cannot be zero
#endif

//constructor
Motor::Motor(int en, int in1, int in2) {
    curr_pow = 0;
    
    _en = en;
    _in1 = in1;
    _in2 = in2;
    
    pinMode(_en, OUTPUT);
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
}

// methods
void Motor::stop() {
    rampSpeed(0);
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
}

void Motor::forward(int target_pow) {
    rampSpeed(target_pow);
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    // TODO: determine which direction is forward or backward
}

void Motor::backward(int target_pow) {
    rampSpeed(target_pow);
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
}

void Motor::rampSpeed(int target_pow) {
    int gradient;
    while(target_pow != curr_pow) {
        // determine the speed gradient to use based on how far
        // the target power is compared to the current power
        if(absValueInt(target_pow - curr_pow) > SPEED_GRADIENT) {
            gradient = SPEED_GRADIENT;
        }
        else {
            gradient = 1;
        }
        
        // ramp up/down the current power accordingly to 'zero-in' on the target power
        if(curr_pow < target_pow) {
            curr_pow += gradient;
        }
        else {
            curr_pow -= gradient;
        }

        analogWrite(_en, curr_pow);
    }
}

int Motor::absValueInt(int value) {
    if(value < 0) {
        return -value;
    }
    else {
        return value;
    }
}