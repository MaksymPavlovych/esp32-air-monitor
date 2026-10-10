#pragma once
#include "types.h"

namespace bmp280_sensor {
    bool begin();                  // true, якщо датчик знайдено
    bool read(SensorData& d);      // true, якщо вдалося прочитати
}
