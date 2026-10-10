#pragma once
#include <stdint.h>
#include <math.h>

struct SensorData {
    float temperature = NAN;    // °C
    float humidity    = NAN;    // %
    float pressure    = NAN;    // гПа
    float co2         = NAN;    // ppm (оцінка, MQ-135)
    float dust        = NAN;    // мкг/м3 (GP2Y1010)
    unsigned long timestamp = 0;
};
