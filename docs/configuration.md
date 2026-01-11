# Configuration Guide

**Valid from version 0.20.0 onwards**

## Overview

All user-configurable parameters are centralized in `include/config.h`. This guide walks you through each option and how to modify them for your setup.

## Quick Start

1. **Copy the template:**
   ```bash
   cp include/secrets_example.h include/secrets.h
   ```

2. **Edit `include/secrets.h`:**
   Add your WiFi networks (SSID, password).

3. **Edit `include/config.h`:**
   Customize mDNS name, HTTP port, OTA settings, and defaults.

4. **Compile and upload:**
   ```bash
   platformio run --environment esp32devkit --target upload
   ```

---

## Configuration Parameters (`config.h`)

### mDNS Name
```cpp
#define MDNS_NAME "Totem-Tabac"
```
- **Description:** The hostname used to access your device over the network.
- **Format:** Alphanumeric characters and hyphens only (no spaces).
- **Access URL:** `http://<MDNS_NAME>.local`
- **Example:** If set to `my-totem`, access via `http://my-totem.local`
- **Note:** Case-insensitive on most networks.

### HTTP Server Port
```cpp
#define HTTP_SERVER_PORT 80
```
- **Description:** Port for the web interface.
- **Default:** 80 (standard HTTP)
- **Advanced:** Change to 8080 if port 80 is occupied, then access via `http://<MDNS_NAME>.local:8080`

### OTA Configuration

#### OTA Port
```cpp
#define OTA_PORT 3232
```
- **Description:** Port used by ArduinoOTA for over-the-air firmware updates.
- **Default:** 3232 (standard ArduinoOTA port)
- **Usage:** PlatformIO uses this automatically; no manual action required.

#### OTA Hostname
```cpp
#define OTA_HOSTNAME "Totem-Tabac"
```
- **Description:** The name visible in PlatformIO OTA devices list.
- **Should match:** Your mDNS name for consistency.

#### OTA Password (Optional)
```cpp
// #define OTA_PASSWORD "totem2026"
```
- **Description:** Protects OTA updates with a password (optional).
- **Default:** Disabled (no password required).
- **To enable:** Uncomment the line and replace `totem2026` with your password.
- **Security:** Use a strong password if enabling.

### Display & Mode Defaults

#### Default Display Type
```cpp
#define DEFAULT_DISPLAY_TYPE DISPLAY_PWM
```
- **Options:**
  - `DISPLAY_PWM` (0) – Analog modules (default)
  - `DISPLAY_MATRIX` (1) – 8×8 LED matrix
- **Description:** Type of display active at power-on (persisted in NVS).

#### Default Mode
```cpp
#define DEFAULT_MODE 3  // MODE_PULSE_VERT
```
- **Mode codes:**
  - 0 = `MODE_AMBIANCE_DOUCE` (Soft Ambiance)
  - 1 = `MODE_VAGUE` (Wave)
  - 2 = `MODE_ARC_EN_CIEL` (Rainbow)
  - 3 = `MODE_PULSE_VERT` (Pulse Green) ← default
  - 4 = `MODE_PULSE_JAUNE` (Pulse Yellow)
  - 5 = `MODE_PULSE_ROUGE` (Pulse Red)
  - 6 = `MODE_RUSH` (Rush)
  - 7 = `MODE_K2000` (K2000 Scanner)
  - 8 = `MODE_JACKPOT`
  - 9 = `MODE_FDJ_WINNER`
  - 10 = `MODE_CLIENT_GAGNANT` (Client Won)
  - 11 = `MODE_CLIENT_PERDANT` (Client Lost)
  - 12 = `MODE_OUVERTURE` (Opening)
  - 13 = `MODE_FERMETURE` (Closing)
  - 14 = `MODE_PAUSE_CAFE` (Coffee Break)
  - 15 = `MODE_MAINTENANCE` (Maintenance)
  - 16 = `MODE_HUMEUR_PATRON` (Mood Color)

#### Matrix Brightness
```cpp
#define DEFAULT_MATRIX_BRIGHTNESS 200
```
- **Range:** 0–255
- **Description:** Default brightness for 8×8 matrix (PWM modules use their own PWM values).
- **200 (default):** Good balance between brightness and power consumption.
- **Adjustable via web UI:** Changes persist to NVS.

---

## WiFi Configuration (`secrets.h`)

**File location:** `include/secrets.h` (create from `secrets_example.h`)

```cpp
static const char* WIFI_NETWORKS[][2] = {
    {"SSID1", "PASSWORD1"},
    {"SSID2", "PASSWORD2"},
    {"SSID3", "PASSWORD3"},
};
```

- **Format:** Array of `{SSID, password}` pairs.
- **Connection order:** Device tries networks sequentially; connects to first available.
- **Security:** Never commit `secrets.h` to Git (protected by `.gitignore`).
- **Template file:** Always use `secrets_example.h` as reference.

---

## Access Your Device

### Web Interface
```
http://<MDNS_NAME>.local
```
- Example: `http://Totem-Tabac.local`
- Direct IP: `http://192.168.x.x` (shown in serial monitor on boot)

### OTA Update Page
```
http://<MDNS_NAME>.local/update
```
- Upload `.bin` firmware files directly from browser.

### API Endpoints
- `/status` – JSON device state
- `/mode?value=<N>` – Set mode
- `/display?value=<0|1>` – PWM (0) or Matrix (1)
- `/brightness?value=<0-255>` – Set matrix brightness
- `/submode` – Cycle speed submode

---

## Serial Monitor Output (Boot)

On power-up, you will see:
```
mDNS started: http://Totem-Tabac.local
IP: 192.168.1.100
Serveur HTTP démarré
OTA prêt
```

- **mDNS:** Confirms the hostname is accessible.
- **IP:** Direct IP address for manual access.
- **OTA prêt:** ArduinoOTA is ready for firmware updates.

---

## Troubleshooting

### Device not accessible via mDNS
- Confirm mDNS name in `config.h` (alphanumeric + hyphens only).
- Check serial output: should show `mDNS started: http://...`.
- Restart device and try after 30 seconds.
- Fallback: Use direct IP address from serial output.

### Port conflicts
- If port 80 is occupied on your network, change `HTTP_SERVER_PORT` to 8080 in `config.h`.
- Recompile and upload.
- Access via `http://<MDNS_NAME>.local:8080`

### Can't upload OTA
- Ensure device is powered and connected to WiFi.
- Check OTA hostname matches `OTA_HOSTNAME` in `config.h`.
- If password is enabled, confirm it in `config.h` (uncommented).
- Use PlatformIO: `platformio run --environment esp32devkit_ota --target upload`

---

## Next Steps

- [Getting Started](getting_started.md) – First-time setup guide
- [Hardware Setup](hardware_setup.md) – GPIO and component wiring
- [Modes Reference](modes_reference.md) – Detailed mode documentation
