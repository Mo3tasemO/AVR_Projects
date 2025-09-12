#ifndef SPI_EEPROM_H
#define SPI_EEPROM_H
#include <cstdint>

namespace EEPROM {
    void init();
    void writeEnable();
    uint8_t readStatus();
    void waitWriteDone();

    void readBytes(uint32_t addr, uint8_t* buf, uint16_t len);
    void writeBytes(uint32_t addr, const uint8_t* buf, uint16_t len);

    inline uint16_t readWord(uint32_t addr);
    inline void writeWord(uint32_t addr, uint16_t w);
}
#endif
