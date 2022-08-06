#ifndef __HRC__H__
#define __HRC__H__

#include <Arduino.h>

class HRC {
private:
    uint8_t _trig_pin{};
    uint8_t _echo_pin{};
    uint32_t _cur_dist{};
public:
    HRC(uint8_t trig_pin, uint8_t echo_pin);
    void init();
    uint8_t get_trig_pin() { return _trig_pin; }
    uint8_t get_echo_pin() { return _echo_pin; }
    uint32_t get_cur_dist() { return _cur_dist; }
    void updateDist();
};

#endif
