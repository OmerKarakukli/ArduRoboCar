#pragma once

#include <Arduino.h>

class Motor {

    enum Direction : uint8_t {
        UNDEFINED = 0,
        BACKWARD = 1,
        FORWARD = 2
    };

private:
    uint8_t _pwm_pin;
    uint8_t _dir_1_pin;
    uint8_t _dir_2_pin;
    bool _reverse;
    Direction _direction;
    int16_t _speed;    //should be between [0 ~ 255]
    
    void setDirection(Direction dir);

public:
    Motor(uint8_t pwm_pin, uint8_t dir_1_pin, uint8_t dir_2_pin, bool reverse);
    void init();
    int16_t setSpeed(int16_t speed);
};
