# Sensor Simulation & Test Automation System

## Overview
This project implements an industrial-style sensor test automation system similar to those used in manufacturing validation and test environments.

Sensor readings are generated using C, validated using threshold and spike detection logic, exported to CSV, ingested into a MySQL database, and exposed through REST APIs built with Node.js and Express.

The project focuses on system logic, data flow, and backend engineering rather than UI.

---

## Architecture
C Program → CSV Report → Node.js Backend → MySQL Database → REST APIs

---

## Features
- Sensor data simulation using C  
- Threshold-based validation  
- Spike / anomaly detection  
- CSV report generation  
- REST APIs for readings, alerts, and summary  
- MySQL-backed persistence  
- Clean Git commit history  

---

## Technologies Used
- **C** – Core simulation logic  
- **Node.js + Express** – Backend APIs  
- **MySQL** – Database  
- **CSV** – Data interchange  
- **Git** – Version control  

---

## API Endpoints
- `GET /api/readings` — All sensor readings  
- `GET /api/alerts` — Failed readings only  
- `GET /api/summary` — Pass/fail statistics  

---

## How to Run

### 1. Run C Simulation
```bash
gcc sensor.c -o sensor
./sensor
This generates:
sensor_data.csv
```

##2. Start Backend Server
```
cd backend
npm install
node server.js 
```

Backend runs at:
```
http://localhost:5000
```

## Database Details

Database: sensor_db_v2

Table: sensor_readings

Data is loaded from CSV during backend startup


---

## Project Notes

node_modules is intentionally excluded from version control

Frontend visualization can be added later

Designed to resemble real-world test automation workflows

---

## Author

Joshika M
