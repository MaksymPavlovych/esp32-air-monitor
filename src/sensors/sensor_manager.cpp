#include <Arduino.h>
#include "sensor_manager.h"
#include "bmp280.h"
#include "dht_sensor.h"
#include "mq135.h"
#include "dust_sensor.h"
#include "utils/filters.h"

namespace sensor_manager {

static MovingAverage<5> co2Filter;
static MovingAverage<10> dustFilter;

void begin() {
    bmp280_sensor::begin();
    dht_sensor::begin();
    mq135_sensor::begin();
    dust_sensor::begin();
}

SensorData readAll() {
    SensorData d;
    d.timestamp = millis();

    bmp280_sensor::read(d);
    dht_sensor::read(d);

    SensorData tmp;
    if (mq135_sensor::read(tmp)) d.co2 = co2Filter.add(tmp.co2);
    if (dust_sensor::read(tmp))  d.dust = dustFilter.add(tmp.dust);

    return d;
}

}  // namespace sensor_manager
