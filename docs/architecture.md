# Project Architecture — Totem Feux du Tabac

This document provides a complete overview of the internal architecture of the **Totem Feux du Tabac** project.  
It explains how the firmware is structured, how modules interact, and how the ESP32 controls the 4 traffic‑light units using PWM.

This document is intended for **beginners**, makers, and developers who want to understand or extend the system.

---

# 1. High‑Level Overview

Totem Feux du Tabac is built around **four main layers**:

+------------------------------------------------------+
|                    Web Interface                     |
+------------------------------------------------------+
|                    Mode Engine                       |
+------------------------------------------------------+
|                 Light Control Layer                  |
+------------------------------------------------------+
|                Hardware / GPIO Layer                 |
+------------------------------------------------------+

### ✔ Web Interface  
Provides remote control (mode, sub‑mode, WiFi setup).

### ✔ Mode Engine  
Contains all animations (K2000, Rainbow, Pulse, etc.).

### ✔ Light Control Layer  
Abstracts PWM control of the 12 LEDs.

### ✔ Hardware Layer  
Defines GPIO mapping and physical wiring.

---

# 2. Repository Structure

/src
main.cpp
modes.cpp
light_helpers.cpp

/include
board_config.h
light_helpers.h

/docs
(documentation files)

/platformio.ini
/README.md
/CHANGELOG.md

---

# 3. Firmware Architecture

## 3.1 main.cpp

`main.cpp` is responsible for:

- Initializing hardware
- Initializing PWM channels
- Starting WiFi manager
- Handling physical button interrupts
- Running the main loop
- Calling `updateMode()` every frame

### Responsibilities

setup():

initLights()

clearAll()

initWiFiManager()

attach button interrupts

set default mode

loop():

updateMode()

---

## 3.2 modes.cpp

This file contains **all lighting animations**.

Each mode is implemented inside a large `switch(mode)` block.

### Responsibilities

- Manage current mode
- Manage sub‑modes (speed, variations)
- Implement animation logic
- Use PWM helpers to control LEDs
- Maintain timing (`lastUpdate`, `animStep`)

### Example modes

- Zen breathing
- Pulse Red / Yellow / Green
- Rainbow
- K2000 (bidirectional)
- K2000 with light trail
- Jackpot
- FDJ Winner
- Client Gagnant / Perdant
- Opening / Closing
- Maintenance

---

## 3.3 light_helpers.cpp / .h

This layer abstracts **all LED control**.

### Responsibilities

- Initialize PWM channels
- Provide simple functions:
  - `setRed(module, value)`
  - `setYellow(module, value)`
  - `setGreen(module, value)`
  - `clearModule()`
  - `clearAll()`
- Provide RGB‑style helper:
  - `setRGB(module, r, y, g)`
- Ensure safe GPIO usage

This layer ensures that **modes never touch GPIO directly**.

---

## 3.4 board_config.h

Defines all hardware‑related constants:

- GPIO mapping for 4 modules × 3 colors
- Button pins
- PWM channel numbers
- Safety notes (boot‑sensitive pins)

### Multi-Environment Support (v0.11.0+)

Since version 0.11.0, `board_config.h` handles **multiple ESP32 boards** using conditional macros.

The appropriate GPIO mapping is automatically selected during compilation based on the `-D ENV_xxx` flag defined in `platformio.ini`.

#### File structure:

```cpp
#ifdef ENV_ESP32_DEVKIT
    // Mapping for classic ESP32 (DevKit)
    #define TL1_RED 4
    #define TL1_YELLOW 5
    // ...
#endif

#ifdef ENV_ESP32S3_N16R8
    // Mapping for ESP32-S3 DevKitC-1 N16R8 (v0.11.2+)
    #define TL1_RED 3
    #define TL1_YELLOW 4
    // ...
#endif

// Common structure
struct TrafficLightPins { int red, yellow, green; };
static const TrafficLightPins TRAFFIC_LIGHTS[4] = { ... };
```

#### Supported environments:

**1. ENV_ESP32_DEVKIT (Classic ESP32)**

- Environment: `esp32devkit`
- Proven and validated mapping
- GPIOs: 4, 5, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23
- Buttons: GPIO 25, 26


**2. ENV_ESP32S3_N16R8 (ESP32-S3 DevKitC-1) — v0.11.3+**

- Environment: `esp32s3_n16r8`
- New secure mapping (firmware 0.11.3)
- GPIOs:
  - Module 0: Red 1, Yellow 2, Green 42
  - Module 1: Red 41, Yellow 40, Green 39
  - Module 2: Red 4, Yellow 5, Green 6
  - Module 3: Red 7, Yellow 15, Green 16
- Buttons: GPIO 21 (mode), 20 (sub-mode)

Example (ESP32 DevKit):

```
TRAFFIC_LIGHTS[0].red    = GPIO 4
TRAFFIC_LIGHTS[0].yellow = GPIO 5
TRAFFIC_LIGHTS[0].green  = GPIO 12
```

Example (ESP32-S3 N16R8 v0.11.3+):

```
TRAFFIC_LIGHTS[0].red    = GPIO 1
TRAFFIC_LIGHTS[0].yellow = GPIO 2
TRAFFIC_LIGHTS[0].green  = GPIO 42
```

---

# 4. PWM Architecture

Each LED is controlled using **8‑bit PWM** (0–255).

### PWM Channels

RED_CH    = {0, 1, 2, 3}
YELLOW_CH = {4, 5, 6, 7}
GREEN_CH  = {8, 9, 10, 11}

Each module has:

- 1 red LED
- 1 yellow LED
- 1 green LED

Total: **12 PWM channels**

---

# 5. Mode Engine Architecture

Each mode follows this pattern:

if (now - lastUpdate > delayMs) {
clearAll();
// draw animation frame
lastUpdate = now;
}

### Sub‑modes

Sub‑modes allow:

- Speed variations
- Direction changes
- Color variations
- Special effects

Example:

subMode 0 = slow
subMode 1 = normal
subMode 2 = fast

---

# 6. Web Interface Architecture

The ESP32 hosts a small HTTP server.

### Routes

- `/` → main UI
- `/nextmode` → switch to next mode
- `/nextsub` → switch to next sub‑mode
- `/status` → JSON status
- `/wifi` → WiFi manager

### UI Features

- Mode selection
- Sub‑mode selection
- Live preview
- WiFi configuration

---

# 7. Physical Buttons

Two buttons are connected to GPIOs:

- Button 1 → Next Mode
- Button 2 → Next Sub‑Mode

Handled via **interrupts** for instant response.

---

# 8. Extending the Project

To add a new mode:

1. Add a new constant in `modes.h`
2. Add a new case in `updateMode()`
3. Use PWM helpers to draw frames
4. Add UI support (optional)

To add new hardware:

- Update `board_config.h`
- Update `initLights()` if needed

---

# 9. Summary

Totem Feux du Tabac is built with a clean, modular architecture:

- **main.cpp** → orchestration  
- **modes.cpp** → animations  
- **light_helpers** → PWM abstraction  
- **board_config** → hardware mapping  
- **web UI** → remote control  

This structure makes the project:

- Easy to understand  
- Easy to extend  
- Beginner‑friendly  
- Robust and maintainable  
