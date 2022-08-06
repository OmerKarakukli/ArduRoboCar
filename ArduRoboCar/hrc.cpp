#include "hrc.h"
HRC::HRC(uint8_t trig_pin, uint8_t echo_pin)
  : _trig_pin(trig_pin)
  , _echo_pin(echo_pin)
{

}
  
void HRC::init()
{
    pinMode(_trig_pin, OUTPUT);
    digitalWrite(_trig_pin, LOW);
    pinMode(_echo_pin, INPUT);    
}

void HRC::updateDist()
{
    digitalWrite(_trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig_pin, LOW);
    uint32_t duration = pulseIn(_echo_pin, HIGH, 3500); //250000
    if (duration != 0) {
        _cur_dist = duration / 5.831;

    } else {
        _cur_dist = 600;
    }
}
