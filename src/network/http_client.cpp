#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "http_client.h"
#include "secrets.h"
#include "utils/air_quality.h"

// Додає "ключ":значення в JSON. NAN пропускається.
static void addField(String& s, const char* key, float v, int decimals) {
    if (isnan(v)) return;
    if (s.length() > 1) s += ',';
    s += '"'; s += key; s += "\":"; s += String(v, decimals);
}

bool sendData(const SensorData& d) {
    if (WiFi.status() != WL_CONNECTED) return false;

    String json = "{";
    addField(json, "temperature", d.temperature, 1);
    addField(json, "humidity",    d.humidity,    1);
    addField(json, "pressure",    d.pressure,    1);
    addField(json, "co2",         d.co2,         0);
    addField(json, "pm1_0",       d.pm1_0,       0);
    addField(json, "pm2_5",       d.pm2_5,       0);
    addField(json, "pm10",        d.pm10,        0);

    int aqi = calcAqiPm25(d.pm2_5);
    if (aqi >= 0) addField(json, "aqi", (float)aqi, 0);

    if (json.length() > 1) json += ',';
    json += "\"level\":\"";
    json += levelName(evaluate(d));
    json += "\"}";

    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(3000);
    int code = http.POST(json);
    http.end();

    Serial.printf("POST -> %d\n", code);
    return code == 201;
}
