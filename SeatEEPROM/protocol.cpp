#include "protocol.h"
#include "uart.h"
#include "nvm_manager.h"
#include <cstring>

static constexpr uint8_t RX_FRAME_MAX = 64;
static uint8_t rx_frame[RX_FRAME_MAX];
static uint8_t rx_idx = 0;
static uint8_t in_frame = 0;

static void sendResp(uint8_t res_id, const uint8_t* payload, uint8_t len) {
    uint8_t header = CMD_HEADER;
    UART::send(&header, 1);
    uint8_t L = 1 + len; // res_id + payload
    UART::putChar(L);
    UART::putChar(res_id);
    if (len) UART::send(payload, len);
    UART::putChar(CMD_TAIL);
}

static void handleFrame(const uint8_t* frame, uint8_t len) {
    if (len < 1) { sendResp(RES_ERR, nullptr, 0); return; }
    uint8_t cmd = frame[0];
    switch (cmd) {
    case CMD_PING: {
        uint8_t p = 0x55;
        sendResp(RES_PONG, &p, 1);
        break;
    }
    case CMD_READ_PROFILE: {
        if (len < 2) { sendResp(RES_ERR, nullptr, 0); break; }
        uint8_t pid = frame[1];
        uint8_t buf[PROFILE_SIZE_BYTES];
        NVM::readProfile(pid, buf);
        sendResp(RES_PROFILE_DATA, buf, PROFILE_SIZE_BYTES);
        break;
    }
    case CMD_WRITE_PROFILE: {
        if (len < 1 + PROFILE_SIZE_BYTES) { sendResp(RES_ERR, nullptr, 0); break; }
        uint8_t pid = frame[1];
        NVM::writeProfile(pid, &frame[2]);
        uint8_t ok = RES_OK;
        sendResp(RES_OK, &ok, 1);
        break;
    }
    case CMD_READ_PARAM: {
        if (len < 2) { sendResp(RES_ERR, nullptr, 0); break; }
        uint8_t param = frame[1];
        uint16_t v = NVM::readParam(param);
        uint8_t out[2] = { uint8_t(v >> 8), uint8_t(v & 0xFF) };
        sendResp(RES_PARAM_DATA, out, 2);
        break;
    }
    case CMD_WRITE_PARAM: {
        if (len < 3) { sendResp(RES_ERR, nullptr, 0); break; }
        uint8_t param = frame[1];
        uint16_t v = (uint16_t(frame[2]) << 8) | frame[3];
        NVM::writeParam(param, v);
        uint8_t ok = RES_OK;
        sendResp(RES_OK, &ok, 1);
        break;
    }
    case CMD_READ_ALL: {
        if (len < 3) { sendResp(RES_ERR, nullptr, 0); break; }
        uint16_t size = (uint16_t(frame[1]) << 8) | frame[2];
        if (size > 2000) { sendResp(RES_ERR, nullptr, 0); break; }
        uint8_t buf[256];
        uint32_t remaining = size;
        uint32_t addr = 0;
        while (remaining) {
            uint16_t chunk = remaining > 256 ? 256 : remaining;
            NVM::readAll(buf, chunk);
            sendResp(RES_BYTE_DATA, buf, chunk);
            remaining -= chunk;
            addr += chunk;
        }
        break;
    }
    default:
        sendResp(RES_ERR, nullptr, 0);
        break;
    }
}

void protocolPoll() {
    while (UART::available()) {
        uint8_t b = UART::read();
        if (!in_frame) {
            if (b == CMD_HEADER) {
                in_frame = 1;
                rx_idx = 0;
                continue;
            }
            else continue;
        }
        else {
            if (rx_idx == 0) {
                // length byte
                rx_frame[0] = b;
                rx_idx = 1;
                continue;
            }
            else {
                uint8_t expected_len = rx_frame[0];
                if (rx_idx <= expected_len) {
                    rx_frame[rx_idx] = b;
                    rx_idx++;
                }
                else {
                    // expecting tail
                    if (b == CMD_TAIL) {
                        uint8_t payload_len = expected_len;
                        handleFrame(&rx_frame[1], payload_len);
                    }
                    else {
                        uint8_t err = RES_ERR;
                        UART::send(&err, 1);
                    }
                    in_frame = 0;
                    rx_idx = 0;
                }
            }
        }
    }
}
