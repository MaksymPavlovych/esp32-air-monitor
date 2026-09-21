import sqlite3
from pathlib import Path

DB_PATH = Path(__file__).parent / "data.db"
FIELDS = ["temperature", "humidity", "pressure", "co2", "pm1_0", "pm2_5", "pm10", "aqi"]
TEXT_FIELDS = ["level"]
COLUMNS = FIELDS + TEXT_FIELDS


def get_conn():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


def init_db():
    conn = get_conn()
    conn.execute("""
        CREATE TABLE IF NOT EXISTS measurements (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ts TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
            temperature REAL, humidity REAL, pressure REAL, co2 REAL,
            pm1_0 REAL, pm2_5 REAL, pm10 REAL, aqi REAL, level TEXT
        )
    """)
    conn.commit()
    conn.close()


def insert(data):
    values = []
    for f in FIELDS:
        v = data.get(f)
        values.append(float(v) if isinstance(v, (int, float)) else None)
    for f in TEXT_FIELDS:
        v = data.get(f)
        values.append(v if isinstance(v, str) else None)
    conn = get_conn()
    conn.execute(
        f"INSERT INTO measurements ({','.join(COLUMNS)}) VALUES ({','.join('?' * len(COLUMNS))})",
        values,
    )
    conn.commit()
    conn.close()


def latest():
    conn = get_conn()
    row = conn.execute("SELECT * FROM measurements ORDER BY id DESC LIMIT 1").fetchone()
    conn.close()
    return dict(row) if row else {}


def history(limit=200):
    conn = get_conn()
    rows = conn.execute(
        "SELECT * FROM measurements ORDER BY id DESC LIMIT ?", (limit,)
    ).fetchall()
    conn.close()
    return [dict(r) for r in reversed(rows)]


def all_rows():
    conn = get_conn()
    rows = conn.execute("SELECT * FROM measurements ORDER BY id").fetchall()
    conn.close()
    return [dict(r) for r in rows]
