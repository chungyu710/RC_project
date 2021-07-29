/*
    Motor.h - Library for driving a DC motor using an L298N motor controller.
    Created by Chung Yu, July 28, 2021.
 */

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor{
    private:
    // attributes
    int _en;
    int _in1;
    int _in2;

    // current power for ramp up/down
    int curr_pow; // ranges from 0 to 255
    
    public:
    //constructor
    Motor(int enPin, int in1Pin, int in2Pin);

    // methods
    void stop();

    void forward(int target_pow);

    void backward(int target_pow);

    void rampSpeed(int target_pow);

    int absValueInt(int value);
};

#endif