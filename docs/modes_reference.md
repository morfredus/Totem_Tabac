# ✅ **7 — `/docs/modes_reference.md`**

```markdown
# Modes Reference — Totem Feux du Tabac

This document describes all lighting modes available in **Totem Feux du Tabac**.  
It explains what each mode does, how it behaves, and which sub‑modes are available.

This guide is beginner‑friendly and intended for anyone who wants to understand or customize the animations.

---

# 1. Overview

The system includes **20+ lighting modes**, grouped into categories:

- Ambient modes  
- Pulse modes  
- Dynamic animations  
- Special effects  
- Functional modes  
- Fun / shop‑specific modes  

Each mode is selected via:

- Web interface  
- Physical button (Next Mode)  
- API routes  

Sub‑modes allow variations such as:

- Speed  
- Direction  
- Color themes  

---

# 2. Ambient Modes

## 2.1 Zen Breathing
A soft breathing effect across all modules.

- Smooth sinusoidal fade  
- Calm and slow  
- Ideal for background ambiance  

**Sub‑modes:**  
0 = very slow  
1 = slow  
2 = normal  

---

## 2.2 Soft Ambiance
A gentle color cycling effect.

- Low‑intensity transitions  
- Relaxed atmosphere  

**Sub‑modes:**  
0 = warm tones  
1 = cool tones  
2 = mixed  

---

## 2.3 Wave
A wave of light moving across the 4 modules.

- Sequential activation  
- Smooth fade in/out  

**Sub‑modes:**  
0 = slow wave  
1 = medium wave  
2 = fast wave  

---

# 3. Rainbow Modes

## 3.1 Rainbow
Classic RGB rainbow cycling.

- Smooth hue rotation  
- All modules synchronized  

**Sub‑modes:**  
0 = slow  
1 = normal  
2 = fast  

---

## 3.2 Rainbow Turbo
A faster, more energetic version.

- Rapid color cycling  
- High‑energy effect  

**Sub‑modes:**  
0 = turbo  
1 = hyper  
2 = insane  

---

# 4. Pulse Modes (PWM)

These modes use **true PWM fading**.

## 4.1 Pulse Green  
## 4.2 Pulse Yellow  
## 4.3 Pulse Red  

Each mode:

- Fades one color up/down  
- Uses sinusoidal brightness curve  
- All modules pulse together  

**Sub‑modes:**  
0 = slow  
1 = normal  
2 = fast  

---

# 5. Dynamic Animations

## 5.1 Rush
A rapid chase effect.

- LEDs flash quickly in sequence  
- High‑energy animation  

**Sub‑modes:**  
0 = clockwise  
1 = counter‑clockwise  
2 = random  

---

## 5.2 K2000 (Bidirectional)
Classic Knight Rider effect.

- Red dot sweeps left → right → left  
- Smooth movement  

**Sub‑modes:**  
0 = slow  
1 = normal  
2 = fast  

---

## 5.3 K2000 Trail (Light Tail)
Enhanced K2000 with fading trail.

- Main red point  
- Fading tail behind it  
- Very smooth PWM effect  

**Sub‑modes:**  
0 = short trail  
1 = medium trail  
2 = long trail  

---

## 5.4 Disco
Random flashing colors.

- High randomness  
- Party effect  

**Sub‑modes:**  
0 = low chaos  
1 = medium chaos  
2 = full chaos  

---

# 6. Special Effects

## 6.1 Jackpot
Casino‑style spinning effect.

- Rapid cycling  
- Ends with a “winning” flash  

**Sub‑modes:**  
0 = slow spin  
1 = fast spin  
2 = ultra spin  

---

## 6.2 FDJ Winner
Celebration animation for lottery winners.

- Blue/white flashes  
- Fast strobe  

**Sub‑modes:**  
0 = short celebration  
1 = medium  
2 = long  

---

# 7. Customer Interaction Modes

## 7.1 Client Gagnant
Green celebration.

- Flashing green  
- Positive effect  

---

## 7.2 Client Perdant
Red disappointment effect.

- Flashing red  
- Short animation  

---

# 8. Functional Modes

## 8.1 Ouverture
Indicates shop opening.

- Green sweeping animation  
- Friendly and welcoming  

---

## 8.2 Fermeture
Indicates shop closing.

- Red sweeping animation  
- Slow fade to black  

---

## 8.3 Pause Café
Indicates temporary break.

- Yellow pulsing  
- Calm and clear  

---

## 8.4 Maintenance
Indicates technical work.

- Alternating yellow/red  
- Slow blinking  

---

# 9. Mood Mode

## 9.1 Humeur du Patron
A fun mode representing the shop owner's mood.

**Sub‑modes:**  
0 = Happy (green)  
1 = Neutral (yellow)  
2 = Angry (red)  
3 = Energetic (rainbow)  
4 = Tired (soft blue)  
5 = Party (disco)  

---

# 10. Summary Table

```
Mode Category        | Mode Name           | Sub‑Modes | Description
---------------------|---------------------|-----------|-------------------------------
Ambient              | Zen                 | Yes       | Soft breathing fade
Ambient              | Soft Ambiance       | Yes       | Gentle color cycling
Ambient              | Wave                | Yes       | Sequential wave effect
Rainbow              | Rainbow             | Yes       | Classic rainbow cycle
Rainbow              | Rainbow Turbo       | Yes       | Fast rainbow cycle
Pulse                | Pulse Green         | Yes       | PWM fade
Pulse                | Pulse Yellow        | Yes       | PWM fade
Pulse                | Pulse Red           | Yes       | PWM fade
Dynamic              | Rush                | Yes       | Fast chase
Dynamic              | K2000               | Yes       | Knight Rider sweep
Dynamic              | K2000 Trail         | Yes       | Sweep with fading tail
Dynamic              | Disco               | Yes       | Random flashing
Special              | Jackpot             | Yes       | Casino effect
Special              | FDJ Winner          | Yes       | Celebration
Customer             | Client Gagnant      | No        | Green flash
Customer             | Client Perdant      | No        | Red flash
Functional           | Ouverture           | No        | Opening animation
Functional           | Fermeture           | No        | Closing animation
Functional           | Pause Café          | No        | Yellow pulse
Functional           | Maintenance         | No        | Warning blink
Mood                 | Humeur du Patron    | Yes       | 6 moods
```

---

# 11. Conclusion

This reference covers all available modes in **Totem Feux du Tabac**.  
Each mode can be customized or extended by modifying `modes.cpp`.

For more details, see:

- `/docs/pwm_system.md`  
- `/docs/architecture.md`  
- `/docs/troubleshooting.md`  
