# NeoPixel Integration Guide

## Overview

Starting with version **0.12.0**, the Totem Feux du Tabac project supports **NeoPixel modules** as an alternative to traditional PWM traffic lights. This enhancement provides:

- 🎨 **Richer color control** with RGB capabilities
- ⚡ **Drastically simplified wiring** (1 pin instead of 12!)
- 🔄 **Seamless transition** from PWM to NeoPixel without code changes
- 🧩 **Unified interface** for both light systems

**Key Advantage:** NeoPixels are **addressable** — a single GPIO pin controls all 12 LEDs in a chain (4 modules × 3 LEDs each).

---

## Architecture

### Traffic Light Manager

The system uses a **unified manager** (`TrafficLightManager`) that handles both PWM and NeoPixel lights transparently. All existing animations and modes work identically regardless of the light type used.

```
┌─────────────────────────────────────┐
│    TrafficLightManager              │
│  (Unified Interface)                │
└──────────────┬──────────────────────┘
               │
      ┌────────┴────────┐
      │                 │
┌─────▼─────┐   ┌──────▼──────────┐
│  PWM Mode │   │  NeoPixel Mode  │
│           │   │                 │
│ 12 pins   │   │ 1 pin only!    │
│ (3/module)│   │ (12 LEDs chain)│
└───────────┘   └─────────────────┘
```

### Key Components

#### 1. **TrafficLightManager** Class (Unified System)
Located in `include/traffic_light_manager.h` and `src/traffic_light_manager.cpp`

Provides unified control over 4 traffic light modules using **one NeoPixel strip** of 12 addressable LEDs, automatically selecting between PWM and NeoPixel based on compile-time configuration.

**LED Organization:**
- Module 0: LEDs 0, 1, 2 (Red, Yellow, Green)
- Module 1: LEDs 3, 4, 5 (Red, Yellow, Green)
- Module 2: LEDs 6, 7, 8 (Red, Yellow, Green)
- Module 3: LEDs 9, 10, 11 (Red, Yellow, Green)

**Key Methods:**
```cpp
void begin();                               // Initialize all modules
void setRed(int module, uint8_t value);     // Control module 0-3
void setYellow(int module, uint8_t value);
void setGreen(int module, uint8_t value);
void setRGB(int module, bool r, bool y, uint8_t g);
void clearModule(int module);               // Turn off one module
void clearAll();                            // Turn off all modules
```

#### 3. **Light Helpers** (Compatibility Layer)
Located in `include/light_helpers.h` and `src/light_helpers.cpp`

Wrapper functions that redirect calls to the unified manager, ensuring backward compatibility with existing animation code.

---

## Hardware Setup

### NeoPixel Module Specifications

Total system consists of:
- **12 NeoPixel LEDs** (WS2812B or compatible) in a single addressable strip
- **Configuration:** NEO_GRB + NEO_KHZ800
- **Connection:** Single data pin + 5V + GND
- **Organization:** 4 modules of 3 LEDs each, controlled via addressing

### Wiring

#### Option 1: PWM Traffic Lights (Default)
Current system using 3 pins per module (red, yellow, green) as defined in `board_config.h`.

#### Optionly **1 data pin** for all 12 LEDs. Configure in `board_config.h`:

```cpp
// Example for ESP32 DevKit
#define NEOPIXEL_DATA_PIN    27

// Example for ESP32-S3
#define NEOPIXEL_DATA_PIN    8
```

**Wiring:**
```
ESP32 GPIO 27 ──► DATA (first LED)
5V ─────────────► VCC (all LEDs)
GND ────────────► GND (all LEDs)

LED chain: LED0 → LED1 → LED2 → ... → LED11
(Each arrow is the DOUT→DIN connection between LEDs)
#define NEOPIXEL_PIN_4    11
```


Edit `include/board_config.h` and uncomment/define the NeoPixel data pin for your board:

```cpp
// Uncomment and configure for your board
#define NEOPIXEL_DATA_PIN    27
```

**Note:** Only ONE pin is needed for all 12 LEDs!Uncomment and configure for your board
#define NEOPIXEL_PIN_1    27
#define NEOPIXEL_PIN_2    32
#define NEOPIXEL_PIN_3    33
#define NEOPIXEL_PIN_4    34
```

### Step 2: Enable NeoPixel Mode

Edit `platformio.ini` and add the `USE_NEOPIXEL_LIGHTS` flag:

```ini
[env:esp32devkit]
platform = espressif32
board = esp32dev

build_flags =
    ${env.build_flags}
    -D ENV_ESP32_DEVKIT
    -D USE_NEOPIXEL_LIGHTS    # Add this line
```

### Step 3: Build and Upload

```bash
pio run -e esp32devkit -t upload
```

---

## Switching Between Systems

To switch back to PWM mode:

1. Comment out or remove `-D USE_NEOPIXEL_LIGHTS` from `platformio.ini`
2. Rebuild and upload

**No code changes required!** The manager automatically selects the appropriate system at compile time.

---

## Color Rendering

### Yellow LED in NeoPixel Mode

Yellow is rendered as an RGB mix to approximate the warm yellow of traditional LEDs:
- **Red:** 100% of brightness value
- **Green:** ~70% of brightness value (180/255 ratio)
- **Blue:** 0%

This produces a natural-looking yellow without being too green.

### Brightness Control

Each NeoPixel module supports global brightness control (0-255) in addition to per-LED intensity control, allowing fine-tuned light output.

---

## Animation Compatibility

All existing animations work identically with NeoPixel modules:

- ✅ **Pulse modes** (green, yellow, red)
- ✅ **Wave effect**
- ✅ **K2000 scanner**
- ✅ **Rainbow turbo**
- ✅ **Jackpot effect**
- ✅ **Winner/Loser effects**
- ✅ **All status modes**

The unified interface ensures animations call the same functions regardless of the underlying hardware.

---

## Troubleshooting

### LEDs Don't Light Up

1. **Check power supply:** NeoPixels require stable 5V power
2. **Verify pins:** Ensure `NEOPIXEL_PIN_x` definitions match your wiring
3. **Check flag:** Confirm `-D USE_NEOPIXEL_LIGHTS` is in `platformio.ini`
4. **Check wiring:** Data line should connect to defined GPIO pin

### Wrong Colors

1. **Check LED order:** Default is NEO_GRB; adjust in `traffic_light_neopixel.cpp` if needed
2. **Verify module type:** WS2812B vs SK6812 may have different color orders

### Flickering

1. **Add capacitor:** 1000µF between 5V and GND near NeoPixels
2. **Check power:** Insufficient power can cause instability
3. **Add resistor:** 330Ω in series with data line

---

## Technical Details

### Memory Usage500 bytes for Adafruit_NeoPixel (single strip of 12 LEDs

- **PWM Mode:** ~200 bytes static + channels
- **NeoPixel Mode:** ~100 bytes per module + Adafruit_NeoPixel overhead (~1KB total)

### Performance

- **PWM:** Direct hardware control, no CPU overhead
- **NeoPixel:** ~30µs per LED update via bit-banging

Both systems provide smooth animations; choose based on your hardware preferences.

---

## API Reference

### Global Instance

```cpp
extern TrafficLightManager trafficLights;
```

Use this global instance throughout your code.

### Example Usage

```cpp
#include "traffic_light_manager.h"

void setup() {
    trafficLights.begin();  // Initialize system
    trafficLights.clearAll();
}

void loop() {
    // Set module 0 to full red
    trafficLights.setRed(0, 255);
    delay(1000);
    
    // Set module 1 to medium yellow
    trafficLights.setYellow(1, 128);
    delay(1000);
    
    // Clear all
    trafficLights.clearAll();
    delay(1000);
}
```

---

## Version History

- **0.12.0** (January 2026): NeoPixel support added with unified manager architecture
- **0.11.x**: PWM-only system

---

## See Also

- [Hardware Setup Guide](hardware_setup.md)
- [Modes Reference](modes_reference.md)
- [PWM System Documentation](pwm_system.md)
- [Architecture Overview](architecture.md)
