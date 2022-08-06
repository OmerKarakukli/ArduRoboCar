#include "motor.h"

Motor::Motor(uint8_t pwm_pin, uint8_t dir_1_pin, uint8_t dir_2_pin, bool reverse = false)
    : _pwm_pin(pwm_pin)
    , _dir_1_pin(dir_1_pin)
    , _dir_2_pin(dir_2_pin)
    , _reverse(reverse)
    , _direction(Direction::FORWARD)
    , _duty_cycle(0)
{

}

void Motor::init()
{
    pinMode(_pwm_pin, OUTPUT);
    analogWrite(_pwm_pin, LOW);
    pinMode(_dir_1_pin, OUTPUT);
    digitalWrite(_dir_1_pin, LOW);
    pinMode(_dir_2_pin, OUTPUT);
    digitalWrite(_dir_2_pin, LOW);
}

void Motor::setDirection(Direction dir)
{
    _direction = dir;

    if(_direction ^ _reverse) {
        digitalWrite(_dir_1_pin, LOW);
        digitalWrite(_dir_2_pin, HIGH);
    
    } else {
        digitalWrite(_dir_1_pin, HIGH);
        digitalWrite(_dir_2_pin, LOW);
    }
}

void Motor::setSpeed(int16_t speed)
{
    if(speed == 0) {
        analogWrite(_pwm_pin, LOW);
    
    } else if(speed > 0) {
        setDirection(Direction::FORWARD);

    } else {
        setDirection(Direction::BACKWARD);
    }

    analogWrite(_pwm_pin, abs(speed));
}
