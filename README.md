# Electrical Load Monitoring & Billing System

A simple C++ console application that allows users to monitor household electrical appliances, calculate daily energy usage, and estimate electricity bills.

This project was built step-by-step in 10 structured stages to demonstrate progressive software development using Git.

---

## Features

- Add appliances
- View appliance list
- Calculate daily energy consumption (kWh)
- Estimate daily and monthly electricity cost
- Search appliance by name
- Save and load appliance data from file
- Export billing summaries
- Delete appliances
- Edit appliance details

---

## Project Structure

The system stores data in two files:

- `appliances.txt` → Stores appliance data
- `billing_summary.txt` → Stores billing history

---

## How It Works

Each appliance has:

- Name
- Power rating (Watts)
- Usage hours per day

Daily energy usage is calculated using:

Monthly energy is calculated for 30 days.

Billing is based on a user-provided tariff per kWh.

---

## 📈 Development Stages (Git Commits)

This project was built progressively in 10 parts:

1. Basic appliance input and display system
2. Added daily energy (kWh) calculation
3. Implemented billing and cost calculation
4. Added appliance search functionality
5. Implemented file saving and loading
6. Added billing summary export
7. Implemented delete appliance feature
8. Added edit appliance feature
9. Integrated all major features
10. Final polished version with improved stability

Each stage represents one commit in the repository.

---

## 🛠 How to Compile and Run

### Using g++

```bash
g++ main.cpp -o load_monitor
./load_monitor
```
