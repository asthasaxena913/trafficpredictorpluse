# Wiring and physical build

## Arduino Uno pin mapping
| Part | Pin |
|---|---|
| Route A red LED | D2 |
| Route A yellow LED | D3 |
| Route A green LED | D4 |
| Route B red LED | D5 |
| Route B yellow LED | D6 |
| Route B green LED | D7 |
| Ambulance indicator LED | D8 |
| Passive buzzer (+), optional | D9 |
| Pothole button | D10 |
| Closure button | D11 |
| Ambulance button | D12 |
| Peak hour button | D13 |
| Reset button | A0 |

Every LED must have its own 220–330 ohm resistor in series. Connect the Arduino pin -> resistor -> LED anode (+); LED cathode (-) -> Arduino GND. Buttons connect between their input pin and GND (firmware uses INPUT_PULLUP). Optional low-current passive buzzer connects D9 (+) and GND (-); for higher-current buzzers, use a transistor driver. All circuits use Arduino USB low-voltage power. Disconnect power while wiring. Do not attach real traffic signal equipment.

## Physical model
- Base: 60 x 90 cm foam board or sunboard.
- Two roads between the same start and destination: congested Route A (main road) and alternate Route B (ring road).
- Buildings: school, college, market, office. Add toy cars and ambulance.
- Mark a pothole and road-closure barricade near Route A.
- Place LED indicators beside each route, and the five labelled buttons near the front.
- Connect Arduino by USB to laptop and show the dashboard.

## Suggested parts and approximate INR budget
- Arduino Uno-compatible: ₹400–700
- Breadboard, jumper wires, LEDs, resistors, buttons, buzzer and USB cable: ₹400–800
- Foam board, paper, glue, markers, printed labels: ₹400–900
- Toy cars, ambulance, buildings and trees: ₹300–800
- **Estimated total: ₹1,500–3,200**, excluding laptop and shipping. These are estimates, not live quotes.

## Testing
1. Power via USB; verify both routes green in normal mode.
2. Press peak-hour: Route A red and Route B green; dashboard HIGH.
3. Press pothole/closure: dashboard updates report fields.
4. Press ambulance: priority LED and buzzer activate; dashboard emergency status.
5. Press reset: clear events.

## Limitations
This is a simulated rule-based prototype. It does not use real-time road speed, GPS, camera feeds, a trained AI predictor, or verified ambulance routing. The green Route B LED represents a suggested path, not a guarantee that a road is clear.
