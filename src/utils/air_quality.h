#pragma once
#include "types.h"

enum class AirLevel { GOOD, MODERATE, BAD, UNKNOWN };

int calcAqiPm25(float pm25);              // AQI за PM2.5, -1 якщо даних немає
AirLevel evaluate(const SensorData& d);   // підсумок за всіма показниками
const char* levelName(AirLevel level);
