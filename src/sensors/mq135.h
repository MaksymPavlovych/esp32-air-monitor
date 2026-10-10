#pragma once
#include "types.h"

namespace mq135_sensor {
    void begin();
    bool read(SensorData& d);
}
