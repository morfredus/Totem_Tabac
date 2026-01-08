# Changelog — Totem Feux du Tabac
All notable changes to this project are documented in this file.

This project follows **Semantic Versioning (SemVer)**:  
**MAJOR.MINOR.PATCH**

---

## [0.8.0] – K2000 Trail Effect (2026-01-08)
### Added
- New **K2000 “light trail” effect** with PWM fading behind the main point.
- Smooth bidirectional sweep (0→3→0) with configurable speeds.
- Fully PWM‑based implementation for realistic Knight Rider animation.

### Changed
- Reworked K2000 mode to use direction logic instead of looping reset.

---

## [0.7.0] – K2000 Bidirectional Sweep (2026-01-08)
### Added
- True **left‑to‑right and right‑to‑left** K2000 sweep.
- Speed control via sub‑modes (slow / normal / fast).

---

## [0.6.0] – Full PWM Rewrite (2026-01-08)
### Added
- Complete rewrite of `light_helpers.h` and `.cpp`.
- 12 independent PWM channels (4 modules × 3 colors).
- New functions:
  - `setRed(module, value)`
  - `setYellow(module, value)`
  - `setGreen(module, value)`
  - `setRGB(module, r, y, g)`
  - `clearModule()`, `clearAll()`
  - `initTrafficLightPWM()`

### Removed
- Deprecated boolean versions of `setRed()` and `setYellow()`.

---

## [0.5.0] – Pulse Modes Overhaul (2026-01-08)
### Added
- True PWM fading for:
  - **Pulse Red**
  - **Pulse Yellow**
  - **Pulse Green**

### Fixed
- Removed fake yellow/red pulses based on green PWM.
- Unified sinusoidal fade engine.

---

## [0.4.0] – GPIO Mapping Overhaul (2026-01-08)
### Added
- New safe PWM‑compatible GPIO mapping for ESP32 DevKit.
- 12 GPIOs assigned for 4 traffic lights (R/Y/G).
- 2 GPIOs assigned for physical buttons.

---

## [0.3.0] – Web Interface Buttons (2026-01-08)
### Added
- Two new web UI buttons:
  - **Next Mode**
  - **Next Sub‑Mode**
- Added HTTP routes `/nextmode` and `/nextsub`.

---

## [0.2.0] – Mode System Expansion (2026-01-08)
### Added
- Full mode engine with:
  - Zen
  - Ambiance Douce
  - Vague
  - Arc‑en‑Ciel
  - Pulse Vert / Jaune / Rouge
  - Rush
  - K2000
  - Disco
  - Jackpot
  - FDJ Winner
  - Client Gagnant
  - Client Perdant
  - Ouverture / Fermeture
  - Pause Café
  - Maintenance
  - Arc‑en‑Ciel Turbo
  - Humeur du Patron

---

## [0.1.0] – Initial Light Control Logic (2026-01-08)
### Added
- Basic LED control functions.
- First version of `modes.cpp`.
- First version of web interface.

---

## [0.0.0] – Project Start (2026-01-08)
### Added
- Project initialization.
- First discussion and architecture planning.
