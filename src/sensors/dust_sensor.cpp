#include "dust_sensor.h"
#include "config.h"
#include <Arduino.h>

namespace dust_sensor {

void begin() {
    pinMode(PIN_DUST_LED, OUTPUT);
    digitalWrite(PIN_DUST_LED, HIGH);  // неактивний стан між вимірами
    Serial.println("GP2Y1010: ініціалізовано");
}

bool read(SensorData& d) {
    // Точний таймінг із даташиту Sharp GP2Y1010AU0F
    digitalWrite(PIN_DUST_LED, LOW);   // вмикаємо світлодіод
    delayMicroseconds(280);
    int raw = analogRead(PIN_DUST_AO); // читаємо, поки світлодіод горить
    delayMicroseconds(40);
    digitalWrite(PIN_DUST_LED, HIGH);  // вимикаємо
    delayMicroseconds(9680);           // пауза до наступного циклу

    float voltage = raw / (float)ADC_MAX * ADC_VREF;
    // Формула з даташиту: щільність пилу (мг/м3) ~ (V - 0.6) / 0.5
    float density = (voltage - 0.6f) / 0.5f;
    if (density < 0) density = 0;
    d.dust = density * 1000.0f;  // мг/м3 -> мкг/м3
    return true;
}

}  // namespace dust_sensor
