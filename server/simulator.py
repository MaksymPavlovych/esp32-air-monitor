import json
import random
import time
import urllib.request

URL = "http://localhost:5000/api/data"

temp, hum, pres, co2, pm25 = 23.0, 45.0, 1013.0, 600.0, 12.0
def aqi_pm25(c):
    table = [(0, 12, 0, 50), (12.1, 35.4, 51, 100), (35.5, 55.4, 101, 150),
             (55.5, 150.4, 151, 200), (150.5, 250.4, 201, 300)]
    c = int(c * 10) / 10
    for cl, ch, il, ih in table:
        if c <= ch:
            return round((ih - il) / (ch - cl) * (c - cl) + il)
    return 300


def level(t, h, co2, pm):
    lv = 0
    if pm >= 75 or co2 >= 1500:
        lv = 2
    elif pm >= 35 or co2 >= 1000:
        lv = 1
    if not (18 <= t <= 26) or not (30 <= h <= 60):
        lv = max(lv, 1)
    return ["good", "moderate", "bad"][lv]

while True:
    temp += random.uniform(-0.2, 0.2)
    hum = min(90, max(15, hum + random.uniform(-0.5, 0.5)))
    pres += random.uniform(-0.3, 0.3)
    co2 = min(2500, max(400, co2 + random.uniform(-30, 30)))
    pm25 = min(150, max(2, pm25 + random.uniform(-2, 2)))

    payload = {
        "temperature": round(temp, 1),
        "humidity": round(hum, 1),
        "pressure": round(pres, 1),
        "co2": round(co2),
        "pm1_0": round(pm25 * 0.6, 1),
        "pm2_5": round(pm25, 1),
        "pm10": round(pm25 * 1.4, 1),
        "aqi": aqi_pm25(pm25),
        "level": level(temp, hum, co2, pm25),
    }
    req = urllib.request.Request(
        URL,
        data=json.dumps(payload).encode(),
        headers={"Content-Type": "application/json"},
    )
    try:
        urllib.request.urlopen(req, timeout=3)
        print("надіслано:", payload)
    except Exception as e:
        print("помилка:", e)
    time.sleep(2)
