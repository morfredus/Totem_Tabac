# ✅ **13 — `/docs/faq.md`**

```markdown
# FAQ — Totem Feux du Tabac

This FAQ answers the most common questions about installing, configuring, and using **Totem Feux du Tabac**.

---

# 1. General Questions

## 1.1 What is Totem Feux du Tabac?
It is an ESP32‑based lighting system controlling 4 traffic‑light modules with more than 20 animations.

---

## 1.2 Which ESP32 boards are supported?
- ESP32 DevKit (WROOM)
- ESP32‑S3 DevKitC‑1 N16R8
- ESP32‑S3 N8R8

All boards using the Arduino framework in PlatformIO are compatible.

---

## 1.3 Can I add more traffic‑light modules?
Yes, but you must:

- Add more GPIOs  
- Add more PWM channels  
- Update `board_config.h`  
- Update `initTrafficLightPWM()`  

---

# 2. Hardware Questions

## 2.1 Do I need resistors for the LEDs?
Most traffic‑light modules already include resistors.  
If using bare LEDs, add 220–330 Ω resistors.

---

## 2.2 Can I power everything from USB?
For testing: **yes**  
For real installation: **no**

Use a stable 5V power supply (2A recommended).

---

## 2.3 My LEDs flicker. Why?
Most common causes:

- Missing common ground  
- Weak power supply  
- Loose wires  

---

## 2.4 Can I use GPIO 34–39?
No.  
These pins are **input‑only** and cannot output PWM.

---

# 3. Software Questions

## 3.1 Do I need PlatformIO?
Yes.  
The project is designed for PlatformIO and will not compile in the Arduino IDE.

---

## 3.2 How do I change the default mode?
Edit:

```
currentMode = MODE_ZEN;
```

in `main.cpp`.

---

## 3.3 How do I add a new mode?
1. Add a constant in `modes.h`  
2. Add a new `case` in `updateMode()`  
3. Implement animation logic  
4. Add UI support (optional)  

---

# 4. WiFi Questions

## 4.1 I cannot find the WiFi Manager network
The ESP32 may already be connected to a saved WiFi.

Reset the ESP32 or clear credentials.

---

## 4.2 The captive portal does not open
Open manually:

```
http://192.168.4.1/
```

---

## 4.3 Can I disable WiFi?
Yes.  
Comment out WiFi initialization in `main.cpp`.

---

# 5. Web Interface Questions

## 5.1 The interface does not load
Try:

- `http://totem.local`  
- The ESP32 IP address  
- Clearing browser cache  

---

## 5.2 Buttons in the UI do nothing
Possible causes:

- ESP32 disconnected  
- Browser caching old scripts  

---

# 6. Animation Questions

## 6.1 Why do some modes have sub‑modes?
Sub‑modes allow:

- Speed variations  
- Direction changes  
- Color variations  

---

## 6.2 Can I change animation speed?
Yes.  
Modify the `delayMs` value inside each mode.

---

## 6.3 Can I change colors?
Yes.  
Use:

```
setRGB(module, r, y, g);
```

in `modes.cpp`.

---

# 7. Buttons Questions

## 7.1 Can I add more buttons?
Yes.  
Add new GPIOs and update button handling in `main.cpp`.

---

## 7.2 My button triggers multiple times
Add software debounce (10–50 ms).

---

# 8. Advanced Questions

## 8.1 Can I control the system via HTTP?
Yes.  
Available routes:

- `/nextmode`
- `/nextsub`
- `/status`

---

## 8.2 Can I integrate this with Home Assistant?
Yes, via HTTP requests or ESPHome (manual porting required).

---

## 8.3 Can I run this on battery?
Not recommended.  
LEDs and ESP32 consume too much power.

---

# 9. Summary

This FAQ covers:

- Hardware  
- Software  
- WiFi  
- Web interface  
- Animations  
- Buttons  
- Advanced usage  

For more details, see the other documentation files in `/docs/`.
