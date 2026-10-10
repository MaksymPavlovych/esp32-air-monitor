#pragma once
#include "types.h"

enum class AirLevel { GOOD, MODERATE, BAD, UNKNOWN };

int calcAqiPm25(float dust);
AirLevel evaluate(const SensorData& d);
const char* levelName(AirLevel level);
