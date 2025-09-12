#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <cstdint>

/* Frame bytes */
constexpr uint8_t CMD_HEADER = 0xAA;
constexpr uint8_t CMD_TAIL = 0x55;

/* Commands (requests) */
constexpr uint8_t CMD_PING = 0xFF;
constexpr uint8_t CMD_READ_PROFILE = 0x10;
constexpr uint8_t CMD_WRITE_PROFILE = 0x11;
constexpr uint8_t CMD_READ_PARAM = 0x12;
constexpr uint8_t CMD_WRITE_PARAM = 0x13;
constexpr uint8_t CMD_READ_ALL = 0x20;
constexpr uint8_t CMD_WRITE_ALL = 0x21;
constexpr uint8_t CMD_READ_BYTE = 0x01;
constexpr uint8_t CMD_WRITE_BYTE = 0x02;

/* Responses (ids) */
constexpr uint8_t RES_OK = 0x00;
constexpr uint8_t RES_ERR = 0x01;
constexpr uint8_t RES_PROFILE_DATA = 0xA0;
constexpr uint8_t RES_PARAM_DATA = 0xA1;
constexpr uint8_t RES_PONG = 0xFE;
constexpr uint8_t RES_BYTE_DATA = 0xB0;

/* Parameter IDs */
constexpr uint8_t PARAM_HEIGHT = 0x01;
constexpr uint8_t PARAM_SLIDE = 0x02;
constexpr uint8_t PARAM_INCLINE = 0x03;

/* Sizes */
constexpr uint8_t PROFILE_SIZE_BYTES = 6; /* 3 params x 2 bytes each */
constexpr uint8_t CALIBRATION_SIZE = 2;

#endif
