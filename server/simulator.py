import json
import random
import time
import urllib.request

URL = "http://localhost:5000/api/data"

temp, hum, pres, co2, pm25 = 23.0, 45.0, 1013.0, 600.0, 12.0

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
