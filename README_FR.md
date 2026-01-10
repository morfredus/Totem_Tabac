# Totem Feux du Tabac
Projet open‑source basé sur ESP32 permettant d’animer **4 modules de feux tricolores** (Rouge / Jaune / Vert) avec plus de 20 modes lumineux : K2000, arc‑en‑ciel, pulses, jackpot, animations FDJ, etc.

Le projet inclut :
- Firmware complet ESP32 (PlatformIO)
- Moteur LED PWM
- Système de modes avancé
- Interface Web
- Boutons physiques
- Documentation complète (FR + EN)

Licence : **MIT License**

---

## 🚀 Fonctionnalités

### 🔥 Modes lumineux (20+)
- Respiration Zen
- Ambiance douce
- Vague
- Arc‑en‑ciel
- Arc‑en‑ciel Turbo
- Pulse Vert / Jaune / Rouge (fade PWM)
- Rush
- K2000 bidirectionnel
- K2000 avec traînée lumineuse (effet Knight Rider)
- Disco
- Jackpot
- FDJ Winner
- Client Gagnant / Perdant
- Ouverture / Fermeture
- Pause Café
- Maintenance
- Humeur du Patron (6 couleurs)

### 🧠 Moteur interne
- 12 canaux PWM (4 modules × 3 couleurs)
- Fades sinus ultra fluides
- Animations bidirectionnelles
- Sous‑modes (vitesse, direction)
- Auto‑mode (heures d’ouverture/fermeture)

### 🌐 Interface Web
- Sélection du mode
- Sélection du sous‑mode
- Statut en direct
- Configuration WiFi

### 🔘 Boutons physiques
- Mode suivant
- Sous‑mode suivant

---

## 📦 Matériel nécessaire

- **ESP32 DevKit** (plusieurs modèles supportés) :
  - UPESY WROOM (ESP32 classique)
  - ESP32-S3 DevKitC-1 N16R8 (avec PSRAM)
- **4 × modules de feux tricolores** (choisir un système) :
  - **LEDs PWM** (par défaut) : 3 pins par module (Rouge/Jaune/Vert) = 12 pins total
  - **Modules NeoPixel** (v0.12.0+) : **1 pin data pour tous** (chaîne de 12 LEDs adressables)
- 12 × GPIO compatibles PWM
  - ESP32-S3 DevKitC-1 N16R8 (v0.11.3+) :
    - Module 0 : Rouge 1, Jaune 2, Vert 42
    - Module 1 : Rouge 41, Jaune 40, Vert 39
    - Module 2 : Rouge 4, Jaune 5, Vert 6
    - Module 3 : Rouge 7, Jaune 15, Vert 16
    - Boutons : GPIO 21 (mode), 20 (sous-mode)
- 2 × boutons (optionnel)
- Alimentation 5V

🎆 **NOUVEAU en v0.12.0 :** Support NeoPixel ! Basculez facilement entre LEDs PWM traditionnelles (12 pins) et NeoPixel (1 seul pin !). Voir `/docs/neopixel_integration_FR.md` pour les détails.

Les schémas de câblage pour chaque carte sont disponibles dans `/docs/hardware_setup_FR.md`.

---

## 🛠️ Logiciels nécessaires

- PlatformIO
- Framework Arduino
- Support ESP32
- Dépendances listées dans `platformio.ini`

Instructions détaillées dans `/docs/software_setup_FR.md`.

---

## 📚 Documentation

Toute la documentation est disponible dans `/docs/` en français et en anglais.

Points d’entrée recommandés :
- `/docs/architecture_FR.md`
- `/docs/hardware_setup_FR.md`
- `/docs/modes_reference_FR.md`- `/docs/neopixel_integration_FR.md` ⭐ NOUVEAU : Support des modules NeoPixel
---

## 🧩 Structure du projet

/src
main.cpp
modes.cpp
light_helpers.cpp
/include
board_config.h
light_helpers.h
/docs
(documentation complète)
/platformio.ini
/README_FR.md
/CHANGELOG_FR.md

---

## 📝 Licence

Projet sous licence **MIT**.  
Voir `LICENSE` pour les détails.

---

## ❤️ Crédits

Créé par **Fred**, pour son bureau de tabac en France.  
Architecture technique, moteur PWM et documentation co‑conçus avec Copilot.
