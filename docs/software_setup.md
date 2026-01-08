# Software Setup — Totem Feux du Tabac

This guide explains how to install, configure, and compile the firmware for the **Totem Feux du Tabac** project using PlatformIO.  
It is written for beginners and requires no prior experience with ESP32 development.

---

# 1. Required Software

You will need:

- **Visual Studio Code**  
  https://code.visualstudio.com/

- **PlatformIO IDE extension**  
  Install it from the VSCode marketplace.

- **Git** (optional but recommended)  
  https://git-scm.com/

---

# 2. Installing PlatformIO

1. Open **Visual Studio Code**  
2. Go to **Extensions**  
3. Search for **PlatformIO IDE**  
4. Click **Install**  
5. Restart VSCode

PlatformIO will automatically install all required toolchains.

---

# 3. Cloning or Downloading the Project

### Option A — Clone with Git

```
git clone https://github.com/yourusername/totem-feux-du-tabac.git
```

### Option B — Download ZIP

1. Go to your GitHub repository  
2. Click **Code → Download ZIP**  
3. Extract the folder

---

# 4. Opening the Project in PlatformIO

1. Open VSCode  
2. Click **PlatformIO Home** (left sidebar)  
3. Choose **Open Project**  
4. Select the project folder  
5. Wait for PlatformIO to install dependencies

---

# 5. Understanding platformio.ini

The project uses a unified configuration supporting:

- ESP32 DevKit (WROOM)
- ESP32‑S3 DevKitC‑1 N16R8
- ESP32‑S3 N8R8

Key settings include:

```
framework = arduino
monitor_speed = 115200
upload_speed = 921600
board_build.partitions = huge_app.csv
build_flags = -std=gnu++17
```

Dependencies include:

- Adafruit NeoPixel  
- Adafruit BusIO  
- Adafruit GFX  
- Adafruit ST7735/ST7789  
- TinyGPSPlus  
- U8g2  

---

# 6. Compiling the Firmware

To compile:

1. Open the project in VSCode  
2. Click the **checkmark icon** (Build) in the bottom bar  
3. Wait for compilation to finish

If everything is correct, you will see:

```
SUCCESS: Build complete
```

---

# 7. Uploading the Firmware to the ESP32

1. Connect the ESP32 via USB  
2. Click the **arrow icon** (Upload)  
3. PlatformIO will compile (if needed) and upload  
4. The ESP32 will reboot automatically

If upload fails:

- Try another USB cable  
- Press and hold **BOOT** during upload (some boards require it)  
- Select the correct COM port in PlatformIO

---

# 8. Serial Monitor

To view logs:

1. Click the **plug icon** (Monitor)  
2. Set baud rate to **115200**  
3. You will see:

```
[INFO] Totem Feux du Tabac starting...
[INFO] WiFi Manager ready
[INFO] Current mode: 0
```

---

# 9. WiFi Setup

The ESP32 starts in **WiFi Manager mode** on first boot.

1. Connect to the WiFi network:  
   **Totem-Feux-Setup**

2. A captive portal opens automatically  
   If not, go to:  
   http://192.168.4.1/

3. Select your home/shop WiFi  
4. Enter password  
5. ESP32 reboots and connects

You can now access the interface at:

```
http://totem.local
```

or via its IP address.

---

# 10. File Structure Overview

```
/src
  main.cpp          → Program entry point
  modes.cpp         → All lighting animations
  light_helpers.cpp → PWM abstraction layer

/include
  board_config.h    → GPIO mapping
  light_helpers.h   → LED control API

/docs
  (documentation)

/platformio.ini     → Build configuration
```

---

# 11. Troubleshooting

### PlatformIO cannot find the board  
→ Install ESP32 platform manually from PlatformIO Home.

### Upload fails  
→ Hold BOOT during upload.  
→ Try another USB cable.

### Serial monitor shows garbage  
→ Wrong baud rate (must be 115200).

### WiFi Manager does not appear  
→ Reset the ESP32.  
→ Clear saved WiFi credentials (hold BOOT 5 seconds if implemented).

---

# 12. Summary

You now know how to:

- Install PlatformIO  
- Open the project  
- Compile the firmware  
- Upload it to the ESP32  
- Configure WiFi  
- Use the serial monitor  

Your software environment is ready.
