#pragma once
#include "types.h"

namespace dht_sensor {
    void begin();
    bool read(SensorData& d);
}
