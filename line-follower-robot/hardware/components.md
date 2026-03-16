# Bill of Materials

| # | Component | Specification | Qty | Approx.|
|---|---|---|---|---|
| 1 | Arduino Nano | ATmega328P, 5V logic | 1 | 
| 2 | IR Sensor Board | 5-channel, S1–S5 + CLP + Near | 1 | 
| 3 | L298N Motor Driver | Dual H-bridge, up to 35V/2A | 1 |
| 4 | DC Gear Motor | 3–12V, with wheel | 2 |
| 5 | 18650 Li-ion Cell | IMR 2000mAh 3.7V | 2 |
| 6 | 18650 Battery Holder | 2S series configuration | 1 |
| 7 | XL4016 Buck Converter | IN: up to 35V, OUT: adjustable | 1 |
| 8 | 3D Printed Chassis | Custom — STL files in hardware/ | 1 | Cost of filament |
| 9 | Jumper Wires | Male-female, male-male | 
| 10 | Micro USB Cable | For Arduino programming | 1 |

## Tools Required

- Soldering iron + solder
- Multimeter (essential for setting buck converter to 5V before connecting Arduino)
- Arduino IDE (free)
- 3D printer or access to one for chassis

## Notes

- Set buck converter output to exactly 5V using a multimeter BEFORE connecting to Arduino VIN
- Check motor rated voltage before increasing battery voltage beyond 7.4V
- L298N has ~1.5–2V internal drop — motors receive less than battery voltage at PWM 255
