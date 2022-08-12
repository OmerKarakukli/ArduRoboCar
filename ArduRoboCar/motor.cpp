#include "motor.h"

Motor::Motor(uint8_t pwm_pin, uint8_t dir_1_pin, uint8_t dir_2_pin, bool reverse = false)
    : _pwm_pin(pwm_pin)
    , _dir_1_pin(dir_1_pin)
    , _dir_2_pin(dir_2_pin)
    , _reverse(reverse)
    , _direction(Direction::UNDEFINED)
    , _speed(0)
{

}

void Motor::init()
{
    pinMode(_pwm_pin, OUTPUT);
    analogWrite(_pwm_pin, LOW);
    _speed = 0;
    pinMode(_dir_1_pin, OUTPUT);
    digitalWrite(_dir_1_pin, LOW);
    pinMode(_dir_2_pin, OUTPUT);
    digitalWrite(_dir_2_pin, LOW);
    _direction = Direction::UNDEFINED;
}

void Motor::setDirection(Direction dir)
{
    _direction = dir;

    if(_direction == Direction::FORWARD || _direction == Direction::BACKWARD && _reverse) {
        digitalWrite(_dir_1_pin, LOW);
        digitalWrite(_dir_2_pin, HIGH);
    
    } else {
        digitalWrite(_dir_1_pin, HIGH);
        digitalWrite(_dir_2_pin, LOW);
    }
}

int16_t Motor::setSpeed(int16_t speed)
{
    if (speed < -255 || speed > 255) {
        return 1;
    }

    _speed = speed;

    if(speed == 0) {
        analogWrite(_pwm_pin, LOW);
    
    } else if(speed > 0 && _direction != Direction::FORWARD) {
        setDirection(Direction::FORWARD);

    } else if (_direction != Direction::BACKWARD){
        setDirection(Direction::BACKWARD);
    }

    analogWrite(_pwm_pin, abs(speed));
    return 0;
}
