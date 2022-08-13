#pragma once

#include <Arduino.h>

class MessagesManager {
public:
    enum MessageID : uint8_t {
        UNDEFINED = 0,
        STATUS = 1,
        COMMAND = 2
    };

    enum Command : uint8_t {
        STATUS_REQUEST = 0,
        GO_FORWARD = 1,
        GO_BACKWARD = 2,
        TURN_LEFT = 3,
        TURN_RIGHT = 4,
        STOP = 5
    };

    struct status_s
    {
        MessageID id;
        uint32_t left_hrc_dist;
        uint32_t front_left_hrc_dist;
        uint32_t right_hrc_dist;
        uint32_t front_right_hrc_dist;
        uint8_t crc;
    } __attribute__((__packed__));

    struct command_s
    {
        MessageID id;
        Command cmd;
        uint8_t crc;
    } __attribute__((__packed__));

    MessagesManager();
    
    void build_status_msg(uint32_t left_hrc_dist, uint32_t front_left_hrc_dist,
        uint32_t right_hrc_dist, uint32_t front_right_hrc_dist,
        char *output_buffer, uint8_t buffer_size);

    void build_command_msg(Command command, char *output_buffer, uint8_t buffer_size);

    int16_t check_status_msg(status_s *msg, char *buffer);

    int16_t check_command_msg(status_s *msg, char *buffer);
};