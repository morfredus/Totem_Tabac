## [0.18.0] – OTA (Over-The-Air) firmware updates (2026-01-11)
### Added
- **OTA Updates**: Firmware can now be updated wirelessly over WiFi without USB cable.
- **ArduinoOTA Integration**: Native ESP32 OTA implementation with password protection.
- **OTA Status Monitoring**: Real-time progress feedback and error handling during updates.
- **LED Shutdown on Update**: All LEDs automatically turn off during OTA update for visual feedback.

### Technical Details
- OTA Hostname: `Totem-Tabac`
- OTA Password: `totem2026` (configurable)
- mDNS support for device discovery
- Update progress displayed via Serial monitor
- Comprehensive error handling (Auth, Begin, Connect, Receive, End)
- Flash usage: 67.8% (888,973 bytes) - includes OTA libraries
- RAM usage: 15.3% (50,092 bytes)

### Usage
- Connect to same WiFi network as the totem
- Use Arduino IDE: Tools → Port → Totem-Tabac (network port)
- Or use PlatformIO: `pio run -t upload --upload-port Totem-Tabac.local`
- Enter password `totem2026` when prompted

## [0.17.0] – Enhanced matrix animations for Rush, K2000, Jackpot, FDJ Winner, and Maintenance (2026-01-11)
### Added
- **Rush mode**: Fast-moving horizontal lines with different speeds, creating a dynamic speed effect with red-orange and yellow colors.
- **K2000 mode**: Classic Kitt-style scanner with vertical columns sweeping left-right with red trailing effect.
- **Jackpot mode**: Slot machine animation with 3 columns of scrolling symbols (Dollar, 7, Cherry, Star) with golden flash on win.
- **FDJ Winner mode**: Victory animation with 3 phases: golden flash, confetti explosion from center, and falling golden coins.
- **Maintenance mode**: Complete matrix test cycling through 8 solid colors, horizontal line scan (cyan), and vertical column scan (orange).

### Changed
- All 5 modes now have dedicated 8x8 matrix animations that utilize the full display.
- Matrix animations respect global brightness settings via `applyMatrixBrightnessToRGB()`.
- PWM animations remain unchanged and fully functional.
- Animations designed to work with or without mask overlay on columns/lines 2 and 5.

### Technical Details
- Rush: Dual-speed horizontal scrolling with trailing effects (50ms refresh).
- K2000: Vertical column scanner with 3-level fade trail (100/60/35ms speeds).
- Jackpot: 4-symbol slot machine with color-coded symbols and periodic golden flash (120/80/50ms speeds).
- FDJ Winner: 40-frame animation loop with explosion physics and particle effects (80ms refresh).
- Maintenance: 24-phase test pattern for complete LED validation (200ms per phase).

## [0.16.1] – Fix brightness scaling for all animations (2026-01-11)
### Fixed
- **Brightness now applied to ALL matrix animations**: All 6 custom animations (Ouverture, Fermeture, Pause Café, Gagnant, Perdant, Humeur Patron) now properly respect the global brightness setting.
- Fixed smileys brightness in Ouverture/Fermeture modes.
- Fixed coffee animation brightness in Pause Café mode.
- Fixed fireworks brightness in Gagnant mode.
- Fixed rain brightness in Perdant mode.
- Fixed diagonal wave brightness in Humeur Patron mode.
- Brightness can now be set to 0 (complete matrix off) without issues.

### Technical Details
- Applied `applyMatrixBrightnessToRGB()` to all animation pixel colors before display.
- Each animation now scales RGB values by global brightness before calling `setPixelXY()`.
- Ensures consistent brightness control across all animation types.

## [0.16.0] – Full persistence and brightness control (2026-01-11)
### Added
- **Full NVS persistence**: Current animation mode, submode, and mood color are now saved and restored on boot.
- **Brightness range 0-255**: Matrix brightness can now be set from 0% (off) to 100% (full brightness).
- **Dynamic brightness in animations**: Brightness value is now applied to all matrix animations for consistent intensity control.

### Changed
- Brightness minimum changed from 10 to 0 (allows complete matrix shutdown).
- All animations now scale pixel colors based on global brightness setting.
- NVS persistence now includes: display type, brightness, current mode, submode, and mood color.

### Technical Details
- Added `loadModeFromNVS()` and `saveCurrentModeToNVS()` functions.
- Added `applyMatrixBrightnessToRGB()` helper function for consistent brightness scaling.
- Mode persistence saves on every mode/submode/mood change.
- Brightness range validation: 0 (off) to 255 (max).

## [0.15.0] – Enhanced matrix animations (2026-01-11)
### Added
- **Patron mood (Humeur du patron)**: Full matrix diagonal wave effect with color fading (30-100% brightness, never fully off).
- **Opening (Ouverture)**: Green full matrix with animated happy smiley face (LED eyes and curved smile off).
- **Closing (Fermeture)**: Red full matrix with animated neutral smiley face (LED eyes and straight mouth off).
- **Coffee break (Pause Café)**: Creative warm animation with rising bubbles and hot brown/orange gradient, mimicking steam from coffee.
- **Winner (Client Gagnant)**: Joy animation with full-matrix color waves and fireworks effect (yellow/green/magenta pulses).
- **Loser (Client Perdant)**: Sadness animation with rain-like falling effect in blue-grey and purple tones.

### Changed
- All 6 utility animations now use full 8x8 matrix for more visual impact when matrix mode is active.
- PWM mode animations remain unchanged and independent.
- Animation helper functions modularized for maintainability.

### Technical Details
- Matrix animations use brightness scaling and wave effects for smooth visual flow.
- Added static animation state tracking per mode for seamless animation transitions.
- Diagonal wave calculation optimized for performance on 64-LED matrix.

## [0.14.1] – Matrix 8x8 initialization fix (2026-01-11)
### Fixed
- **Matrix GPIO pin**: Changed from GPIO 27 to GPIO 15 (more stable at boot, no boot conflicts).
- **Matrix initialization sequence**: Corrected order to `begin() → clear() → setBrightness() → show()` with 10ms stabilization delay.
- **Display switching**: Added explicit PWM pin deactivation when switching to matrix mode (high-impedance state).
- **Mode switching stability**: Added 50ms delays during display type changes to ensure hardware stabilization.
- **Code organization**: Moved NeoPixel strip declaration to file beginning to fix compilation order issues.
- **Phantom LEDs**: Fixed residual PWM LEDs lighting up when matrix is selected.
- **Brightness control**: Corrected matrix brightness application during initialization.

### Technical Details
- PWM pins are now properly detached and set to INPUT mode when matrix is active.
- Matrix buffer is properly cleared and displayed during mode transitions.
- `showUniversal()` calls ensure all animations properly update the display.

## [0.14.0] – Mode cleanup and optimization (2026-01-11)
### Removed
- **MODE_ZEN**: Removed redundant mode (duplicate of Pulse Vert).
- **MODE_DISCO**: Removed (similar to Jackpot).
- **MODE_ARC_EN_CIEL_TURBO**: Removed (merged into Arc-en-ciel with speed submodes).

### Changed
- **MODE_ARC_EN_CIEL**: Now uses speed submodes (Slow/Medium/Fast) instead of direction inversion.
- Default startup mode changed from ZEN to PULSE_VERT.
- Mode enum reindexed for consistency (17 modes instead of 20).
- Web UI buttons now properly aligned with new mode indices.

### Fixed
- Web UI mode selection now correctly highlights active mode.
- Submode display logic updated for new mode structure.

## [0.13.0] – Modern festive web UI redesign (2026-01-11)
### Added
- Complete redesign of web interface with modern, festive, and professional styling.
- Glassmorphism design with gradient backgrounds and blur effects.
- Smooth animations (float, pulse, glow effects).
- Google Fonts integration (Poppins font family).
- Improved color palette buttons (larger, perfectly round, tooltips).
- Dedicated submode button styling with reserved space to prevent UI jumping.
- Enhanced hover effects and visual feedback.
- Responsive design optimized for mobile and desktop.

### Changed
- Web UI now uses modern CSS gradients and backdrop filters.
- Submode zones now have fixed height (60px) to maintain consistent layout.
- Color mood buttons increased from 48px to 60px for better accessibility.
- Interface title with animated gradient and emoji decorations.

### Fixed
- Submodes now properly display when mode is selected.
- Submodes are clickable and functional with dedicated styling.
- UI no longer jumps when submodes appear/disappear.

## [1.0.0] – Modern web UI overhaul (2026-01-11)
### Added
- New modern, interactive, responsive web interface.
- Exclusive display type selection (PWM or matrix) via UI.
- Dedicated settings section.

## [1.1.0] – Persistent settings (2026-01-11)
### Added
- Save/restore display type (NVS).
- Save/restore matrix brightness.

## [1.2.0] – Robust AJAX endpoints (2026-01-11)
### Added
- Endpoints /mode, /display, /brightness, /humeur, /status, /auto (later removed).
- Full UI action handling in firmware.

## [1.2.1] – JS/C++ fixes and robustness (2026-01-11)
### Fixed
- Fixed JS/C++ string conversion for web page generation.
- Fixed string and initialization bugs.

## [1.3.0] – PWM/matrix parity and clean switch (2026-01-11)
### Added
- Automatic LED shutdown when switching display type.
- Hardware re-init on PWM/matrix switch.

## [1.4.0] – Patron Mood RGB on matrix (2026-01-11)
### Added
- Selected color displayed on all three matrix traffic lights (full RGB palette).
- Full PWM/matrix parity for this mode.

## [1.4.1] – Removal of auto mode (2026-01-11)
### Removed
- Complete removal of time-based auto mode (backend, UI, endpoints).

## [1.4.2] – Comment and history cleanup (2026-01-11)
### Fixed
- Removed all references to Copilot in comments and changelogs.

## History — dev/8x8 branch
# History:
#   - v0.12.0-dev8x8: Added NeoPixel 8x8 matrix, traffic light mapping, synchronized doc
#   - v0.11.x and earlier: PWM classic modules only
#
## [0.12.0-dev8x8] – NeoPixel 8x8 Matrix Integration (2026-01-10)
### Added

## [0.12.0-dev8x8] – Display Selection, Web UI, Persistence (2026-01-10)
### Added
- **Exclusive display selection**: classic PWM modules *or* 8x8 NeoPixel matrix, never both at once.
- **Live selection via web UI** (radio button).
- **Automatic persistence** of display choice (NVS save/restore).
- **Universal helpers**: all animation logic now uses abstracted helpers, compatible with both PWM and matrix.
- **Full documentation sync** (EN/FR).

### Changed
- Refactored all animation code to use universal helpers.
- Web UI: new display selection section, simplified header.

### User Impact
- Firmware always starts with the last selected display (PWM or matrix).
- Instant switching via web UI, no reboot required.
- Documentation and guides updated.

---

- README, hardware_setup, and changelogs updated for matrix support

# Changelog — Totem Feux du Tabac
All notable changes to this project are documented in this file.

This project follows **Semantic Versioning (SemVer)**:  
**MAJOR.MINOR.PATCH**

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
