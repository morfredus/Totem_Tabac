# Quick Start — NeoPixel Integration

## What Changed in v0.12.0?

The project now supports **NeoPixel RGB modules** as an alternative to traditional PWM traffic lights, with **zero code changes** required in your animations.

---

## For Users Sticking with PWM (Default)

**Nothing to do!** The system continues to work exactly as before. All existing wiring and configurations remain valid.

---

## For Users Switching to NeoPixel

### 1. Hardware Setup
Replace your 3-wire traffic light modules with NeoPixel modules:
- **Total:** 12 NeoPixel LEDs (WS2812B or compatible) in a single addressable strip
- **Organization:** 4 modules × 3 LEDs each (Module 0: LEDs 0-2, Module 1: LEDs 3-5, etc.)
- **Wiring:** **1 data pin** + 5V + GND for all 12 LEDs (vs 12 PWM pins before)

### 2. Software Configuration

#### Step A: Define Pin in `board_config.h`
Uncomment and configure the NeoPixel data pin:

```cpp
// For ESP32 DevKit
#define NEOPIXEL_DATA_PIN    27

// For ESP32-S3
// #define NEOPIXEL_DATA_PIN    8
```

**Note:** NeoPixels are addressable — only one GPIO controls all 12 LEDs!

#### Step B: Enable NeoPixel Mode in `platformio.ini`
Add the flag to your environment's `build_flags`:

```ini
[env:esp32devkit]
build_flags =
    ${env.build_flags}
    -D ENV_ESP32_DEVKIT
    -D USE_NEOPIXEL_LIGHTS    # Add this line
```

#### Step C: Build and Upload
```bash
pio run -e esp32devkit -t upload
```

---

## Key Benefits

✅ **Extremely Simplified Wiring:** 1 pin instead of 12!  
✅ **Richer Colors:** Full RGB control per LED  
✅ **Same Animations:** All modes work identically  
✅ **Easy Switch:** Toggle compile flag to switch systems  

---

## Full Documentation

- [Complete NeoPixel Guide (EN)](docs/neopixel_integration.md)
- [Guide Complet NeoPixel (FR)](docs/neopixel_integration_FR.md)

---

## Architecture Summary

```
          Your Animation Code
                  ↓
        TrafficLightManager
         (Unified Interface)
                  ↓
         ┌────────┴────────┐
         ↓                 ↓
    PWM System      NeoPixel System
   (12 channels)     (1 data pin)
                    (12 LEDs chain)
```

**The manager handles everything automatically based on your compile-time choice.**

---

## Troubleshooting

**LEDs don't work?**
1. Check power supply (5V stable)
2. Verify pin definitions match your wiring
3. Confirm `-D USE_NEOPIXEL_LIGHTS` flag is present
4. Check data line connections

**Need to switch back to PWM?**
1. Remove `-D USE_NEOPIXEL_LIGHTS` from `platformio.ini`
2. Rebuild and upload

---

## Questions?

See full documentation or open an issue on the project repository.
