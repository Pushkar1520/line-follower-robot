# Wiring Reference

## Power Circuit

```
[18650 2S Pack ~7.4V]
        |
        +──────────────────────→ L298N  (12V motor power terminal)
        |
        +──→ [XL4016 Buck Converter IN+]
        |            |
        |       OUT+ (5V) ──→ Arduino Nano VIN
        |
        └──────────────────────→ L298N GND
                               → Arduino GND
                               → Buck Converter IN−
                               → IR Sensor Board GND
```

## IR Sensor Board → Arduino Nano

```
IR Board          Arduino Nano
VCC       ──────→ 5V
GND       ──────→ GND
S1        ──────→ D2
S2        ──────→ D3
S3        ──────→ D4
S4        ──────→ D5
S5        ──────→ D6
```

## L298N → Arduino Nano

```
L298N             Arduino Nano
ENA       ──────→ D10  (PWM — left motor speed)
IN1       ──────→ D11  (left motor direction)
IN2       ──────→ D12  (left motor direction)
ENB       ──────→ D9   (PWM — right motor speed)
IN3       ──────→ A1   (right motor direction)
IN4       ──────→ A5   (right motor direction)
GND       ──────→ GND
```

## L298N → Motors

```
L298N             Motors
OUT1+OUT2 ──────→ Left DC gear motor
OUT3+OUT4 ──────→ Right DC gear motor
```

## Notes

- IR sensor board height above ground: 1–1.5 cm
- If robot turns wrong direction: swap IN1↔IN2 or IN3↔IN4 for that motor
- CLP pin on IR board: pull LOW briefly over white surface to recalibrate sensors
- Near pin: proximity output — can connect to D13 for obstacle detection (unused in this build)
