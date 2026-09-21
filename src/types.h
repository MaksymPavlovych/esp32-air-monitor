#pragma once
#include <stdint.h>
#include <math.h>

// Єдиний формат даних, який ходить між усіма модулями.
// NAN означає "значення не отримано" (датчик відсутній або помилка читання).
struct SensorData {
    float temperature = NAN;    // °C
    float humidity    = NAN;    // %
    float pressure    = NAN;    // гПа
    float co2         = NAN;    // ppm (оцінка)
    float pm1_0       = NAN;    // мкг/м3
    float pm2_5       = NAN;    // мкг/м3
    float pm10        = NAN;    // мкг/м3
    unsigned long timestamp = 0; // millis() у момент вимірювання
};
