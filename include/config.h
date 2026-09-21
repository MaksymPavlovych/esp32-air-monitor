#pragma once
#include <stdint.h>

// ============ Serial ============
constexpr unsigned long SERIAL_BAUD = 115200;

// ============ Піни ESP32 ============
// BMP280 (I2C)
constexpr uint8_t PIN_I2C_SDA = 21;
constexpr uint8_t PIN_I2C_SCL = 22;
constexpr uint8_t BMP280_I2C_ADDR = 0x76;   // якщо сканер покаже 0x77, зміни тут

// DHT22
constexpr uint8_t PIN_DHT = 4;

// MQ-135 (тільки піни АЦП1: GPIO32-39, бо АЦП2 не працює з Wi-Fi)
constexpr uint8_t PIN_MQ135_AO = 34;

// PMS5003 (UART2)
constexpr uint8_t PIN_PMS_RX = 16;          // ESP32 RX2 <- TX датчика
constexpr uint8_t PIN_PMS_TX = 17;          // ESP32 TX2 -> RX датчика
constexpr unsigned long PMS_BAUD = 9600;

// ============ АЦП і дільник напруги MQ-135 ============
constexpr int ADC_MAX = 4095;               // 12 біт
constexpr float ADC_VREF = 3.3f;
constexpr float DIVIDER_R1 = 10000.0f;      // Ом
constexpr float DIVIDER_R2 = 20000.0f;      // Ом

// ============ Інтервали (мс) ============
constexpr unsigned long SENSOR_INTERVAL_MS = 5000;      // опитування датчиків

// ============ Пороги оцінки якості повітря ============
constexpr float PM25_MODERATE = 35.0f;      // мкг/м3
constexpr float PM25_BAD      = 75.0f;
constexpr float CO2_MODERATE  = 1000.0f;    // ppm (оцінка за MQ-135)
constexpr float CO2_BAD       = 1500.0f;
constexpr float TEMP_MIN = 18.0f, TEMP_MAX = 26.0f;     // °C
constexpr float HUM_MIN  = 30.0f, HUM_MAX  = 60.0f;     // %
