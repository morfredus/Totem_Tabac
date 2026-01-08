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

- ESP32 DevKit (WROOM ou S3)
- 4 × modules de feux tricolores
- 12 × GPIO compatibles PWM
- 2 × boutons (optionnel)
- Alimentation 5V

Les schémas de câblage sont disponibles dans `/docs/hardware_setup_FR.md`.

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
- `/docs/modes_reference_FR.md`

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
