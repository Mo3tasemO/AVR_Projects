#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "spi_eeprom.h"
#include "nvm_manager.h"
#include "protocol.h"

// protocolPoll declaration (defined in protocol.cpp)
extern void protocolPoll();

static volatile bool shutdown_requested = false;

int main() {
    UART::init(115200);
    NVM::init();
    _delay_ms(10);

    // Load startup data
    NVM::loadStartup();

    while (1) {
        protocolPoll();

        // Example runtime diagnostics hook - placeholder
        // if (some_error) NVM::saveDiagnostic(errorCode);

        if (shutdown_requested) {
            NVM::saveShutdownCalibration();
            shutdown_requested = false;
        }

        _delay_ms(5);
    }
    return 0;
}
