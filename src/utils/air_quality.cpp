#include "air_quality.h"
#include "config.h"
#include <math.h>

struct Breakpoint { float cLow, cHigh; int iLow, iHigh; };

static const Breakpoint PM25_TABLE[] = {
    {0.0f,   12.0f,    0,  50},
    {12.1f,  35.4f,   51, 100},
    {35.5f,  55.4f,  101, 150},
    {55.5f,  150.4f, 151, 200},
    {150.5f, 250.4f, 201, 300},
    {250.5f, 350.4f, 301, 400},
    {350.5f, 500.4f, 401, 500},
};

int calcAqiPm25(float dust) {
    if (isnan(dust) || dust < 0) return -1;
    dust = floorf(dust * 10.0f) / 10.0f;
    for (const auto& bp : PM25_TABLE) {
        if (dust <= bp.cHigh) {
            float aqi = (float)(bp.iHigh - bp.iLow) / (bp.cHigh - bp.cLow)
                        * (dust - bp.cLow) + bp.iLow;
            return (int)roundf(aqi);
        }
    }
    return 500;
}

static void raise(int& level, int v) { if (v > level) level = v; }

AirLevel evaluate(const SensorData& d) {
    bool any = false;
    int level = 0;

    if (!isnan(d.dust)) {
        any = true;
        if (d.dust >= PM25_BAD) raise(level, 2);
        else if (d.dust >= PM25_MODERATE) raise(level, 1);
    }
    if (!isnan(d.co2)) {
        any = true;
        if (d.co2 >= CO2_BAD) raise(level, 2);
        else if (d.co2 >= CO2_MODERATE) raise(level, 1);
    }
    if (!isnan(d.temperature)) {
        any = true;
        if (d.temperature < TEMP_MIN || d.temperature > TEMP_MAX) raise(level, 1);
    }
    if (!isnan(d.humidity)) {
        any = true;
        if (d.humidity < HUM_MIN || d.humidity > HUM_MAX) raise(level, 1);
    }

    if (!any) return AirLevel::UNKNOWN;
    return level == 0 ? AirLevel::GOOD : (level == 1 ? AirLevel::MODERATE : AirLevel::BAD);
}

const char* levelName(AirLevel level) {
    switch (level) {
        case AirLevel::GOOD:     return "good";
        case AirLevel::MODERATE: return "moderate";
        case AirLevel::BAD:      return "bad";
        default:                 return "unknown";
    }
}
