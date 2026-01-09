# Troubleshooting — Totem Feux du Tabac

This document lists common issues encountered when installing, wiring, compiling, or running **Totem Feux du Tabac**, along with their solutions.

It is designed to be simple, practical, and beginner‑friendly.

---

# 1. Hardware Issues

## 1.1 One LED does not light up
**Possible causes:**
- Wrong GPIO wiring  
- LED polarity reversed  
- Damaged LED  

**Solutions:**
- Check wiring against `/docs/hardware_setup.md`  
- Ensure anode (+) and cathode (–) are correct  
- Test the LED with a simple ON/OFF sketch  

---

## 1.2 All LEDs stay ON
**Cause:**  
Ground not connected or floating.

**Solution:**  
Connect **all grounds together**:  
ESP32 GND ↔ LED GND ↔ Power supply GND

---

## 1.3 LEDs flicker randomly
**Cause:**  
Unstable power supply or missing common ground.

**Solution:**  
- Use a stable 5V supply (2A recommended)  
- Ensure all grounds are connected  

---

## 1.4 ESP32 resets or crashes
**Possible causes:**
- Weak USB cable  
- Insufficient power  
- Short circuit  

**Solutions:**
- Try another USB cable  
- Use a proper 5V power supply  
- Inspect wiring for shorts  

---

## 1.5 PWM not working on some pins
**Cause:**  
Some GPIOs are **input‑only** or **boot‑sensitive**.

**Solution:**  
Use only PWM‑capable pins (see `board_config.h`).

---

# 2. Software Issues

## 2.1 PlatformIO cannot find the board
**Cause:**  
ESP32 platform not installed.

**Solution:**  
Install it from PlatformIO Home → Platforms → ESP32.

---

## 2.2 Upload fails
**Possible causes:**
- Wrong COM port  
- Bad USB cable  
- Board requires BOOT button  

**Solutions:**
- Select correct COM port  
- Try another cable  
- Hold **BOOT** during upload (if needed)  

---

## 2.3 Serial monitor shows unreadable characters
**Cause:**  
Wrong baud rate.

**Solution:**  
Set baud rate to **115200**.

---

## 2.4 Compilation errors
**Possible causes:**
- Missing libraries  
- Corrupted PlatformIO installation  
- Wrong environment selected  

**Solutions:**
- Reopen project  
- Delete `.pio` folder and rebuild  
- Ensure correct environment in `platformio.ini`  

---

# 3. WiFi Issues

## 3.1 Cannot find the WiFi Manager network
**Cause:**  
ESP32 already connected to a saved WiFi.

**Solutions:**
- Reset the ESP32  
- Clear WiFi credentials (if implemented)  
- Move closer to the ESP32  

---

## 3.2 Captive portal does not open
**Solution:**  
Open browser manually and go to:

```
http://192.168.4.1/
```

---

## 3.3 ESP32 does not connect to home/shop WiFi
**Possible causes:**
- Wrong password  
- 5 GHz network (ESP32 supports only 2.4 GHz)  
- Weak signal  

**Solutions:**
- Double‑check password  
- Ensure WiFi is 2.4 GHz  
- Move ESP32 closer to router  

---

# 4. Web Interface Issues

## 4.1 Interface not loading
**Solutions:**
- Try `http://totem.local`  
- Or use the ESP32 IP address  
- Clear browser cache  

---

## 4.2 Buttons in the UI do nothing
**Possible causes:**
- ESP32 disconnected from WiFi  
- Browser caching old scripts  

**Solutions:**
- Refresh page  
- Reboot ESP32  
- Check WiFi connection  

---

# 5. Animation Issues

## 5.1 Mode changes but LEDs do nothing
**Cause:**  
PWM not initialized or wrong GPIO mapping.

**Solution:**  
Check:

- `initTrafficLightPWM()`  
- `board_config.h`  

---

## 5.2 Animations are slow or laggy
**Cause:**  
Too many operations in the loop.

**Solution:**  
Ensure `updateMode()` is lightweight.

---

## 5.3 Wrong colors displayed
**Cause:**  
Red/Yellow/Green wires swapped.

**Solution:**  
Check wiring and mapping.

---

# 6. Buttons Issues

## 6.1 Button does nothing
**Possible causes:**
- Wrong GPIO  
- No pull‑up  
- Bad wiring  

**Solutions:**
- Use internal pull‑ups  
- Check wiring  
- Test with a simple button sketch  

---

## 6.2 Button triggers multiple times
**Cause:**  
Bounce effect.

**Solution:**  
Add software debounce (10–50 ms).

---

# 7. Advanced Debugging

## 7.1 Enable debug logs
Add debug prints in:

- `main.cpp`  
- `modes.cpp`  
- `light_helpers.cpp`  

Example:

```
Serial.println("Mode changed");
```

---

## 7.2 Check PWM values
Print values before writing:

```
Serial.println(value);
```

---

## 7.3 Check WiFi status
Use:

```
WiFi.status()
```

---

# 8. Summary

This troubleshooting guide covers:

- Hardware issues  
- Software issues  
- WiFi problems  
- Web interface issues  
- Animation problems  
- Button issues  
- Debugging techniques  

If a problem persists, check:

- Wiring  
- Power supply  
- `board_config.h`  
- Serial monitor logs  

Everything can be fixed with patience and method.
