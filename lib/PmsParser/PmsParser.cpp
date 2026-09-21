#include "PmsParser.h"

bool PmsParser::feed(uint8_t b, PmsFrame& out) {
    if (pos_ == 0) {
        if (b == 0x42) buf_[pos_++] = b;
        return false;
    }
    if (pos_ == 1) {
        if (b == 0x4D) {
            buf_[pos_++] = b;
        } else {
            pos_ = 0;
            if (b == 0x42) buf_[pos_++] = b;
        }
        return false;
    }

    buf_[pos_++] = b;
    if (pos_ < 32) return false;
    pos_ = 0;

    uint16_t len = (buf_[2] << 8) | buf_[3];
    if (len != 28) return false;

    uint16_t sum = 0;
    for (int i = 0; i < 30; i++) sum += buf_[i];
    uint16_t checksum = (buf_[30] << 8) | buf_[31];
    if (sum != checksum) return false;

    // Значення для атмосферних умов (байти 10-15)
    out.pm1_0 = (buf_[10] << 8) | buf_[11];
    out.pm2_5 = (buf_[12] << 8) | buf_[13];
    out.pm10  = (buf_[14] << 8) | buf_[15];
    return true;
}
