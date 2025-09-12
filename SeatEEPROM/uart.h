#ifndef UART_H
#define UART_H
#include <cstdint>

namespace UART {
    void init(uint32_t baud);
    void putChar(uint8_t c);
    void send(const uint8_t* buf, uint16_t len);
    uint8_t available();
    uint8_t read();
}
#endif
