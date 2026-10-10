#include "bmp280.h"
#include "config.h"
#include <Adafruit_BMP280.h>

namespace bmp280_sensor {

static Adafruit_BMP280 bmp;
static bool ok = false;

bool begin() {
    ok = bmp.begin(BMP280_I2C_ADDR);
    if (!ok) {
        Serial.println("BMP280: не знайдено. Перевір SDA/SCL і адресу.");
        return false;
    }
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                     Adafruit_BMP280::SAMPLING_X2,
                     Adafruit_BMP280::SAMPLING_X16,
                     Adafruit_BMP280::FILTER_X16,
                     Adafruit_BMP280::STANDBY_MS_500);
    Serial.println("BMP280: OK");
    return true;
}

bool read(SensorData& d) {
    if (!ok) return false;
    d.pressure = bmp.readPressure() / 100.0f;  // Па -> гПа
    return true;
}

}  // namespace bmp280_sensor
