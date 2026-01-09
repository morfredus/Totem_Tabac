# PWM System — Totem Feux du Tabac

This document explains how the PWM (Pulse Width Modulation) system works in **Totem Feux du Tabac**.  
It covers channel allocation, frequency, resolution, helper functions, and best practices for creating smooth lighting animations.

This guide is intended for beginners and advanced users who want to understand or extend the LED engine.

---

# 1. What is PWM?

PWM (Pulse Width Modulation) is a technique used to control LED brightness by switching the signal ON and OFF very quickly.

- **0** = LED fully OFF  
- **255** = LED fully ON  
- Values in between = brightness levels  

The ESP32 can generate PWM signals on many GPIO pins using the **LEDC** hardware peripheral.

---

# 2. PWM Configuration

The project uses:

- **12 PWM channels**
- **8‑bit resolution** (0–255)
- **1 kHz frequency**

### Why 8‑bit?

- Smooth enough for fades  
- Fast to compute  
- Compatible with all ESP32 variants  

### Why 1 kHz?

- No visible flicker  
- Stable for long‑term use  
- Works well with LED modules  

---

# 3. Channel Allocation

Each traffic‑light module has:

- 1 × Red LED  
- 1 × Yellow LED  
- 1 × Green LED  

Total: **4 modules × 3 LEDs = 12 channels**

```
RED_CH    = {0, 1, 2, 3}
YELLOW_CH = {4, 5, 6, 7}
GREEN_CH  = {8, 9, 10, 11}
```

Example:

```
Module 0 → Red channel 0
Module 1 → Red channel 1
Module 2 → Red channel 2
Module 3 → Red channel 3
```

---

# 4. GPIO Mapping

Each PWM channel is attached to a specific GPIO defined in `board_config.h`.


## ESP32 DevKit (esp32devkit)
```
Module 0: Red 4, Yellow 5, Green 12
Module 1: Red 13, Yellow 14, Green 16
Module 2: Red 17, Yellow 18, Green 19
Module 3: Red 21, Yellow 22, Green 23
```

## ESP32-S3 DevKitC-1 N16R8 (esp32s3_n16r8)
```
Module 0: Red 1, Yellow 2, Green 42
Module 1: Red 41, Yellow 40, Green 39
Module 2: Red 4, Yellow 5, Green 6
Module 3: Red 7, Yellow 15, Green 16
Buttons: 21 (mode), 20 (submode)
```

---

# 5. Initialization

PWM is initialized in `initTrafficLightPWM()`:

- Configure 12 channels  
- Attach each channel to its GPIO  
- Set frequency and resolution  

Pseudo‑code:

```
for each channel:
    ledcSetup(channel, 1000 Hz, 8 bits)
    ledcAttachPin(gpio, channel)
```

---

# 6. Helper Functions

The PWM system is abstracted through helper functions in `light_helpers.cpp`.

## 6.1 setRed(module, value)

Sets brightness of the red LED of a module.

```
setRed(0, 255);  // full brightness
setRed(2, 128);  // half brightness
```

## 6.2 setYellow(module, value)

Same as above for yellow.

## 6.3 setGreen(module, value)

Same as above for green.

## 6.4 setRGB(module, r, y, g)

Sets all 3 LEDs at once.

```
setRGB(1, 255, 128, 0);
```

## 6.5 clearModule(module)

Turns off all LEDs of a module.

## 6.6 clearAll()

Turns off all LEDs of all modules.

---

# 7. Fade Engine

Many modes use sinusoidal fading:

```
value = (sin(angle) + 1) * 127.5
```

This produces:

- Smooth transitions  
- Natural breathing effects  
- No visible steps  

Used in:

- Zen  
- Pulse modes  
- Wave  
- Rainbow transitions  

---

# 8. Timing and Animation

Animations use:

- `millis()` for timing  
- `lastUpdate` to control frame rate  
- `animStep` to track animation progress  

Example:

```
if (now - lastUpdate > delayMs) {
    animStep++;
    lastUpdate = now;
}
```

---

# 9. Best Practices

### Use clearAll() before drawing a new frame  
Prevents ghosting.

### Avoid writing to GPIO directly  
Always use helper functions.

### Keep PWM values between 0–255  
Do not exceed 255.

### Use sub‑modes for speed variations  
Keeps code clean.

### Use sinusoidal curves for smooth fades  
Linear fades look harsh.

---

# 10. Extending the PWM System

To add a new LED or module:

1. Add new GPIOs in `board_config.h`  
2. Add new PWM channels  
3. Update `initTrafficLightPWM()`  
4. Add helper functions if needed  

To add new animations:

- Use `setRed()`, `setYellow()`, `setGreen()`, or `setRGB()`  
- Use fades, waves, or patterns  
- Update `modes.cpp`  

---

# 11. Summary

The PWM system provides:

- 12 independent channels  
- Smooth 8‑bit brightness control  
- Helper functions for easy use  
- A clean architecture for animations  

This system is the foundation of all lighting effects in **Totem Feux du Tabac**.
