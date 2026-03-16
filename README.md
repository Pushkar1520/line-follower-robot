# Line Follower Robot — Arduino Nano + 5 IR Sensors + PID Control

A high-speed PID-controlled line follower robot built with an Arduino Nano, 5-channel IR sensor board, L298N motor driver, and a 3D-printed chassis powered by 18650 Li-ion cells.

## Features

- PID control loop for smooth, accurate line tracking
- Dynamic straight-line speed boost — full 255 PWM on confirmed straights
- Inner wheel reversal on sharp turns for tight cornering
- Lost-line recovery using last known error direction
- Intersection detection via all-sensor trigger
- Tuned for thin black lines on white surface


## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Nano (ATmega328P) |
| IR Sensor Board | 5-channel, digital output (S1–S5, CLP, Near) |
| Motor Driver | L298N dual H-bridge |
| Motors | DC gear motors (x2) |
| Battery | IMR 18650 cells — 2S pack (~7.4V) |
| Buck Converter | XL4016 — steps 7.4V down to 5V for Arduino |
| Chassis | 3D printed |

---

## Pin Mapping

### IR Sensor Board → Arduino Nano

| Sensor Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| S1 (leftmost) | D2 |
| S2 | D3 |
| S3 (center) | D4 |
| S4 | D5 |
| S5 (rightmost) | D6 |

### L298N Motor Driver → Arduino Nano

| L298N Pin | Arduino Pin | Function |
|---|---|---|
| ENA | D10 (PWM) | Left motor speed |
| IN1 | D11 | Left motor direction |
| IN2 | D12 | Left motor direction |
| ENB | D9 (PWM) | Right motor speed |
| IN3 | A1 | Right motor direction |
| IN4 | A5 | Right motor direction |
| GND | GND | Common ground |

### Power Wiring

```
18650 Pack (+) ──→ Buck Converter IN+
                └→ L298N motor power pin (12V terminal)
18650 Pack (−) ──→ Buck Converter IN−, L298N GND, Arduino GND
Buck OUT+ (5V) ──→ Arduino VIN
```

---

## How PID Works Here

Each sensor is assigned a weight: S1=−2, S2=−1, S3=0, S4=+1, S5=+2.

The error is the weighted average of all active sensors. Error = 0 means perfectly centered. Negative = line is left, positive = line is right.

```
correction = (Kp × error) + (Ki × integral) + (Kd × derivative)

leftSpeed  = baseSpeed + correction
rightSpeed = baseSpeed − correction
```

When error stays below `STRAIGHT_THRESHOLD` for `BOOST_CONFIRM` consecutive loops, the robot switches to `STRAIGHT_SPEED` (255 PWM) for maximum velocity on straight sections.

---

## PID Tuning Values

| Parameter | Value | Purpose |
|---|---|---|
| Kp | 180.0 | Main correction force |
| Ki | 0.01 | Long-term drift correction |
| Kd | 100.0 | Dampens oscillation |
| BASE_SPEED | 220 | Curve following speed |
| STRAIGHT_SPEED | 255 | Straight-line boost speed |
| STRAIGHT_THRESHOLD | 0.25 | Error limit to trigger boost |
| BOOST_CONFIRM | 6 | Loops before boost activates |

### Tuning Guide

1. Set `Ki=0`, `Kd=0` — raise `Kp` until robot follows line but wobbles
2. Raise `Kd` to ~0.5×Kp to kill wobble
3. Only add `Ki` (0.001–0.01) if robot drifts consistently on straights
4. If corners are missed at high speed — lower `BASE_SPEED` by 20, not Kp

---

## Getting Started

1. Clone the repository
   ```bash
   git clone https://github.com/YOUR_USERNAME/line-follower-robot.git
   ```

2. Open `src/line_follower_pid.ino` in Arduino IDE

3. Select **Board:** Arduino Nano, **Processor:** ATmega328P (Old Bootloader) if upload fails

4. Upload and open Serial Monitor at 9600 baud to observe error values while tuning

5. Place robot on track with IR sensor board 1–1.5 cm above surface


## License

MIT License — see [LICENSE](LICENSE)
