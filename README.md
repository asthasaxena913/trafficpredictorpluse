# Traffic Predictor+ — ASTRIVA.03

An Arduino-powered **physical traffic congestion demonstration** with a Flask web dashboard, RoadWatch pothole/closure reports, simulated peak-hour risk, alternative-route recommendation, and ambulance priority.

Based on the team's project presentation for Shri Krishna University, Chhatarpur. This is a rule-based educational prototype with simulated data. No verified time-saving claims are made.

## Contents
- `arduino/TrafficPredictorPlus/TrafficPredictorPlus.ino` — Arduino Uno firmware
- `web/app.py` — Python Flask server and serial bridge
- `web/templates/index.html` — dashboard
- `web/static/` — CSS and JavaScript
- `docs/WIRING.md` — connections and build notes
- `requirements.txt` — Python dependencies

## Setup
1. Install Arduino IDE and Python 3.10+.
2. Wire components as shown in `docs/WIRING.md`.
3. Open the `.ino` sketch in Arduino IDE, select **Arduino Uno** and the correct port, and upload.
4. Close Arduino Serial Monitor.
5. In a terminal in this repository:
   ```bash
   python -m pip install -r requirements.txt
   ```
6. Set your serial port if not `COM3`:
   - Windows PowerShell: `$env:ARDUINO_PORT='COM4'`
   - macOS/Linux: `export ARDUINO_PORT=/dev/ttyACM0` (replace as appropriate)
7. Start the app: `python web/app.py`
8. Visit `http://127.0.0.1:5000`.

If Arduino is disconnected, the dashboard works in **DEMO** mode with checkboxes. With Arduino connected, the hardware buttons control the status. This local server is not intended for public deployment.

## Scenario logic
- No incident: LOW risk; Route A recommended.
- Peak hour or pothole: HIGH risk; Route B recommended.
- Closure: HIGH risk; Route B recommended.
- Ambulance button: Route B priority indicator and buzzer activated.

The LED and buzzer are illustrative, not actual traffic-light controls. Future improvements: measured traffic datasets, model training, verified incident reporting, Leaflet/OpenStreetMap routing, and real ETA evaluation.

## GitHub upload
Create a new GitHub repository and upload **the contents of this folder** (not the ZIP alone) via **Add file → Upload files**, or run:
```bash
git init
git add .
git commit -m "Initial Traffic Predictor+ prototype"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/Traffic-Predictor-Plus.git
git push -u origin main
```
Replace `YOUR_USERNAME` with your account. Do not commit passwords or tokens.
