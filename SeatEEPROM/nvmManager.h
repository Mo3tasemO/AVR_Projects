#ifndef NVM_MANAGER_H
#define NVM_MANAGER_H
#include <cstdint>
#include <cstdbool>

namespace NVM {
    void init();
    void loadStartup();
    void saveShutdownCalibration();

    void readProfile(uint8_t profile_id, uint8_t* out); /* out must be PROFILE_SIZE_BYTES */
    bool writeProfile(uint8_t profile_id, const uint8_t* data);

    uint16_t readParam(uint8_t param_id);
    bool writeParam(uint8_t param_id, uint16_t value);

    void readAll(uint8_t* out, uint32_t size);
    bool writeAll(const uint8_t* data, uint32_t size);

    void saveDiagnostic(uint16_t code);
}
#endif
