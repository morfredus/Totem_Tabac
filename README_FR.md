# Totem Feux du Tabac

## ⚡️ Matrice NeoPixel 8x8 (v0.20.0)

Un système de feu tricolore animé basé sur ESP32, conçu pour les bureaux de tabac français ("tabacs").

Le projet contrôle **4 modules de feu tricolore physiques** (Rouge / Orange / Vert) en utilisant **12 canaux PWM** et une **matrice 8x8**, offrant 20+ modes d'éclairage incluant K2000, arc-en-ciel, pulsations, jackpot, animations FDJ, et plus.

**Nouveautés de la v0.20.0 :**
- Configuration centralisée via `config.h` (paramètres modifiables par l'utilisateur)
- Personnalisation du nom d'hôte mDNS (par défaut : `Totem-Tabac.local`)
- Ports serveur HTTP et OTA configurables
- Documentation utilisateur complète (Démarrage rapide, Guides de configuration)

---

## 🚀 Démarrage Rapide

1. **Cloner et Configurer**
   ```bash
   git clone https://github.com/fred-br/Totem_Tabac.git
   cd Totem_Tabac
   cp include/secrets_example.h include/secrets.h
   # Éditer include/secrets.h avec vos identifiants WiFi
   ```

2. **Personnaliser (Optionnel)**
   - Éditer `include/config.h` pour changer le nom mDNS, le port HTTP, les paramètres OTA, ou les paramètres d'affichage par défaut
   - Tous les paramètres sont bien documentés avec des commentaires

3. **Compiler et Télécharger**
   ```bash
   platformio run -e esp32devkit          # Téléchargement USB
   platformio run -e esp32devkit_ota -t upload  # Téléchargement OTA
   ```

4. **Accéder à l'Interface Web**
   - Via mDNS : `http://totem-tabac.local` (ou le nom d'hôte personnalisé de config.h)
   - Via IP : `http://<IP_ESP32>:80` (ou le port personnalisé de config.h)

**Guide Complet de Démarrage :** Voir [docs/getting_started_FR.md](docs/getting_started_FR.md) (aussi disponible en anglais : [docs/getting_started.md](docs/getting_started.md))

---

## 🎨 Fonctionnalités

### 🔥 Modes d'Éclairage (20+)
- Respiration zen
- Ambiance douce
- Vague
- Arc-en-ciel
- Arc-en-ciel turbo
- Pulsation Rouge / Orange / Vert (fade PWM)
- Rush
- K2000 (bidirectionnel)
- K2000 avec traîne de lumière (effet Knight Rider)
- Disco
- Jackpot
- FDJ Gagnant
- Client Gagnant / Perdant
- Ouverture / Fermeture
- Pause Café
- Maintenance
- Humeur du Patron (6 couleurs)

### 🧠 Moteur
- 12 canaux PWM (4 modules × 3 couleurs)
- Fade sinusoïdal lisse
- Animations bidirectionnelles
- Sous-modes (vitesse, direction, variations)
- Mode automatique (heures d'ouverture/fermeture)

### 🌐 Interface Web
- Sélection de mode et sous-mode
- Monitoring du statut en direct
- Panneau de configuration WiFi
- **Sélection d'affichage** : modules PWM ou matrice NeoPixel 8x8 (exclusif, persistant)
- **Mises à Jour OTA** : page web professionnelle à `/update` avec barre de progression

### 🌍 Accès Réseau
- **Découverte mDNS** : accès par le nom (ex. `http://Totem-Tabac.local`)
- **Nom d'Hôte Personnalisable** : changer `MDNS_NAME` dans `include/config.h`
- **Protection Optionnelle par Mot de Passe** : sécuriser les mises à jour OTA via `OTA_PASSWORD` dans `include/config.h`

---

## 🟦 Sélection d'Affichage (PWM ou Matrice)

Depuis la version 0.12.0-dev8x8, le firmware permet la sélection dynamique du système d'affichage :

- **Modules PWM classiques** (4 modules, 12 canaux)
- **Matrice NeoPixel 8x8** (simule 3 feux tricolores)

Le choix se fait via l'interface web (bouton radio) et est automatiquement sauvegardé (persistant après redémarrage).

### 🟣 Modes Doux pour la Matrice (v0.19.0+)
- Ambiance : base chaude + respiration verte douce, matrice complète
- Vague : vague verte à travers la matrice
- Arc-en-ciel : bandes verticales avec modulation verticale
- Pulsation Rouge/Orange/Vert : respiration uniforme sur la matrice complète

Voir [docs/modes_reference_FR.md](docs/modes_reference_FR.md) pour les détails des animations.

### 🔘 Boutons Physiques
- Prochain Mode
- Prochain Sous-Mode

---

## ⚙️ Configuration

Tous les paramètres modifiables par l'utilisateur sont centralisés dans `include/config.h` :

| Paramètre | Défaut | Objectif |
|-----------|--------|---------|
| `MDNS_NAME` | "Totem-Tabac" | Nom d'hôte mDNS (ex. `totem-tabac.local`) |
| `HTTP_SERVER_PORT` | 80 | Port de l'interface web |
| `OTA_HOSTNAME` | "Totem-Tabac" | Nom de l'appareil pour les mises à jour OTA |
| `OTA_PORT` | 3232 | Port du protocole OTA |
| `OTA_PASSWORD` | (commenté) | Mot de passe optionnel pour la sécurité OTA |
| `DEFAULT_DISPLAY_TYPE` | PWM | Affichage initial (PWM ou Matrice) |
| `DEFAULT_MODE` | 3 (Pulsation Vert) | Mode d'éclairage initial |
| `DEFAULT_MATRIX_BRIGHTNESS` | 200 | Luminosité des LEDs matrice (0–255) |

**Guide Complet de Configuration :** Voir [docs/configuration_FR.md](docs/configuration_FR.md) (ou [docs/configuration.md](docs/configuration.md) en anglais)

---

## 📦 Composants Matériels

- **ESP32 DevKit** (plusieurs cartes supportées) :
  - UPESY WROOM (ESP32 classique)
  - ESP32-S3 DevKitC-1 N16R8 (v0.11.3+)

- **4 × Modules de feu tricolore** (Rouge/Orange/Vert)
- **12 × GPIO compatibles PWM**
- **2 × Boutons** (optionnel)
- **Alimentation 5V**

Schémas de câblage complets pour chaque carte : [docs/hardware_setup_FR.md](docs/hardware_setup_FR.md)

---

## 🛠️ Logiciels Requis

- PlatformIO
- Framework Arduino
- Support des cartes ESP32
- Dépendances listées dans `platformio.ini`

Instructions de configuration : [docs/software_setup_FR.md](docs/software_setup_FR.md)

---

## 📚 Documentation

Toute la documentation est disponible en **français et anglais** sous `/docs/` :

| Document | Objectif |
|----------|---------|
| [getting_started_FR.md](docs/getting_started_FR.md) | Démarrage rapide en 5 minutes pour les nouveaux utilisateurs |
| [configuration_FR.md](docs/configuration_FR.md) | Référence de configuration complète |
| [architecture_FR.md](docs/architecture_FR.md) | Design du système et structure du code |
| [hardware_setup_FR.md](docs/hardware_setup_FR.md) | Câblage et assemblage matériel |
| [modes_reference_FR.md](docs/modes_reference_FR.md) | Détails des animations et documentation des modes |
| [software_setup_FR.md](docs/software_setup_FR.md) | Configuration de l'environnement de développement |
| [faq_FR.md](docs/faq_FR.md) | Questions fréquemment posées |
| [troubleshooting_FR.md](docs/troubleshooting_FR.md) | Problèmes courants et solutions |

Les équivalents en anglais sont disponibles sans suffixe `_FR` (ex. `getting_started.md`).

---

## 🧩 Structure du Projet

```
.
├── src/
│   ├── main.cpp
│   ├── modes.cpp
│   ├── light_helpers.cpp
│   └── wifi_manager.cpp
├── include/
│   ├── config.h              (← paramètres modifiables par l'utilisateur)
│   ├── secrets.h             (← identifiants WiFi, copier depuis secrets_example.h)
│   ├── secrets_example.h     (← modèle pour la configuration WiFi)
│   ├── board_config.h
│   ├── light_helpers.h
│   ├── modes.h
│   ├── submode.h
│   ├── web_page.h
│   └── wifi_manager.h
├── docs/
│   ├── getting_started_FR.md
│   ├── configuration_FR.md
│   ├── architecture_FR.md
│   ├── hardware_setup_FR.md
│   ├── modes_reference_FR.md
│   ├── software_setup_FR.md
│   ├── faq_FR.md
│   ├── troubleshooting_FR.md
│   └── (équivalents en anglais sans suffixe _FR)
├── platformio.ini
├── README.md
├── README_FR.md
├── CHANGELOG.md
└── CHANGELOG_FR.md
```

---

## 🔄 Mises à Jour du Firmware

### Téléchargement USB
```bash
platformio run -e esp32devkit
```

### Téléchargement OTA (Over-The-Air)
```bash
platformio run -e esp32devkit_ota -t upload
```
L'appareil doit être connecté au réseau. Statut de mise à jour visible à `http://totem-tabac.local/update`.

---

## 📝 Licence

Ce projet est sous licence **MIT**.  
Voir `LICENSE` pour les détails.

---

## ❤️ Crédits

Créé par **Fred**, pour son bureau de tabac en France.  
Architecture technique, moteur PWM et documentation co-conçus avec GitHub Copilot.

---

## 🌐 Statut du Projet

| Aspect | Statut |
|--------|--------|
| Firmware | v0.20.0 (Stable) |
| Matériel | 4× PWM + Matrice NeoPixel 8×8 |
| Documentation | Complète (FR + EN) |
| Interface Web | Fonctionnelle + Support OTA |
| Configuration | Conviviale (config.h) |
