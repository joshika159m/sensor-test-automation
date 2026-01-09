const express = require("express");
const fs = require("fs");
const csv = require("csv-parser");
const mysql = require("mysql2");
const cors = require("cors");

const app = express();
app.use(cors());

const CSV_PATH = "../sensor_data.csv";

const db = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "jammy123@",
  database: "sensor_db_v2"
});

db.connect(err => {
  if (err) {
    console.error("MySQL connection failed:", err.message);
    return;
  }
  console.log("MySQL connected");
});

// Load CSV data ONCE into DB
function loadCSVToDB() {
  fs.createReadStream(CSV_PATH)
    .pipe(csv())
    .on("data", (row) => {
      db.query(
        "INSERT INTO sensor_readings (sensor_id, temperature, status, reason) VALUES (?, ?, ?, ?)",
        [row.ID, row.Temperature, row.Status, row.Reason]
      );
    })
    .on("end", () => {
      console.log("CSV data loaded into database");
    });
}

loadCSVToDB();

// APIs now read from DB
app.get("/api/readings", (req, res) => {
  db.query("SELECT * FROM sensor_readings", (err, results) => {
    if (err) return res.status(500).json(err);
    res.json(results);
  });
});

app.get("/api/alerts", (req, res) => {
  db.query(
    "SELECT * FROM sensor_readings WHERE status='FAIL'",
    (err, results) => {
      if (err) return res.status(500).json(err);
      res.json(results);
    }
  );
});

app.get("/api/summary", (req, res) => {
  db.query(
    "SELECT COUNT(*) AS total, SUM(status='FAIL') AS failed FROM sensor_readings",
    (err, result) => {
      if (err) return res.status(500).json(err);
      const total = result[0].total;
      const failed = result[0].failed;
      res.json({
        total_readings: total,
        failures: failed,
        pass_rate: ((total - failed) / total * 100).toFixed(2) + "%"
      });
    }
  );
});

app.listen(5000, () => {
  console.log("Backend running on http://localhost:5000");
});
