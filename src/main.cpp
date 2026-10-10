#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "secrets.h"
#include "types.h"
#include "network/wifi_manager.h"
#include "network/http_client.h"
#include "sensors/sensor_manager.h"

static unsigned long lastSend = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("\n=== ESP32 Air Monitor: старт ===");

    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

    sensor_manager::begin();
    wifi_manager::begin();
}

void loop() {
    wifi_manager::loop();

    if (millis() - lastSend >= SENSOR_INTERVAL_MS) {
        lastSend = millis();

        SensorData d = sensor_manager::readAll();

        Serial.printf(
            "T=%.1f H=%.1f P=%.1f CO2=%.0f Dust=%.0f\n",
            d.temperature, d.humidity, d.pressure, d.co2, d.dust
        );

        sendData(d);
    }
}
