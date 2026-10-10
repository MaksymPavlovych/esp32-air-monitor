#pragma once
#include <stdint.h>

// ============ Serial ============
constexpr unsigned long SERIAL_BAUD = 115200;

// ============ Піни ESP32 ============
// BMP280 (I2C)
constexpr uint8_t PIN_I2C_SDA = 21;
constexpr uint8_t PIN_I2C_SCL = 22;
constexpr uint8_t BMP280_I2C_ADDR = 0x76;

// DHT
constexpr uint8_t PIN_DHT = 4;

// MQ-135 (тільки піни АЦП1: GPIO32-39, бо АЦП2 не працює з Wi-Fi)
constexpr uint8_t PIN_MQ135_AO = 34;

// GP2Y1010AU0F (датчик пилу)
constexpr uint8_t PIN_DUST_LED = 25;   // імпульс підсвітки (цифровий вихід)
constexpr uint8_t PIN_DUST_AO  = 35;   // аналоговий вихід (АЦП1)

// ============ АЦП і дільник напруги MQ-135 ============
constexpr int ADC_MAX = 4095;
constexpr float ADC_VREF = 3.3f;
constexpr float DIVIDER_R1 = 10000.0f;
constexpr float DIVIDER_R2 = 20000.0f;

// ============ Інтервали (мс) ============
constexpr unsigned long SENSOR_INTERVAL_MS = 5000;

// ============ Пороги оцінки якості повітря ============
constexpr float PM25_MODERATE = 35.0f;
constexpr float PM25_BAD      = 75.0f;
constexpr float CO2_MODERATE  = 1000.0f;
constexpr float CO2_BAD       = 1500.0f;
constexpr float TEMP_MIN = 18.0f, TEMP_MAX = 26.0f;
constexpr float HUM_MIN  = 30.0f, HUM_MAX  = 60.0f;
