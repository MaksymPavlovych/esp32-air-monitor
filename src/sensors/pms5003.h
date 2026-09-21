#pragma once
#include "types.h"

namespace pms5003 {
    void begin();
    void update();                 // викликати в loop() якомога частіше
    bool read(SensorData& d);      // true, якщо є свіжі дані (не старші 5 с)
}
