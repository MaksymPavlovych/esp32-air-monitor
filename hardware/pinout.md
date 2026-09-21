# Таблиця підключення

| Датчик   | Пін датчика | Пін ESP32     | Живлення |
|----------|-------------|---------------|----------|
| BMP280   | VCC         | 3V3           | 3.3V     |
| BMP280   | GND         | GND           |          |
| BMP280   | SDA         | GPIO21        |          |
| BMP280   | SCL         | GPIO22        |          |
| DHT22    | VCC (+)     | 3V3           | 3.3V     |
| DHT22    | DATA (OUT)  | GPIO4         |          |
| DHT22    | GND (-)     | GND           |          |
| MQ-135   | VCC         | VIN (5V)      | 5V       |
| MQ-135   | GND         | GND           |          |
| MQ-135   | AO          | GPIO34 через дільник R1=10к / R2=20к | |
| PMS5003  | VCC         | VIN (5V)      | 5V       |
| PMS5003  | GND         | GND           |          |
| PMS5003  | TX          | GPIO16 (RX2)  |          |
| PMS5003  | RX          | GPIO17 (TX2)  |          |
| PMS5003  | SET, RESET  | не підключені |          |
