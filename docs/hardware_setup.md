# Hardware Setup — Totem Feux du Tabac
#
## 🟦 8x8 NeoPixel Matrix (dev/8x8)

> **New in 0.12.0-dev8x8**: The project supports an 8x8 NeoPixel matrix for advanced traffic light simulation and animations.

- **Addressing:** 0–63, top-to-bottom, left-to-right
- **Traffic light mapping:**
  - Red:    0 1 8 9   | 3 4 11 12   | 6 7 14 15
  - Yellow: 24 25 32 33 | 27 28 35 36 | 30 31 38 39
  - Green:  48 49 56 57 | 51 52 59 60 | 54 55 62 63
- **GPIO used:** See `board_config.h` (per environment)
- **Branch:** All matrix features are developed on `dev/8x8`

See README and changelog for full details. All documentation is synchronized per .copilot rules.


This guide explains how to wire and assemble the hardware for the **Totem Feux du Tabac** project.  
It is written for beginners and assumes no prior electronics experience.

---

# 1. Required Components

## Mandatory
- **1 × ESP32 DevKit** (WROOM or S3)
- **4 × Traffic‑light modules** (Red / Yellow / Green LEDs)
- **12 × PWM‑compatible GPIO pins**
- **1 × 5V power supply** (2A recommended)
- **Jumper wires**
- **Breadboard or terminal blocks**

## Optional
- **2 × Push buttons** (Mode / Sub‑mode)
- **Resistors** (10kΩ for pull‑ups if needed)
- **3D‑printed enclosure**
- **DIN‑rail mount**

---

# 2. Understanding the Traffic‑Light Modules

Each module contains:

- 1 × Red LED  
- 1 × Yellow LED  
- 1 × Green LED  

Each LED has:

- **1 anode (positive)**
- **1 cathode (negative)**

The ESP32 controls each LED using **PWM** (0–255 brightness).

---

# 3. GPIO Mapping

The project uses **12 GPIOs** for the 4 modules.

Module 0 → Red / Yellow / Green
Module 1 → Red / Yellow / Green
Module 2 → Red / Yellow / Green
Module 3 → Red / Yellow / Green

## 3.1 Multi-Environment Support (v0.11.0+)

Since version 0.11.0, the project supports **two ESP32 boards** with different GPIO mappings.

The mapping is automatically selected during compilation based on the chosen PlatformIO environment.

### Mapping A: ESP32 DevKit (Classic ESP32)

**PlatformIO Environment:** `esp32devkit`  
**Board:** esp32doit-devkit1

```
Module 0:
  Red    → GPIO 4
  Yellow → GPIO 5
  Green  → GPIO 12

Module 1:
  Red    → GPIO 13
  Yellow → GPIO 14
  Green  → GPIO 16

Module 2:
  Red    → GPIO 17
  Yellow → GPIO 18
  Green  → GPIO 19

Module 3:
  Red    → GPIO 21
  Yellow → GPIO 22
  Green  → GPIO 23

Buttons:
  Mode    → GPIO 25
  Submode → GPIO 26
```


### Mapping B: ESP32-S3 DevKitC-1 N16R8 (v0.11.3+)

**PlatformIO Environment:** `esp32s3_n16r8`  
**Board:** esp32-s3-devkitc-1

⚠️ **Update 0.11.3**: New GPIO mapping as in `board_config.h`:

```
Module 0:
  Red    → GPIO 1
  Yellow → GPIO 2
  Green  → GPIO 42

Module 1:
  Red    → GPIO 41
  Yellow → GPIO 40
  Green  → GPIO 39

Module 2:
  Red    → GPIO 4
  Yellow → GPIO 5
  Green  → GPIO 6

Module 3:
  Red    → GPIO 7
  Yellow → GPIO 15
  Green  → GPIO 16

Buttons:
  Mode    → GPIO 21
  Submode → GPIO 20
```

**Note:** This mapping avoids dangerous GPIOs:
- ✗ GPIO 0, 1, 2: Boot/UART0
- ✗ GPIO 45, 46: Strapping pins
- ✗ GPIO 26-32: Input-only
- ✓ GPIO 3-16: 100% PWM safe

---


# 4.1. Using the 8x8 NeoPixel Matrix (optional)

Since version 0.12.0-dev8x8, you can use an 8x8 NeoPixel matrix *instead of* the classic PWM modules (never both at once).

## Matrix Wiring

- **VCC** (matrix) → 5V power supply
- **GND** (matrix) → common GND
- **DIN** (matrix) → GPIO defined in `board_config.h` (`NEOPIXEL_MATRIX_PIN`)

> ⚠️ **Important:** Display selection (PWM modules or matrix) is done via the web interface (radio button) and is automatically saved. Only one system is active at a time.

## Traffic light mapping on the matrix

The matrix simulates 3 traffic lights:

- **Light 1**: columns 0–1 (top = red, center = yellow, bottom = green)
- **Light 2**: columns 3–4
- **Light 3**: columns 6–7

See `/docs/modes_reference.md` for animation details and `/README.md` for display selection instructions.

# 4. Wiring Diagram (Text Version)

Use the diagram corresponding to your ESP32 board (see section 3 for mappings).

### For ESP32 DevKit (esp32devkit):

```
ESP32 GPIO 4   → Module 0 Red (+)
ESP32 GPIO 5   → Module 0 Yellow (+)
ESP32 GPIO 12  → Module 0 Green (+)

ESP32 GPIO 13  → Module 1 Red (+)
ESP32 GPIO 14  → Module 1 Yellow (+)
ESP32 GPIO 16  → Module 1 Green (+)

ESP32 GPIO 17  → Module 2 Red (+)
ESP32 GPIO 18  → Module 2 Yellow (+)
ESP32 GPIO 19  → Module 2 Green (+)

ESP32 GPIO 21  → Module 3 Red (+)
ESP32 GPIO 22  → Module 3 Yellow (+)
ESP32 GPIO 23  → Module 3 Green (+)

ESP32 GPIO 25  → Mode Button
ESP32 GPIO 26  → Submode Button

ALL CATHODES (–) → GND
ESP32 GND        → Power supply GND
```


### For ESP32-S3 DevKitC-1 N16R8 (esp32s3_n16r8) — v0.11.3+:

```
ESP32 GPIO 1   → Module 0 Red (+)
ESP32 GPIO 2   → Module 0 Yellow (+)
ESP32 GPIO 42  → Module 0 Green (+)

ESP32 GPIO 41  → Module 1 Red (+)
ESP32 GPIO 40  → Module 1 Yellow (+)
ESP32 GPIO 39  → Module 1 Green (+)

ESP32 GPIO 4   → Module 2 Red (+)
ESP32 GPIO 5   → Module 2 Yellow (+)
ESP32 GPIO 6   → Module 2 Green (+)

ESP32 GPIO 7   → Module 3 Red (+)
ESP32 GPIO 15  → Module 3 Yellow (+)
ESP32 GPIO 16  → Module 3 Green (+)

ESP32 GPIO 21  → Mode Button
ESP32 GPIO 20  → Submode Button

ALL CATHODES (–) → GND
ESP32 GND        → Power supply GND
```

---

# 5. Powering the System

### Option A — Power from USB  
Good for testing.

### Option B — External 5V Power Supply  
Recommended for real installation.

**Important:**  
All grounds must be connected together:

ESP32 GND ↔ LED GND ↔ Power Supply GND

---

# 6. Button Wiring

Two buttons are used:

- **Button 1 → Next Mode**
- **Button 2 → Next Sub‑Mode**

### Wiring

Button → GPIO (e.g., 0 or 35)
Button → GND

The ESP32 internal pull‑ups are used.

---

# 7. Safety Notes

- Avoid GPIOs 34–39 for PWM (input‑only).
- Avoid GPIOs 0, 2, 15 during boot unless you know what you're doing.
- Always connect grounds together.
- Do not power LEDs directly from ESP32 3.3V pin.
- Use a proper 5V supply for long‑term installation.

---

# 8. Troubleshooting

### LED always ON  
→ Wrong wiring (inverted polarity)

### LED flickers  
→ Missing common ground

### ESP32 resets randomly  
→ Power supply too weak

### PWM not working  
→ GPIO not PWM‑capable

---

# 9. Summary

You now have:

- ESP32 wired to 4 traffic‑light modules  
- 12 PWM channels connected  
- Optional buttons installed  
- Safe and stable power supply  

Your hardware is ready for the firmware.
