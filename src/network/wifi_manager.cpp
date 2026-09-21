#include <Arduino.h>
#include <WiFi.h>
#include "wifi_manager.h"
#include "secrets.h"

namespace wifi_manager {

static unsigned long lastAttempt = 0;

void begin() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Wi-Fi: підключення");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("\nWi-Fi OK, IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWi-Fi: не вдалося, спробую пізніше");
    }
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) return;
    if (millis() - lastAttempt < 10000) return;
    lastAttempt = millis();
    Serial.println("Wi-Fi: перепідключення...");
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

bool connected() { return WiFi.status() == WL_CONNECTED; }

}  // namespace wifi_manager
