#include <Arduino.h>
#include "config.h"
#include "secrets.h"
#include "types.h"
#include "network/wifi_manager.h"
#include "network/http_client.h"

static unsigned long lastSend = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("ESP32 Air Monitor: тест відправки");
    wifi_manager::begin();
}

void loop() {
    wifi_manager::loop();

    if (millis() - lastSend >= SENSOR_INTERVAL_MS) {
        lastSend = millis();
        SensorData d;
        d.temperature = 23.5f;
        d.humidity    = 45.0f;
        d.pressure    = 1013.2f;
        d.co2         = 650;
        d.pm1_0 = 5; d.pm2_5 = 12; d.pm10 = 20;
        sendData(d);
    }
}
