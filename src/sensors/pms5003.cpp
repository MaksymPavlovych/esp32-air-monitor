#include <Arduino.h>
#include "pms5003.h"
#include "config.h"
#include "PmsParser.h"

namespace pms5003 {

static PmsParser parser;
static PmsFrame last;
static bool hasData = false;
static unsigned long lastFrameMs = 0;

void begin() {
    Serial2.begin(PMS_BAUD, SERIAL_8N1, PIN_PMS_RX, PIN_PMS_TX);
}

void update() {
    while (Serial2.available()) {
        PmsFrame f;
        if (parser.feed(Serial2.read(), f)) {
            last = f;
            hasData = true;
            lastFrameMs = millis();
        }
    }
}

bool read(SensorData& d) {
    if (!hasData || millis() - lastFrameMs > 5000) return false;
    d.pm1_0 = last.pm1_0;
    d.pm2_5 = last.pm2_5;
    d.pm10  = last.pm10;
    return true;
}

}  // namespace pms5003
