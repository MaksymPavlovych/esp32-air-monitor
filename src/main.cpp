#include <Arduino.h>
#include "config.h"
#include "secrets.h"
#include "types.h"

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    Serial.println("ESP32 Air Monitor: скелет проєкту працює");
}

void loop() {
    delay(1000);
}
