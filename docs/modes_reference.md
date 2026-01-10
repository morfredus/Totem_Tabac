# Modes Reference — Totem Feux du Tabac

This document describes all lighting modes available in **Totem Feux du Tabac**.  
It explains what each mode does, how it behaves, and which sub‑modes are available.

This guide is beginner‑friendly and intended for anyone who wants to understand or customize the animations.

---

# 1. Overview

The system includes **16 lighting modes**, grouped into categories:

- Ambient modes (2 modes)
- Rainbow mode (1 mode)
- Pulse modes (3 modes)
- Dynamic animations (3 modes)
- Special effects (2 modes)
- Functional modes (4 modes)
- Mood mode (1 mode)

Each mode is selected via:

- Web interface  
- Physical button (Next Mode)  
- API routes  

Sub‑modes allow variations such as speed, direction, or effects.

---

# 2. Ambient Modes

## 2.1 Soft Lighting (Ambiance Douce)
**Index: 0**

Gentle and progressive color cycle.

- Soft transitions between green and yellow
- Relaxing and warm atmosphere
- Continuous smooth animation

**No sub‑modes**

---

## 2.2 Wave
**Index: 1**

A green light wave traveling across all 4 modules.

- Sequential module activation
- Soothing and fluid effect
- Constant left-to-right movement

**No sub‑modes**

---

# 3. Rainbow Mode

## 3.1 Rainbow
**Index: 2**

Dynamic and colorful RGB cycle.

- Full rainbow color rotation
- Staggered modules for wave effect
- 6 colors: Red, Yellow, Green, Cyan, Violet, White

**Sub‑modes:**  
- 0 = Normal (120 ms between steps)
- 1 = Turbo (60 ms between steps)

---

# 4. Pulse Modes (PWM)

These modes use **real PWM fade** for smooth and fluid breathing.

## 4.1 Green Pulse  
**Index: 3**

Sinusoidal green breathing on all modules.

**Sub‑modes:**  
- 0 = Slow 🐢 (40 ms per step)
- 1 = Normal 🚶 (20 ms per step)
- 2 = Fast 🏃 (10 ms per step)

---

## 4.2 Yellow Pulse  
**Index: 4**

Sinusoidal yellow breathing on all modules.

**Sub‑modes:**  
- 0 = Slow 🐢 (40 ms per step)
- 1 = Normal 🚶 (20 ms per step)
- 2 = Fast 🏃 (10 ms per step)

---

## 4.3 Red Pulse  
**Index: 5**

Sinusoidal red breathing on all modules.

**Sub‑modes:**  
- 0 = Slow 🐢 (40 ms per step)
- 1 = Normal 🚶 (20 ms per step)
- 2 = Fast 🏃 (10 ms per step)

---

# 5. Dynamic Animations

## 5.1 Rush
**Index: 6**

Fast and energetic red flashing effect.

- Synchronized red flashes on all modules
- Very dynamic animation
- Ideal for attracting attention or rush periods

**No sub‑modes**

---

## 5.2 K2000 (Bidirectional)
**Index: 7**

Classic Knight Rider effect with white light point and trail.

- Intense white main point (255)
- Light trail behind (150 then 60)
- Smooth bidirectional movement
- Automatic reversal at edges

**Sub‑modes:**  
- 0 = Forward ➡️ (150 ms per step)
- 1 = Backward ⬅️ (80 ms per step)
- Note: Sub-mode 2 accelerates further (40 ms)

---

## 5.3 Jackpot
**Index: 8**

Very festive "slot machine" effect.

- Random RGB colors changing rapidly
- Full white flash every 8 steps
- Continuous and energetic animation

**Sub‑modes:**  
- 0 = Slow 🐢 (150 ms per step)
- 1 = Normal 🚶 (100 ms per step)
- 2 = Fast 🏃 (60 ms per step)

---

# 6. Special Effects

## 6.1 Winner 🎉
**Index: 9**

Complete celebration animation that merges the old FDJ Winner and Customer Winner.

**4-phase sequence:**

1. **Phase 1** (steps 0-7): Fast and festive yellow flashing
   - Alternating full yellow / off at 90 ms
   
2. **Phase 2** (steps 8-15): Rising green wave
   - Green point moving up with trail
   - Upward progression effect
   
3. **Phase 3** (steps 16-27): Bright random colors
   - Random RGB in high values (200-255)
   - Very festive and energetic effect
   
4. **Phase 4** (steps 28+): Stable green finale
   - All modules in fixed green
   - Victory confirmation

**Features:**
- More festive than old FDJ Winner alone
- Less intense and longer than Jackpot
- Complete and satisfying animation
- Total duration: approximately 2.5 seconds

**No sub‑modes**

---

# 7. Customer Interaction Modes

## 7.1 Customer Lost
**Index: 10**

Red flashes with intermittent yellow to indicate a loss.

- Fixed red continuously
- Alternating yellow blink
- Clear but not aggressive animation
- 180 ms delay between changes

**No sub‑modes**

---

# 8. Functional Modes

## 8.1 Open
**Index: 11**

Shop opening signal.

- Fixed green on all modules
- Clear and welcoming signal
- Visible from distance

---

## 8.2 Closed
**Index: 12**

Shop closing signal.

- Fixed red on all modules
- Clear closing signal
- Visible from distance

---

## 8.3 Coffee Break
**Index: 13**

Temporary break indication.

- Fixed yellow continuously
- Green blinking every 300 ms
- Clear but not urgent signal

---

## 8.4 Maintenance
**Index: 14**

Technical maintenance signal.

- Complete cycle of 6 colors
- Red → Yellow → Green → White → Violet → Blue
- Changes every 250 ms
- Technical and visible signal

---

# 9. Mood Mode

## 9.1 Boss Mood
**Index: 15**

Fun mode representing the boss's mood on module 4 only.

**Available colors (selectable via web interface):**

- 0 = Happy 😊 (green)
- 1 = Calm 😌 (yellow)
- 2 = Angry 😡 (red)
- 3 = Serene 😇 (blue)
- 4 = Creative 🎨 (violet)
- 5 = Neutral 😐 (white)

**Note:** Only module 4 (the highest) lights up in this mode.

---

# 10. Summary Table

```
Index | Category      | Mode                    | Sub‑modes  | Description
------|---------------|-------------------------|------------|-------------------------------
0     | Ambient       | Soft Lighting           | No         | Soft green/yellow cycle
1     | Ambient       | Wave                    | No         | Sequential green wave
2     | Rainbow       | Rainbow                 | Yes (0-1)  | Colorful RGB cycle
3     | Pulse         | Green Pulse             | Yes (0-2)  | Green PWM breathing
4     | Pulse         | Yellow Pulse            | Yes (0-2)  | Yellow PWM breathing
5     | Pulse         | Red Pulse               | Yes (0-2)  | Red PWM breathing
6     | Dynamic       | Rush                    | No         | Fast red flashing
7     | Dynamic       | K2000                   | Yes (0-1)  | White sweep with trail
8     | Dynamic       | Jackpot                 | Yes (0-2)  | Random colors + flash
9     | Special       | Winner 🎉               | No         | Festive 4-phase animation
10    | Customer      | Customer Lost           | No         | Red/yellow flash
11    | Functional    | Open                    | No         | Fixed green
12    | Functional    | Closed                  | No         | Fixed red
13    | Functional    | Coffee Break            | No         | Yellow + blinking green
14    | Functional    | Maintenance             | No         | 6-color cycle
15    | Mood          | Boss Mood               | Yes (0-5)  | Module 4 color
```

---

# 11. Changes from Previous Versions

## Removed Modes

- **MODE_ZEN**: Removed as identical to Green Pulse. Use Green Pulse instead.
- **MODE_ARC_EN_CIEL (classic)**: Removed as Rainbow Turbo is sufficient. The remaining mode now offers 2 speeds via sub-modes.
- **MODE_DISCO**: Removed as identical to Jackpot. Use Jackpot instead.
- **MODE_FDJ_WINNER**: Merged into the new Winner mode.
- **MODE_CLIENT_GAGNANT**: Merged into the new Winner mode.

## Modified Modes

- **Winner 🎉**: New mode combining the best aspects of FDJ Winner and Customer Winner, with a more festive and complete 4-phase animation.

## Web Interface Impact

All buttons have been reorganized to reflect the new structure:
- Mode indices have been updated
- Sub-modes correspond to the correct modes
- Automatic mode now has a functional `/auto` route

---

# 12. Automatic Mode

The system includes an automatic mode that switches automatically between:

- **Closed** (red): before opening time and after closing time
- **Green Pulse** (default): during opening hours

Configuration via web interface:
- Opening time (default: 8 AM)
- Closing time (default: 6 PM)
- Enable/disable toggle

---

# 13. Conclusion

This reference covers all 16 modes available in **Totem Feux du Tabac**.  
Each mode can be modified or extended in [modes.cpp](../src/modes.cpp).

For more information:

- [/docs/pwm_system.md](pwm_system.md) — Technical details about the PWM system
- [/docs/architecture.md](architecture.md) — Project architecture
- [/docs/troubleshooting.md](troubleshooting.md) — Troubleshooting guide

---

**Last updated:** January 2026  
**Version:** Compatible with current firmware version
