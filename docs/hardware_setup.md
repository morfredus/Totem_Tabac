# Hardware Setup — Totem Feux du Tabac

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

### Example mapping (from board_config.h)

Module 0:
Red    → GPIO 13
Yellow → GPIO 26
Green  → GPIO 33

Module 1:
Red    → GPIO 14
Yellow → GPIO 27
Green  → GPIO 32

Module 2:
Red    → GPIO 16
Yellow → GPIO 17
Green  → GPIO 18

Module 3:
Red    → GPIO 19
Yellow → GPIO 21
Green  → GPIO 22

*(Your actual mapping may differ depending on your board.)*

---

# 4. Wiring Diagram (Text Version)

ESP32 GPIO 13  → Module 0 Red (+)
ESP32 GPIO 26  → Module 0 Yellow (+)
ESP32 GPIO 33  → Module 0 Green (+)

ESP32 GPIO 14  → Module 1 Red (+)
ESP32 GPIO 27  → Module 1 Yellow (+)
ESP32 GPIO 32  → Module 1 Green (+)

ESP32 GPIO 16  → Module 2 Red (+)
ESP32 GPIO 17  → Module 2 Yellow (+)
ESP32 GPIO 18  → Module 2 Green (+)

ESP32 GPIO 19  → Module 3 Red (+)
ESP32 GPIO 21  → Module 3 Yellow (+)
ESP32 GPIO 22  → Module 3 Green (+)

ALL LED (–) → GND
ESP32 GND   → Power supply GND

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
