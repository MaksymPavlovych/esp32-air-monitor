#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "http_client.h"
#include "secrets.h"
#include "utils/air_quality.h"

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
    addField(json, "dust",        d.dust,        0);

    int aqi = calcAqiPm25(d.dust);
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
