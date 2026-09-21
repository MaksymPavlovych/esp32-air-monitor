import csv
import io

from flask import Flask, Response, jsonify, render_template, request

from database import FIELDS, all_rows, history, init_db, insert, latest

app = Flask(__name__)
init_db()


@app.post("/api/data")
def receive():
    data = request.get_json(silent=True)
    if not isinstance(data, dict):
        return jsonify(error="invalid json"), 400
    insert(data)
    return jsonify(ok=True), 201


@app.get("/api/latest")
def api_latest():
    return jsonify(latest())


@app.get("/api/history")
def api_history():
    limit = request.args.get("limit", 200, type=int)
    return jsonify(history(limit))


@app.get("/export.csv")
def export_csv():
    buf = io.StringIO()
    writer = csv.writer(buf)
    writer.writerow(["ts"] + FIELDS)
    for r in all_rows():
        writer.writerow([r["ts"]] + [r[f] for f in FIELDS])
    return Response(
        buf.getvalue(),
        mimetype="text/csv",
        headers={"Content-Disposition": "attachment; filename=measurements_raw.csv"},
    )


@app.get("/")
def index():
    return render_template("index.html")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
