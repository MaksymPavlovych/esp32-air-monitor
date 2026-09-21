#pragma once
#include <stdint.h>

struct PmsFrame {
    uint16_t pm1_0 = 0;
    uint16_t pm2_5 = 0;
    uint16_t pm10  = 0;
};

// Автомат розбору потоку байтів PMS5003. Кадр: 32 байти, початок 0x42 0x4D.
class PmsParser {
public:
    // Подай черговий байт. Повертає true, коли зібрано валідний кадр (він в out).
    bool feed(uint8_t b, PmsFrame& out);
private:
    uint8_t buf_[32];
    uint8_t pos_ = 0;
};
