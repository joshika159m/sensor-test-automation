const express = require("express");
const fs = require("fs");
const csv = require("csv-parser");
const cors = require("cors");

const app = express();
app.use(cors());

const CSV_PATH = "../sensor_data.csv";

function readCSV(callback) {
  const results = [];
  fs.createReadStream(CSV_PATH)
    .pipe(csv())
    .on("data", (data) => results.push(data))
    .on("end", () => callback(results));
}

app.get("/api/readings", (req, res) => {
  readCSV((data) => res.json(data));
});

app.get("/api/alerts", (req, res) => {
  readCSV((data) => {
    const alerts = data.filter(r => r.Status === "FAIL");
    res.json(alerts);
  });
});

app.get("/api/summary", (req, res) => {
  readCSV((data) => {
    const total = data.length;
    const failed = data.filter(r => r.Status === "FAIL").length;
    res.json({
      total_readings: total,
      failures: failed,
      pass_rate: ((total - failed) / total * 100).toFixed(2) + "%"
    });
  });
});

app.listen(5000, () => {
  console.log("Backend running on http://localhost:5000");
});
