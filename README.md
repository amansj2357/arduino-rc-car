# 🚗 Bluetooth-Controlled RC Car

A 3D-printed, Arduino-based RC car controlled wirelessly over Bluetooth from a smartphone. Built from scratch in about six weeks — circuit prototyping, a custom double-layer chassis designed in Fusion 360, and motor control code tuned to fix real-world quirks like drift.

<img width="756" height="1008" alt="Car_Image" src="https://github.com/user-attachments/assets/c71ce618-76a2-42cc-bd2f-7bbd0dd501a6" />

<!-- Add a photo or short clip/GIF of the car driving here, e.g.: -->
<!-- ![RC Car](media/car-photo.jpg) -->

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware](#hardware)
- [How It Works](#how-it-works)
- [Build Timeline](#build-timeline)
- [Challenges & Solutions](#challenges--solutions)
- [Future Improvements](#future-improvements)
- [Repo Structure](#repo-structure)
- [Getting Started](#getting-started)
- [Team](#team)

## Overview
This project is a two-wheel-drive RC car controlled wirelessly via Bluetooth from a phone-based controller. It features a custom double-layer 3D-printed chassis, an Arduino-based control board, and a motor driver circuit that was tuned in software to compensate for real-world drift.

## Features
- 📱 Bluetooth control from a phone
- 🖨️ Custom double-layer 3D-printed chassis (reinforced base layer + filament-efficient, cutout-heavy top layer)
- ⚙️ Software drift correction via per-wheel speed adjustment
- 🔋 Fully portable, battery-powered

## Hardware
> Fill in the exact part names/models you used — these are placeholders based on what's visible in the build.
- Arduino (model: ___)
- Motor driver board (dual H-bridge, model: ___)
- Bluetooth module (model: ___, e.g. HC-05/HC-06)
- 2× DC gear motors + wheels
- 1× caster wheel (rear support)
- Battery pack
- 3D-printed chassis — 2 layers, joined with printed pegs, super glue, and hot glue
- Misc: jumper wires, screw terminal blocks

## How It Works
The Arduino receives movement commands over Bluetooth from a phone controller app. It converts these into PWM signals sent to the motor driver, which drives the left and right motors independently. To fix a rightward drift discovered during testing, the code applies a small speed adjustment factor to the right wheel so the car drives straight.

## Build Timeline
| When | Milestone |
|---|---|
| July | Planning — chose the microcontroller, scoped resources and project complexity |
| Early Aug | Circuit/schematic design over Discord calls |
| Aug 11 | Circuit tested — motors confirmed working; CAD modeling began |
| Aug 12 | Chassis modeled in Fusion 360 (double-layer design with connecting pegs) |
| Aug 13 | Chassis assembled, electronics mounted, Bluetooth motor control coded, tested, and debugged |

## Challenges & Solutions
**Limited time.** With a tight schedule, we scoped down to a simpler but still challenging build rather than over-planning, and iterated quickly once we had a direction. This did cause some late-stage issues, which we worked through as they came up (like the drift below).

**Chassis design tradeoff.** Balancing 3D-printing filament efficiency against structural support for all the housed components. Solved with a solid, strong base layer and a lighter, cutout-heavy top layer.

**Rightward drift.** The car pulled right when driving straight. Possible causes included an uneven floor, irregular caster wheel rotation, or uneven internal wheel rotation from the chassis weight. Since we couldn't reduce weight further without cutting components, we fixed it in software — adding a small speed correction factor to the right wheel — which resolved the drift.

## Future Improvements
- Add a front axle with two additional wheels for proper steering. Currently, steering works by rotating in place on the two rear wheels + caster wheel, which also causes the rear wheels to sag under the chassis weight.
- A front axle would solve both the steering and weight-distribution issues in one change.

## Repo Structure
```
├── code/           # Arduino sketches / firmware
├── cad/            # Fusion 360 files and STL/STEP exports for the chassis
├── media/          # Photos and videos of the build and finished car
├── docs/           # Wiring diagrams, schematics, build notes
└── README.md
```

## Getting Started
1. Clone this repo:
   ```
   git clone https://github.com/<amansj2357>/<RC-CAR-2026>.git
   ```
2. Open the sketch in `code/` using the Arduino IDE.
3. Install any required libraries (list them here — e.g. a Bluetooth serial library).
4. Wire up the hardware following the diagram in `docs/`.
5. Upload the code to your Arduino.
6. Pair your phone over Bluetooth and drive!

## Team
- Aman Jaswal
- Eliott Tenn
