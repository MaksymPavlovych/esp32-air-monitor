#include "mq135.h"
#include "config.h"
#include <Arduino.h>

namespace mq135_sensor {

void begin() {
    pinMode(PIN_MQ135_AO, INPUT);
    Serial.println("MQ-135: ініціалізовано (потребує 24-48 год прогріву)");
}

bool read(SensorData& d) {
    int raw = analogRead(PIN_MQ135_AO);
    // Напруга на вході ESP32 (після дільника)
    float vAdc = raw / (float)ADC_MAX * ADC_VREF;
    // Відновлена напруга на самому виході датчика (до дільника)
    float vSensor = vAdc * (DIVIDER_R1 + DIVIDER_R2) / DIVIDER_R2;
    // Спрощена оцінка ppm CO2. Для курсової зазнач, що це
    // орієнтовна лінійна оцінка, а не точна газоаналітична калібровка.
    float ppm = 400.0f + (vSensor / 3.3f) * 2000.0f;
    d.co2 = ppm;
    return true;
}

}  // namespace mq135_sensor
