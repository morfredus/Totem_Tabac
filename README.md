# Totem Feux du Tabac

## ⚡️ NeoPixel 8x8 Matrix (v0.20.0)

An open-source ESP32-based animated traffic-light system designed for French tobacco shops ("tabacs").

The project controls **4 physical traffic-light modules** (Red / Yellow / Green) using **12 PWM channels** and an **8x8 matrix**, offering 20+ lighting modes including K2000, rainbow, pulses, jackpot, FDJ animations, and more.

**What's new in v0.20.0:**
- Centralized configuration via `config.h` (user-modifiable parameters)
- mDNS hostname customization (default: `Totem-Tabac.local`)
- Customizable HTTP server port and OTA settings
- Comprehensive user documentation (Getting Started, Configuration guides)

---

## 🚀 Quick Start

1. **Clone and Setup**
   ```bash
   git clone https://github.com/fred-br/Totem_Tabac.git
   cd Totem_Tabac
   cp include/secrets_example.h include/secrets.h
   # Edit include/secrets.h with your WiFi credentials
   ```

2. **Customize (Optional)**
   - Edit `include/config.h` to change mDNS hostname, HTTP port, OTA settings, or display defaults
   - All parameters are well-documented with comments

3. **Compile & Upload**
   ```bash
   platformio run -e esp32devkit          # USB upload
   platformio run -e esp32devkit_ota -t upload  # OTA upload
   ```

4. **Access Web Interface**
   - Via mDNS: `http://totem-tabac.local` (or custom hostname from config.h)
   - Via IP: `http://<ESP32_IP>:80` (or custom port from config.h)

**Full Getting Started Guide:** See [docs/getting_started.md](docs/getting_started.md) (also available in French: [docs/getting_started_FR.md](docs/getting_started_FR.md))

---

## 🎨 Features

### 🔥 Lighting Modes (20+)
- Zen breathing
- Soft ambiance
- Wave
- Rainbow
- Rainbow Turbo
- Pulse Green / Yellow / Red (PWM fade)
- Rush
- K2000 (bidirectional)
- K2000 with light trail (Knight Rider effect)
- Disco
- Jackpot
- FDJ Winner
- Client Gagnant / Perdant
- Ouverture / Fermeture
- Pause Café
- Maintenance
- Humeur du Patron (6 colors)

### 🧠 Engine
- 12 PWM channels (4 modules × 3 colors)
- Smooth sinusoidal fading
- Bidirectional animations
- Sub-modes (speed, direction, variations)
- Auto-mode (opening/closing hours)

### 🌐 Web Interface
- Mode and sub-mode selection
- Live status monitoring
- WiFi configuration panel
- **Display selection**: PWM modules or 8x8 NeoPixel matrix (exclusive, persistent)
- **OTA Updates**: Professional web page at `/update` with progress bar

### 🌍 Network Access
- **mDNS Discovery**: Access device by name (e.g., `http://Totem-Tabac.local`)
- **Customizable Hostname**: Change `MDNS_NAME` in `include/config.h`
- **Optional Password Protection**: Secure OTA updates via `OTA_PASSWORD` in `include/config.h`

---

## 🟦 Display Selection (PWM or Matrix)

Since version 0.12.0-dev8x8, the firmware allows dynamic selection of the display system:

- **Classic PWM modules** (4 modules, 12 channels)
- **8x8 NeoPixel matrix** (simulates 3 traffic lights)

The choice is made via the web interface (radio button) and is automatically saved (persistent after reboot).

### 🟣 Soft Modes for Matrix (v0.19.0+)
- Ambiance: warm base + soft green breathing, full matrix
- Wave: green wave across the matrix
- Rainbow: vertical scrolling bands with vertical modulation
- Pulse Green/Yellow/Red: uniform breathing across full matrix

See [docs/modes_reference.md](docs/modes_reference.md) for animation details.

### 🔘 Physical Buttons
- Next Mode
- Next Sub-Mode

---

## ⚙️ Configuration

All user-modifiable parameters are centralized in `include/config.h`:

| Parameter | Default | Purpose |
|-----------|---------|---------|
| `MDNS_NAME` | "Totem-Tabac" | mDNS hostname (e.g., `totem-tabac.local`) |
| `HTTP_SERVER_PORT` | 80 | Web interface port |
| `OTA_HOSTNAME` | "Totem-Tabac" | Device name for OTA updates |
| `OTA_PORT` | 3232 | OTA protocol port |
| `OTA_PASSWORD` | (commented) | Optional password for OTA security |
| `DEFAULT_DISPLAY_TYPE` | PWM | Initial display (PWM or Matrix) |
| `DEFAULT_MODE` | 3 (Pulse Green) | Initial lighting mode |
| `DEFAULT_MATRIX_BRIGHTNESS` | 200 | Matrix LED brightness (0–255) |

**Full Configuration Guide:** See [docs/configuration.md](docs/configuration.md) (or [docs/configuration_FR.md](docs/configuration_FR.md) in French)

---

## 📦 Hardware Requirements

- **ESP32 DevKit** (multiple boards supported):
  - UPESY WROOM (Classic ESP32)
  - ESP32-S3 DevKitC-1 N16R8 (v0.11.3+)

- **4 × Traffic-light modules** (Red/Yellow/Green)
- **12 × PWM-compatible GPIOs**
- **2 × Buttons** (optional)
- **5V power supply**

Full wiring diagrams for each board: [docs/hardware_setup.md](docs/hardware_setup.md)

---

## 🛠️ Software Requirements

- PlatformIO
- Arduino framework
- ESP32 board support
- Dependencies listed in `platformio.ini`

Setup instructions: [docs/software_setup.md](docs/software_setup.md)

---

## 📚 Documentation

All documentation is available in **English and French** under `/docs/`:

| Document | Purpose |
|----------|---------|
| [getting_started.md](docs/getting_started.md) | 5-minute quick start for first-time users |
| [configuration.md](docs/configuration.md) | Complete configuration reference |
| [architecture.md](docs/architecture.md) | System design and code structure |
| [hardware_setup.md](docs/hardware_setup.md) | Wiring and hardware assembly |
| [modes_reference.md](docs/modes_reference.md) | Animation details and mode documentation |
| [software_setup.md](docs/software_setup.md) | Development environment setup |
| [faq.md](docs/faq.md) | Frequently asked questions |
| [troubleshooting.md](docs/troubleshooting.md) | Common issues and solutions |

French equivalents available with `_FR` suffix (e.g., `getting_started_FR.md`).

---

## 🧩 Project Structure

```
.
├── src/
│   ├── main.cpp
│   ├── modes.cpp
│   ├── light_helpers.cpp
│   └── wifi_manager.cpp
├── include/
│   ├── config.h              (← user-modifiable parameters)
│   ├── secrets.h             (← WiFi credentials, copy from secrets_example.h)
│   ├── secrets_example.h     (← template for WiFi setup)
│   ├── board_config.h
│   ├── light_helpers.h
│   ├── modes.h
│   ├── submode.h
│   ├── web_page.h
│   └── wifi_manager.h
├── docs/
│   ├── getting_started.md
│   ├── configuration.md
│   ├── architecture.md
│   ├── hardware_setup.md
│   ├── modes_reference.md
│   ├── software_setup.md
│   ├── faq.md
│   ├── troubleshooting.md
│   └── (French equivalents with _FR suffix)
├── platformio.ini
├── README.md
├── README_FR.md
├── CHANGELOG.md
└── CHANGELOG_FR.md
```

---

## 🔄 Firmware Updates

### USB Upload
```bash
platformio run -e esp32devkit
```

### OTA Upload (Over-The-Air)
```bash
platformio run -e esp32devkit_ota -t upload
```
Device must be on the network. Update status visible at `http://totem-tabac.local/update`.

---

## 📝 License

This project is licensed under the **MIT License**.  
See `LICENSE` for details.

---

## ❤️ Credits

Created by **Fred**, for his tobacco shop in France.  
Technical architecture, PWM engine, and documentation co-designed with GitHub Copilot.

---

## 🌐 Project Status

| Aspect | Status |
|--------|--------|
| Firmware | v0.20.0 (Stable) |
| Hardware | 4× PWM + 8×8 NeoPixel Matrix |
| Documentation | Complete (EN + FR) |
| Web Interface | Functional + OTA Support |
| Configuration | User-friendly (config.h) |
