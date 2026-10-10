#pragma once
#include "types.h"

namespace dust_sensor {
    void begin();
    bool read(SensorData& d);   // блокує приблизно на 0.6 мс, це нормально
}
