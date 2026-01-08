# Totem Feux du Tabac
An open‑source ESP32‑based animated traffic‑light system designed for French tobacco shops (“tabacs”).  
The project controls **4 physical traffic‑light modules** (Red / Yellow / Green) using **12 PWM channels**, offering more than 20 lighting modes including K2000, rainbow, pulses, jackpot, FDJ animations, and more.

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

### 🔘 Physical Buttons
- Next Mode
- Next Sub‑Mode

---

## 📦 Hardware Requirements

- ESP32 DevKit (WROOM or S3)
- 4 × Traffic‑light modules (Red/Yellow/Green)
- 12 × PWM‑compatible GPIOs
- 2 × Buttons (optional)
- 5V power supply

Full wiring diagrams are available in `/docs/hardware_setup.md`.

---

## 🛠️ Software Requirements

- PlatformIO
- Arduino framework
- ESP32 board support
- Dependencies listed in `platformio.ini`

Setup instructions are available in `/docs/software_setup.md`.

---

## 📚 Documentation

All documentation is available in English and French under `/docs/`.

Recommended starting points:
- `/docs/architecture.md`
- `/docs/hardware_setup.md`
- `/docs/modes_reference.md`

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
/README.md
/CHANGELOG.md


---

## 📝 License

This project is licensed under the **MIT License**.  
See `LICENSE` for details.

---

## ❤️ Credits

Created by **Fred**, for his tobacco shop in France.  
Technical architecture, PWM engine, and documentation co‑designed with Copilot.
