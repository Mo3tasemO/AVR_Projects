#include "nvm_manager.h"
#include "spi_eeprom.h"
#include "protocol.h"
#include <cstring>

namespace {

    constexpr uint32_t ADDR_STARTUP = 0x0000;
    constexpr uint32_t ADDR_PROFILES = 0x0100;
    constexpr uint32_t ADDR_DIAGNOSTIC = 0x0400;
    constexpr uint32_t ADDR_CALIBRATION = 0x0800;

    constexpr uint8_t PROFILE_SLOT_SIZE = PROFILE_SIZE_BYTES;
    constexpr uint8_t PROFILE_SLOTS = 8;

} // anonymous

namespace NVM {

    void init() {
        EEPROM::init();
    }

    void loadStartup() {
        uint8_t buf[PROFILE_SIZE_BYTES];
        EEPROM::readBytes(ADDR_STARTUP, buf, PROFILE_SIZE_BYTES);
        (void)buf; // application should copy to its RAM vars
    }

    void saveShutdownCalibration() {
        uint8_t cal[CALIBRATION_SIZE] = { 0x12, 0x34 }; // replace with actual calibration
        EEPROM::writeBytes(ADDR_CALIBRATION, cal, CALIBRATION_SIZE);
    }

    void readProfile(uint8_t profile_id, uint8_t* out) {
        if (profile_id >= PROFILE_SLOTS) {
            std::memset(out, 0, PROFILE_SIZE_BYTES);
            return;
        }
        uint32_t addr = ADDR_PROFILES + uint32_t(profile_id) * PROFILE_SLOT_SIZE;
        EEPROM::readBytes(addr, out, PROFILE_SIZE_BYTES);
    }

    bool writeProfile(uint8_t profile_id, const uint8_t* data) {
        if (profile_id >= PROFILE_SLOTS) return false;
        uint32_t addr = ADDR_PROFILES + uint32_t(profile_id) * PROFILE_SLOT_SIZE;
        EEPROM::writeBytes(addr, data, PROFILE_SIZE_BYTES);
        return true;
    }

    uint16_t readParam(uint8_t param_id) {
        uint32_t addr = ADDR_STARTUP;
        switch (param_id) {
        case PARAM_HEIGHT: addr = ADDR_STARTUP + 0; break;
        case PARAM_SLIDE:  addr = ADDR_STARTUP + 2; break;
        case PARAM_INCLINE:addr = ADDR_STARTUP + 4; break;
        default: return 0;
        }
        return EEPROM::readWord(addr);
    }

    bool writeParam(uint8_t param_id, uint16_t value) {
        uint32_t addr = ADDR_STARTUP;
        switch (param_id) {
        case PARAM_HEIGHT: addr = ADDR_STARTUP + 0; break;
        case PARAM_SLIDE:  addr = ADDR_STARTUP + 2; break;
        case PARAM_INCLINE:addr = ADDR_STARTUP + 4; break;
        default: return false;
        }
        EEPROM::writeWord(addr, value);
        return true;
    }

    void readAll(uint8_t* out, uint32_t size) {
        EEPROM::readBytes(0, out, (uint16_t)size);
    }

    bool writeAll(const uint8_t* data, uint32_t size) {
        EEPROM::writeBytes(0, data, (uint16_t)size);
        return true;
    }

    void saveDiagnostic(uint16_t code) {
        EEPROM::writeWord(ADDR_DIAGNOSTIC, code);
    }

} // namespace NVM
