#include "message.h"

MessagesManager::MessagesManager() {
    
}

void MessagesManager::build_status_msg(uint32_t left_hrc_dist, uint32_t front_left_hrc_dist,
    uint32_t right_hrc_dist, uint32_t front_right_hrc_dist,
    char *output_buffer, uint8_t buffer_size) {
    
    if (output_buffer == NULL || buffer_size < sizeof(status_s)) {
        return;
    }

    status_s msg;
    msg.id = MessageID::STATUS;
    msg.left_hrc_dist = left_hrc_dist;
    msg.front_left_hrc_dist = front_left_hrc_dist;
    msg.right_hrc_dist = right_hrc_dist;
    msg.front_right_hrc_dist = front_right_hrc_dist;

    msg.crc = 0;
    for (uint8_t i = 0; i < sizeof(status_s) - 1; i++) {
        uint8_t *msg_ptr = (uint8_t*)&msg;
        msg.crc ^= msg_ptr[i];
    }

    memcpy(output_buffer, &msg, sizeof(status_s));
}

void MessagesManager::build_command_msg(Command command, char *output_buffer, uint8_t buffer_size) {
        
    if (output_buffer == NULL || buffer_size < sizeof(command_s)) {
        return;
    }

    command_s msg;
    msg.id = MessageID::COMMAND;
    msg.cmd = command;

    msg.crc = 0;
    for (uint8_t i = 0; i < sizeof(command_s) - 1; i++) {
        uint8_t *msg_ptr = (uint8_t*)&msg;
        msg.crc ^= msg_ptr[i];
    }

    memcpy(output_buffer, &msg, sizeof(command_s));
}

int16_t MessagesManager::check_status_msg(status_s *msg, char *buffer) {
    memcpy(msg, buffer, sizeof(status_s));

    uint8_t calc_crc = 0;
    for (uint8_t i = 0; i < sizeof(status_s) - 1; i++) {
        uint8_t *msg_ptr = (uint8_t*)msg;
        calc_crc ^= msg_ptr[i];
    }

    if (calc_crc == msg->crc) {
        return 0;
    
    } else {
        return 1;
    }
}

int16_t MessagesManager::check_command_msg(status_s *msg, char *buffer) {
    memcpy(msg, buffer, sizeof(command_s));

    uint8_t calc_crc = 0;
    for (uint8_t i = 0; i < sizeof(command_s) - 1; i++) {
        uint8_t *msg_ptr = (uint8_t*)msg;
        calc_crc ^= msg_ptr[i];
    }

    if (calc_crc == msg->crc) {
        return 0;
    
    } else {
        return 1;
    }
}