#pragma once

#include <Arduino.h>

class Motor {

    enum Direction : uint8_t {
        BACKWARD = 0,
        FORWARD = 1
    };

private:
    uint8_t _pwm_pin;
    uint8_t _dir_1_pin;
    uint8_t _dir_2_pin;
    bool _reverse;
    Direction _direction;
    int16_t _duty_cycle;    //should be between [0 ~ 255]
    
    void setDirection(Direction dir);

public:
    Motor(uint8_t pwm_pin, uint8_t dir_1_pin, uint8_t dir_2_pin, bool reverse);
    void init();
    void setSpeed(int16_t speed);
};
