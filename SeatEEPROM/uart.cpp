#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <cstdint>

namespace UART {

    static constexpr uint16_t RX_BUF_SIZE = 128;
    static volatile uint8_t rx_buf[RX_BUF_SIZE];
    static volatile uint16_t rx_head = 0;
    static volatile uint16_t rx_tail = 0;

    void init(uint32_t baud) {
        // Calculate UBRR for asynchronous normal mode
        uint32_t ubrr = (F_CPU / 16UL / baud) - 1UL;
        UBRR0H = (uint8_t)(ubrr >> 8);
        UBRR0L = (uint8_t)(ubrr & 0xFF);
        UCSR0A = 0;
        UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
        rx_head = rx_tail = 0;
        sei();
    }

    void putChar(uint8_t c) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = c;
    }

    void send(const uint8_t* buf, uint16_t len) {
        for (uint16_t i = 0; i < len; i++) putChar(buf[i]);
    }

    uint8_t available() {
        return (uint8_t)((RX_BUF_SIZE + rx_head - rx_tail) % RX_BUF_SIZE);
    }

    uint8_t read() {
        if (rx_head == rx_tail) return 0;
        uint8_t v = rx_buf[rx_tail++];
        rx_tail %= RX_BUF_SIZE;
        return v;
    }

} // namespace UART

// RX ISR: push received byte to circular buffer
ISR(USART_RX_vect) {
    uint8_t c = UDR0;
    uint16_t next = (UART::rx_head + 1) % UART::RX_BUF_SIZE;
    if (next != UART::rx_tail) {
        UART::rx_buf[UART::rx_head] = c;
        UART::rx_head = next;
    }
}
