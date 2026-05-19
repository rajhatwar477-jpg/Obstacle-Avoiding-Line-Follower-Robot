# 🤖 Obstacle Avoiding Line Follower Robot
### Arduino · HC-SR04 · L298N · 2-Channel IR
 
A compact autonomous robot that follows a line on the ground — and dodges anything that gets in its way. Built around an Arduino, a couple of IR sensors, an ultrasonic ranger, and an L298N motor driver.
 
---
 
## 📸 Demo
 
> *(Drop a GIF or photo of your robot here — everyone loves a hardware demo)*
 
---
 
## ✨ What It Does
 
The robot runs two behaviours, and switches between them automatically:
 
| Mode | Trigger | Behaviour |
|------|---------|-----------|
| **Line Following** | Path is clear | Reads IR sensors and steers to stay on the line |
| **Obstacle Avoidance** | Object < 20 cm ahead | Stops → backs up → turns right → resumes |
 
No libraries required beyond stock Arduino — just upload and go.
 
---
 
## 🧰 Hardware You'll Need
 
| Component | Qty | Notes |
|-----------|-----|-------|
| Arduino Uno / Nano | 1 | Any 5 V board should work |
| L298N Motor Driver | 1 | Dual H-bridge |
| HC-SR04 Ultrasonic Sensor | 1 | Trig + Echo |
| 2-Channel IR Sensor Module | 1 | LOW = line detected |
| DC Gear Motors + Wheels | 2 | Matched pair |
| Chassis & caster | 1 | Any 2WD chassis |
| Li-Po / 18650 battery pack | 1 | 7–12 V |
| Jumper wires, standoffs | — | — |
 
---
 
## 🔌 Wiring / Pin Map
 
```
Arduino Pin  →  Connected To
──────────────────────────────
D2           →  IR Left  (signal)
D3           →  IR Right (signal)
D9           →  HC-SR04  TRIG
D10          →  HC-SR04  ECHO
D4           →  L298N    IN1
D5           →  L298N    IN2
D6           →  L298N    IN3
D7           →  L298N    IN4
D11 (PWM)    →  L298N    ENA
D12 (PWM)    →  L298N    ENB
```
 
> ⚠️ Power the L298N from your battery pack, **not** from the Arduino's 5 V pin. Share a common ground.
 
---
 
## 🚀 Getting Started
 
1. **Clone or download** this repo and open `robot.ino` in the Arduino IDE.
2. Wire everything up per the pin map above.
3. Place the robot on a dark line against a light surface (black tape on white card works great).
4. Upload the sketch and open the Serial Monitor at **9600 baud** to watch live sensor readings.
5. Power it up and watch it go.
---
 
## ⚙️ Tuning Parameters
 
All the numbers you'll want to tweak live at the top of the file — no hunting through the code:
 
```cpp
#define OBSTACLE_DIST     20    // cm — how close before swerving
#define MOTOR_SPEED      160    // 0–255 — straight-line speed
#define TURN_SPEED       130    // 0–255 — turning speed
#define AVOID_TURN_TIME  400    // ms — how long to turn when avoiding
```
 
**Quick tuning guide:**
 
- Robot overshoots turns → lower `TURN_SPEED`
- Robot ignores the line → check IR polarity; flip `LINE_DETECTED` between `HIGH` / `LOW`
- Obstacle detection too sensitive / too late → adjust `OBSTACLE_DIST`
- Avoidance turn too sharp or not enough → tweak `AVOID_TURN_TIME`
---
 
## 🧠 How It Works
 
```
Every loop:
  ┌─ Measure distance with HC-SR04
  │
  ├── Obstacle closer than OBSTACLE_DIST?
  │     YES → avoidObstacle()
  │             Stop → back up (300 ms) → turn right (AVOID_TURN_TIME) → continue
  │
  └── No obstacle → read IR sensors
        Both on line   → moveForward()
        Left on line   → turnLeft()
        Right on line  → turnRight()
        Neither        → stopMotors()  (end of line or lost)
```
 
The ultrasonic sensor fires first every loop, so obstacle avoidance always takes priority over line following.
 
---
 
## 📂 File Structure
 
```
📁 obstacle-line-follower/
 ├── robot.ino        ← Main sketch (everything is here)
 └── README.md        ← You are here
```
 
---
 
## 🐛 Troubleshooting
 
| Symptom | Likely cause | Fix |
|---------|-------------|-----|
| Robot spins in place | Motor wiring reversed on one side | Swap IN1/IN2 or IN3/IN4 |
| Robot ignores line | IR sensor polarity mismatch | Change `#define LINE_DETECTED HIGH` → `LOW` (or vice-versa) |
| No obstacle detection | Echo/Trig pins swapped | Double-check D9 = TRIG, D10 = ECHO |
| Motors don't move | ENA/ENB not PWM pins | Must use D11 and D12 on Uno |
| Erratic behaviour | Shared ground missing | Connect Arduino GND → L298N GND |
 
---
 
## 🤝 Contributing
 
Pull requests are welcome! If you add a feature (PID line following, left-turn avoidance, Bluetooth control, etc.) feel free to open a PR.
 
1. Fork the repo
2. Create a feature branch (`git checkout -b feature/pid-control`)
3. Commit your changes
4. Open a pull request
---

 
*Made with ☕ and too many jumper wires*
 
