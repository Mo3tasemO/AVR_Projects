#include "spi_eeprom.h"
#include <avr/io.h>
#include <util/delay.h>

namespace EEPROM {

#define EEPROM_CS_PORT PORTB
#define EEPROM_CS_DDR  DDRB
#define EEPROM_CS_PIN  PB2

#define OP_READ  0x03
#define OP_WRITE 0x02
#define OP_WREN  0x06
#define OP_RDSR  0x05

    static inline void cs_low() { EEPROM_CS_PORT &= ~(1 << EEPROM_CS_PIN); }
    static inline void cs_high() { EEPROM_CS_PORT |= (1 << EEPROM_CS_PIN); }

    static uint8_t spiXfer(uint8_t d) {
        SPDR = d;
        while (!(SPSR & (1 << SPIF)));
        return SPDR;
    }

    void init() {
        DDRB |= (1 << PB3) | (1 << PB5) | (1 << EEPROM_CS_PIN);
        DDRB &= ~(1 << PB4);
        SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
        SPSR = 0;
        cs_high();
    }

    void writeEnable() {
        cs_low();
        spiXfer(OP_WREN);
        cs_high();
        _delay_us(1);
    }

    uint8_t readStatus() {
        cs_low();
        spiXfer(OP_RDSR);
        uint8_t s = spiXfer(0xFF);
        cs_high();
        return s;
    }

    void waitWriteDone() {
        while (readStatus() & 0x01) _delay_ms(2);
    }

    void readBytes(uint32_t addr, uint8_t* buf, uint16_t len) {
        cs_low();
        spiXfer(OP_READ);
        spiXfer((addr >> 16) & 0xFF);
        spiXfer((addr >> 8) & 0xFF);
        spiXfer(addr & 0xFF);
        for (uint16_t i = 0; i < len; i++) buf[i] = spiXfer(0xFF);
        cs_high();
    }

    void writeBytes(uint32_t addr, const uint8_t* buf, uint16_t len) {
        // byte-by-byte simple implementation
        for (uint16_t i = 0; i < len; i++) {
            writeEnable();
            cs_low();
            spiXfer(OP_WRITE);
            uint32_t a = addr + i;
            spiXfer((a >> 16) & 0xFF);
            spiXfer((a >> 8) & 0xFF);
            spiXfer(a & 0xFF);
            spiXfer(buf[i]);
            cs_high();
            waitWriteDone();
        }
    }

    inline uint16_t readWord(uint32_t addr) {
        uint8_t b[2];
        readBytes(addr, b, 2);
        return (uint16_t(b[0]) << 8) | b[1];
    }

    inline void writeWord(uint32_t addr, uint16_t w) {
        uint8_t b[2] = { uint8_t(w >> 8), uint8_t(w & 0xFF) };
        writeBytes(addr, b, 2);
    }

} // namespace EEPROM
