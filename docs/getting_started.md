# Getting Started

**Valid from version 0.20.0 onwards**

Welcome to **Totem Feux du Tabac** – an intelligent LED animation system for retail storefronts. This guide helps you get up and running in 5 minutes.

## What You Have

- **Totem Tabac Firmware** (v0.20.0+)
- **ESP32 DevKit** microcontroller
- **LED display** (PWM modules or 8×8 NeoPixel matrix)
- **Web interface** accessible over WiFi
- **OTA updates** (firmware uploads via network)

---

## 1. Hardware Assembly (5 min)

### Wiring Checklist
- [ ] Solder/connect GPIO pins per `docs/hardware_setup.md`
- [ ] Connect power supply (5V recommended)
- [ ] Verify all LED connections

**GPIO Reference** (see `include/board_config.h`):
- Button 1: GPIO 0 (next mode)
- Button 2: GPIO 35 (next submode)
- PWM/LEDs: See hardware guide
- Matrix data: GPIO 14 (WS2812B)

---

## 2. Prepare Firmware

### Install PlatformIO
```bash
pip install platformio
```

### Clone or Download
```bash
git clone <repository>
cd Totem_Tabac
```

### Setup Secrets
```bash
cp include/secrets_example.h include/secrets.h
```
Edit `include/secrets.h` and add your WiFi networks:
```cpp
static const char* WIFI_NETWORKS[][2] = {
    {"YourSSID", "YourPassword"},
    {"SecondWiFi", "SecondPassword"},
};
```

### (Optional) Customize Config
Edit `include/config.h` to adjust:
- mDNS name: `#define MDNS_NAME "Totem-Tabac"`
- HTTP port: `#define HTTP_SERVER_PORT 80`
- Default mode/brightness

---

## 3. Upload Firmware

### Via USB (First Time)
```bash
platformio run --environment esp32devkit --target upload
```

### Via OTA (After WiFi Connected)
```bash
platformio run --environment esp32devkit_ota --target upload
```

### Monitor Serial Output
```bash
platformio device monitor
```

Expected output:
```
mDNS started: http://Totem-Tabac.local
IP: 192.168.1.100
Serveur HTTP démarré
OTA prêt
```

---

## 4. Access Your Device

### Web Interface
Open in your browser:
```
http://Totem-Tabac.local
```

Or use the direct IP (from serial monitor):
```
http://192.168.1.100
```

### Features You'll See
- **Mode selector** – Soft, dynamic, utility modes
- **Display toggle** – PWM modules or 8×8 matrix
- **Brightness slider** – Adjust LED intensity
- **Speed controls** – Speed submodes for soft modes
- **Color picker** – Mood color (Humeur du Patron)
- **OTA update** – Upload new firmware from browser

---

## 5. First Use

### Initial Power-On
1. Device connects to first known WiFi
2. Serial monitor shows IP and mDNS URL
3. Default mode: Pulse Green (PWM modules)
4. Default brightness: 200/255

### Navigation
- **Physical buttons:**
  - Button 1 (GPIO 0): Cycle modes
  - Button 2 (GPIO 35): Cycle speed submodes
- **Web UI:**
  - Click mode buttons to switch instantly
  - Adjust brightness with slider
  - Changes persist across reboots

---

## 6. Advanced: Modes Overview

| Mode | Code | Type | Speeds? |
|------|------|------|---------|
| Ambiance Douce | 0 | Soft | ✓ |
| Vague (Wave) | 1 | Soft | ✓ |
| Arc-en-ciel (Rainbow) | 2 | Soft | ✓ |
| Pulse Vert | 3 | Soft | ✓ |
| Pulse Jaune | 4 | Soft | ✓ |
| Pulse Rouge | 5 | Soft | ✓ |
| Rush | 6 | Dynamic | ✗ |
| K2000 Scanner | 7 | Dynamic | ✓ |
| Jackpot | 8 | Dynamic | ✗ |
| FDJ Winner | 9 | Dynamic | ✗ |
| Client Gagnant | 10 | Utility | ✗ |
| Client Perdant | 11 | Utility | ✗ |
| Ouverture (Opening) | 12 | Utility | ✗ |
| Fermeture (Closing) | 13 | Utility | ✗ |
| Pause Café | 14 | Utility | ✗ |
| Maintenance | 15 | Utility | ✗ |
| Humeur du Patron | 16 | Utility | ✗ |

See [Modes Reference](modes_reference.md) for detailed descriptions.

---

## 7. Network & Security

### mDNS (Zero-Config Networking)
Your device is automatically discoverable as:
```
Totem-Tabac.local
```
Change the name in `include/config.h`.

### WiFi Networks
Add multiple networks in `include/secrets.h`; device connects to the first available.

### OTA Password (Optional)
Uncomment in `include/config.h` to require a password for OTA updates:
```cpp
#define OTA_PASSWORD "your_secure_password"
```

---

## 8. Troubleshooting

| Issue | Solution |
|-------|----------|
| Device not showing in WiFi | Check `secrets.h`; verify SSID and password |
| Can't access `http://Totem-Tabac.local` | Use direct IP from serial monitor |
| Web UI slow/laggy | Restart device; check WiFi signal |
| OTA upload fails | Ensure device is powered and on same WiFi |
| LEDs not lighting | Check GPIO wiring; verify power supply |
| Buttons unresponsive | Check GPIO 0 and 35 connections |

---

## Next Steps

- [Configuration Guide](configuration.md) – Detailed parameter reference
- [Hardware Setup](hardware_setup.md) – GPIO and component wiring
- [Modes Reference](modes_reference.md) – All animation details
- [FAQ](faq.md) – Common questions and answers
- [Troubleshooting](troubleshooting.md) – Advanced debugging

---

## Quick Reference

| Command | Purpose |
|---------|---------|
| `platformio run --environment esp32devkit --target upload` | Upload via USB |
| `platformio run --environment esp32devkit_ota --target upload` | Upload via WiFi (OTA) |
| `platformio device monitor` | View serial logs |
| `http://Totem-Tabac.local/update` | Manual firmware upload page |

---

**Enjoy your Totem Feux du Tabac! 🎉**

For support, check [FAQ](faq.md) or [Troubleshooting](troubleshooting.md).
