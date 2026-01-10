# Changelog — Totem Feux du Tabac
All notable changes to this project are documented in this file.

This project follows **Semantic Versioning (SemVer)**:  
**MAJOR.MINOR.PATCH**

---

## [0.12.0] – NeoPixel Support & Unified Manager (2026-01-10)
### Added
- 🎆 **NeoPixel module support**: Alternative to traditional PWM traffic lights
  - **Single GPIO control**: 1 pin controls all 12 LEDs (4 modules × 3 LEDs) via addressable strip
  - Direct integration via Adafruit_NeoPixel library
  - Yellow rendered as RGB mix (R:100%, G:70%) for natural appearance
- **Unified Traffic Light Manager**: `TrafficLightManager` class
  - Single interface for both PWM and NeoPixel systems
  - Automatic system selection via compile-time flag `USE_NEOPIXEL_LIGHTS`
  - Zero code changes required to switch between systems
  - LED addressing: Module 0 (LEDs 0-2), Module 1 (LEDs 3-5), Module 2 (LEDs 6-8), Module 3 (LEDs 9-11)
- **Pin configuration in board_config.h**: Single `NEOPIXEL_DATA_PIN` definition
  - Example configurations for ESP32 DevKit and ESP32-S3
  - Drastically simplified wiring: 1 pin total (vs 12 for PWM)
- **Complete documentation** (EN + FR):
  - `/docs/neopixel_integration.md` & `_FR.md`: Setup, configuration, troubleshooting
  - Architecture diagrams and API reference
  - Hardware requirements and wiring examples

### Changed
- **light_helpers.h/cpp**: Now wrapper functions redirecting to unified manager
- **modes.cpp**: `initLights()` now uses `trafficLights.begin()`
- **Adafruit NeoPixel library**: Already in dependencies (v1.12.0+)

### Compatibility
- ✅ All 20+ animations work identically with both PWM and NeoPixel
- ✅ Backward compatible: Default behavior unchanged (PWM mode)
- ✅ Seamless switching: Remove/add `-D USE_NEOPIXEL_LIGHTS` flag to switch

### Documentation Updated
- README.md & README_FR.md: Added NeoPixel section with version highlight
- New dedicated guides: `neopixel_integration.md` & `_FR.md`

---

## [0.11.4] – Animation Cleanup & Auto Route (2026-01-10)
### Changed
- Removed redundant modes: Zen (merged into Pulse Green), classic Rainbow (Turbo kept), Disco (duplicated Jackpot), FDJ Winner and Client Winner (merged into Winner).
- New **Winner** mode: 4-phase festive sequence (yellow flash → green wave with trail → bright RGB random → stable green finale), more festive than FDJ Winner but lighter than Jackpot.
- Default mode switched to Pulse Green; automatic mode daytime uses Pulse Green instead of Zen.
- Web UI buttons reorganized with correct indices and highlighting; removed obsolete buttons and added Winner.
- Sub-mode mappings updated to match remaining modes.

### Fixed
- Added missing `/auto` route to handle automatic mode configuration (fixes Not found: /auto).

### Docs
- Updated FR/EN mode reference to reflect mode removals, new Winner, button reordering, and auto-mode behavior.

---

## [0.11.3] – New ESP32-S3 GPIO Mapping (2026-01-09)
### Changed
- Updated GPIO mapping for `esp32s3_n16r8` (ESP32-S3 DevKitC-1 N16R8):
  - Module 0: Red 1, Yellow 2, Green 42
  - Module 1: Red 41, Yellow 40, Green 39
  - Module 2: Red 4, Yellow 5, Green 6
  - Module 3: Red 7, Yellow 15, Green 16
  - Buttons: 21 (mode), 20 (sub-mode)
- All user documentation (FR + EN) updated to reflect this mapping and ensure consistency with the source code.

---

## [0.11.2] – ESP32-S3 Anti-Bootloop Fixes (2026-01-09)
### Fixed
- **Critical bootloop issue on ESP32-S3** caused by unsafe GPIO selection.
- GPIO 1, 2 now avoided (UART0 communication).
- GPIO 0 now avoided (boot button risk).
- GPIO 45, 46 now avoided (strapping pins).
- GPIO 26-32 now avoided (input-only on S3).

### Changed
- ESP32-S3 GPIO mapping updated to GPIO 3-16 (100% safe for PWM).
- New mapping: Module 1 (GPIO 3-5), Module 2 (GPIO 6-8), Module 3 (GPIO 9-11), Module 4 (GPIO 12-14), Buttons (GPIO 15-16).
- Documentation updated to reflect real GPIO allocation.

### User Impact
- ESP32-S3 now stable with zero bootloop risk.
- Hardware setup must use GPIO 3-16 for LEDs.

---

## [0.11.1] – Environment Naming Cleanup (2026-01-09)
### Changed
- Environment renamed from `upesy_wroom` to `esp32devkit` for clarity.
- Board specification changed to `esp32doit-devkit1` (standard PlatformIO board).
- Compilation flag changed from `-D ENV_ESP32_CLASSIC` to `-D ENV_ESP32_DEVKIT`.

---

## [0.11.0] – Dual-Environment Architecture Stabilization (2026-01-09)
### Added
- Common `[env]` section in `platformio.ini` for shared configuration.
- Inheritance-based build flag system (`${env.build_flags}`, `${env.lib_deps}`).
- Monitor exception decoder for ESP32-S3 debugging.

### Changed
- `platformio.ini` restructured for better maintainability.
- Both environments now inherit common settings.
- Default environment set to `esp32devkit`.

---

## [0.10.0] – GPIO Configuration Refactoring (2026-01-09)
### Added
- New `[env]` common configuration section in `platformio.ini`.
- All dependencies centralized in common section.
- Build flags and monitor speeds unified.

### Changed
- `esp32devkit` and `esp32s3_n16r8` now inherit from `[env]`.
- Reduced configuration duplication.
- Cleaner, more maintainable project structure.

---

## [0.9.0] – Multi-Environment Architecture (2026-01-09)
### Added
- **New ESP32-S3 DevKitC-1 N16R8 environment** with PSRAM support.
- Common `[env]` section in `platformio.ini` to share dependencies and build flags.
- Multi-environment GPIO mapping system in `board_config.h`.
- Compilation flags `-D ENV_UPESY_WROOM` and `-D ENV_ESP32S3_N16R8` for automatic mapping selection.
- Safe GPIO mapping for ESP32-S3 (GPIO 1-14) avoiding boot-sensitive and USB/JTAG pins.
- Complete libraries added: Adafruit BusIO, GFX, ST7735/ST7789, TinyGPSPlus, U8g2.

### Changed
- Complete restructuring of `platformio.ini` with configuration inheritance.
- `board_config.h` now features two distinct mappings protected by `#ifdef`.
- UPESY_WROOM mapping kept strictly identical (no modifications).
- Version incremented from 0.8.0 → 0.9.0.

### User Impact
- Project now compiles for two different ESP32 boards.
- Environment selection available via PlatformIO: `upesy_wroom` or `esp32s3_n16r8`.
- No impact on existing light mode behavior.

### Developer Impact
- New environments easily added via common `[env]` section.
- Modular and extensible GPIO mapping.
- Better code organization with clear hardware configuration separation.

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
