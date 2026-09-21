#include <unity.h>
#include "PmsParser.h"

static void makeFrame(uint8_t* f, uint16_t pm1, uint16_t pm25, uint16_t pm10) {
    for (int i = 0; i < 32; i++) f[i] = 0;
    f[0] = 0x42; f[1] = 0x4D; f[2] = 0; f[3] = 28;
    f[10] = pm1 >> 8;  f[11] = pm1 & 0xFF;
    f[12] = pm25 >> 8; f[13] = pm25 & 0xFF;
    f[14] = pm10 >> 8; f[15] = pm10 & 0xFF;
    uint16_t sum = 0;
    for (int i = 0; i < 30; i++) sum += f[i];
    f[30] = sum >> 8; f[31] = sum & 0xFF;
}

static bool feedAll(PmsParser& p, const uint8_t* d, int n, PmsFrame& out) {
    bool ok = false;
    for (int i = 0; i < n; i++) if (p.feed(d[i], out)) ok = true;
    return ok;
}

void test_valid_frame() {
    uint8_t f[32]; makeFrame(f, 10, 25, 40);
    PmsParser p; PmsFrame out;
    TEST_ASSERT_TRUE(feedAll(p, f, 32, out));
    TEST_ASSERT_EQUAL_UINT16(10, out.pm1_0);
    TEST_ASSERT_EQUAL_UINT16(25, out.pm2_5);
    TEST_ASSERT_EQUAL_UINT16(40, out.pm10);
}

void test_bad_checksum() {
    uint8_t f[32]; makeFrame(f, 10, 25, 40);
    f[31] ^= 0xFF;
    PmsParser p; PmsFrame out;
    TEST_ASSERT_FALSE(feedAll(p, f, 32, out));
}

void test_garbage_before_frame() {
    uint8_t f[32]; makeFrame(f, 5, 12, 20);
    uint8_t data[36] = {0x00, 0x42, 0x11, 0xFF};
    for (int i = 0; i < 32; i++) data[4 + i] = f[i];
    PmsParser p; PmsFrame out;
    TEST_ASSERT_TRUE(feedAll(p, data, 36, out));
    TEST_ASSERT_EQUAL_UINT16(12, out.pm2_5);
}

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_valid_frame);
    RUN_TEST(test_bad_checksum);
    RUN_TEST(test_garbage_before_frame);
    return UNITY_END();
}
