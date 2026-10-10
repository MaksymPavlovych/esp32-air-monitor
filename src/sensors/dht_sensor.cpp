#include "dht_sensor.h"
#include "config.h"
#include <DHT.h>

#define DHT_TYPE DHT11   // <-- зміни на DHT11, якщо в тебе DHT11

namespace dht_sensor {

static DHT dht(PIN_DHT, DHT_TYPE);

void begin() {
    dht.begin();
    Serial.println("DHT: ініціалізовано");
}

bool read(SensorData& d) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) return false;
    d.humidity = h;
    d.temperature = t;
    return true;
}

}  // namespace dht_sensor
