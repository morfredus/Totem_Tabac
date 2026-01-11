# Totem Feux du Tabac
#
## ⚡️ NeoPixel 8x8 Matrix (0.19.0)

> Evolved since 0.12.0-dev8x8 and enriched in 0.17.0–0.19.0:
> - Dedicated full‑matrix animations (Rush, K2000, Jackpot, FDJ Winner, Maintenance)
> - Soft modes adapted to matrix (Ambiance, Wave, Rainbow, Pulse Green/Yellow/Red) using all LEDs while respecting potential mask around the three lights (columns 0/3/6)
> - OTA update with a custom professional web page and upload progress bar (`/update`)

- **Matrix addressing:** 0–63, top-to-bottom, left-to-right
- **Traffic light mapping:**
  - Red:    0 1 8 9   | 3 4 11 12   | 6 7 14 15
  - Yellow: 24 25 32 33 | 27 28 35 36 | 30 31 38 39
  - Green:  48 49 56 57 | 51 52 59 60 | 54 55 62 63
- **GPIO used:** See [include/board_config.h](include/board_config.h) (per environment)
- **Branch:** All matrix features are developed on `dev/8x8`

All documentation, changelogs, and hardware guides are synchronized per .copilot rules.

An open‑source ESP32‑based animated traffic‑light system designed for French tobacco shops (“tabacs”).  
The project controls **4 physical traffic‑light modules** (Red / Yellow / Green) using **12 PWM channels** and an **8x8 matrix**, offering 17+ lighting modes including K2000, rainbow, pulses, jackpot, FDJ animations, and more.

This repository includes:
- Full ESP32 firmware (PlatformIO)
- PWM‑based LED engine
- Mode engine with 20+ animations
- Web interface for remote control
- Physical button support
- Complete documentation (English + French)

Licensed under the **MIT License**.

---

## 🚀 Features

### 🔥 Lighting Modes (20+)
- Zen breathing
- Soft ambiance
- Wave
- Rainbow
- Rainbow Turbo
- Pulse Green / Yellow / Red (PWM fade)
- Rush
- K2000 (bidirectional)
- K2000 with light trail (Knight Rider effect)
- Disco
- Jackpot
- FDJ Winner
- Client Gagnant / Perdant
- Ouverture / Fermeture
- Pause Café
- Maintenance
- Humeur du Patron (6 colors)

### 🧠 Engine
- 12 PWM channels (4 modules × 3 colors)
- Smooth sinusoidal fading
- Bidirectional animations
- Sub‑modes (speed, direction, variations)
- Auto‑mode (opening/closing hours)

### 🌐 Web Interface
- Mode selection
- Sub‑mode selection
- Live status
- WiFi configuration
- **Display selection**: choose between classic PWM modules or 8x8 NeoPixel matrix (exclusive, persistent)
- **OTA**: dedicated update page [include/ota_page.h](include/ota_page.h) served at `/update` (glassmorphism design, progress bar, inline messages, auto‑redirect)

---

## 🟦 Display Selection (PWM or Matrix)

Since version 0.12.0-dev8x8, the firmware allows dynamic selection of the display system:

- **Classic PWM modules** (4 modules, 12 channels)
- **8x8 NeoPixel matrix** (simulates 3 traffic lights)

The choice is made via the web interface (radio button) and is **automatically saved** (persistent after reboot).

### 🟣 Soft modes adapted for matrix (0.19.0)
- Ambiance: warm base + soft green breathing, full matrix, visual accent near columns 0/3/6
- Wave: green wave across the matrix, relief near columns 0/3/6
- Rainbow: vertical scrolling bands (red→violet) across full matrix with vertical modulation
- Pulse Green/Yellow/Red: uniform breathing across full matrix with subtle spatial variation

All animation logic uses universal helpers, ensuring identical behavior regardless of display type.

See [docs/modes_reference.md](docs/modes_reference.md) for animation details and [docs/hardware_setup.md](docs/hardware_setup.md) for matrix wiring.

### 🔘 Physical Buttons
- Next Mode
- Next Sub‑Mode

---

## 📦 Hardware Requirements

- **ESP32 DevKit** (multiple boards supported):
  - UPESY WROOM (Classic ESP32)

  - ESP32-S3 DevKitC-1 N16R8 (v0.11.3+):
    - Module 0: Red 1, Yellow 2, Green 42
    - Module 1: Red 41, Yellow 40, Green 39
    - Module 2: Red 4, Yellow 5, Green 6
    - Module 3: Red 7, Yellow 15, Green 16
    - Buttons: GPIO 21 (mode), 20 (sub-mode)
  - 4 × Traffic‑light modules (Red/Yellow/Green)
  - 12 × PWM‑compatible GPIOs
  - 2 × Buttons (optional)
  - 5V power supply

Full wiring diagrams for each board are available in `/docs/hardware_setup.md`.

---

## 🛠️ Software Requirements

- PlatformIO
- Arduino framework
- ESP32 board support
- Dependencies listed in `platformio.ini`

Setup instructions are available in [docs/software_setup.md](docs/software_setup.md).

---

## 📚 Documentation

All documentation is available in English and French under `/docs/`.

Recommended starting points:
- [docs/architecture.md](docs/architecture.md)
- [docs/hardware_setup.md](docs/hardware_setup.md)
- [docs/modes_reference.md](docs/modes_reference.md)

---

## 🧩 Project Structure

/src
main.cpp
modes.cpp
light_helpers.cpp
/include
board_config.h
light_helpers.h
/docs
(full documentation)
/platformio.ini
[README.md](README.md)
[CHANGELOG.md](CHANGELOG.md)


---

## 📝 License

This project is licensed under the **MIT License**.  
See `LICENSE` for details.

---

## ❤️ Credits

Created by **Fred**, for his tobacco shop in France.  
Technical architecture, PWM engine, and documentation co‑designed with Copilot.
