# .copilot: Suivi des évolutions — Branche dev/8x8
# Fichier : CHANGELOG_FR.md
# Version projet : 0.12.0-dev8x8
# Dernière modif : 2026-01-10
# Auteur : Fred & Copilot
# - Journal des modifications synchronisé avec README, hardware_setup, platformio.ini (FR/EN)
# - Ajout matrice NeoPixel 8x8, mapping feux, GPIO, doc synchronisée
# Branche active : dev/8x8
# Historique :
#   - v0.12.0-dev8x8 : Ajout matrice NeoPixel 8x8, mapping feux, doc synchronisée
#   - v0.11.x et antérieures : PWM modules classiques uniquement
#
## [0.12.0-dev8x8] – Intégration matrice NeoPixel 8x8 (2026-01-10)
### Ajouté
- Prise en charge d'une matrice NeoPixel 8x8 (adresses 0–63, haut en bas, gauche à droite)
- Simulation de 3 feux tricolores sur la matrice (rouge, jaune, vert pour chaque feu)
- Sélection sécurisée du GPIO pour la matrice selon l'environnement (voir board_config.h)
- Documentation utilisateur (FR/EN) mise à jour : mapping, câblage, utilisation
- Version projet passée à 0.12.0-dev8x8
### Modifié
- Règles .copilot appliquées : chaque évolution est versionnée, documentée et synchronisée (FR/EN)
- README, guides hardware et changelogs mis à jour pour la matrice

#
## [0.11.3] – Nouveau mapping GPIO ESP32-S3 (2026-01-09)
### Modifié
- Mise à jour du mapping GPIO pour l'environnement `esp32s3_n16r8` (ESP32-S3 DevKitC-1 N16R8) :
  - Module 0 : Rouge 1, Jaune 2, Vert 42
  - Module 1 : Rouge 41, Jaune 40, Vert 39
  - Module 2 : Rouge 4, Jaune 5, Vert 6
  - Module 3 : Rouge 7, Jaune 15, Vert 16
  - Boutons : 21 (mode), 20 (sous-mode)
- Tous les documents utilisateur (FR + EN) ont été mis à jour pour refléter ce mapping et garantir la cohérence avec le code source.

# Journal des modifications — Totem Feux du Tabac
Toutes les évolutions importantes du projet sont documentées ici.

Le projet suit le schéma **Semantic Versioning (SemVer)** :  
**MAJEUR.MINEUR.CORRECTIF**

---

## [0.11.2] – Corrections anti-bootloop ESP32-S3 (2026-01-09)
### Corrigé
- **Problème critique de bootloop sur ESP32-S3** causé par le choix de GPIO non sécurisés.
- GPIO 1, 2 maintenant évités (UART0).
- GPIO 0 maintenant évité (risque bouton boot).
- GPIO 45, 46 maintenant évités (strapping pins).
- GPIO 26-32 maintenant évités (input-only sur S3).

### Modifié
- Mapping GPIO ESP32-S3 mise à jour vers GPIO 3-16 (100% sécurisé pour PWM).
- Nouveau mapping : Module 1 (GPIO 3-5), Module 2 (GPIO 6-8), Module 3 (GPIO 9-11), Module 4 (GPIO 12-14), Boutons (GPIO 15-16).
- Documentation mise à jour pour refléter l'allocation réelle des GPIO.

### Impact utilisateur
- ESP32-S3 maintenant stable sans risque de bootloop.
- Le câblage matériel doit utiliser GPIO 3-16 pour les LEDs.

---

## [0.11.1] – Nettoyage des noms d'environnements (2026-01-09)
### Modifié
- Environnement renommé de `upesy_wroom` à `esp32devkit` pour la clarté.
- Spécification de la carte changée à `esp32doit-devkit1` (board standard PlatformIO).
- Flag de compilation changé de `-D ENV_ESP32_CLASSIC` à `-D ENV_ESP32_DEVKIT`.

---

## [0.11.0] – Stabilisation de l'architecture multi-environnements (2026-01-09)
### Ajouté
- Section commune `[env]` dans `platformio.ini` pour partager la configuration.
- Système d'héritage basé sur les flags (`${env.build_flags}`, `${env.lib_deps}`).
- Décodeur d'exceptions pour le débogage ESP32-S3.

### Modifié
- `platformio.ini` restructuré pour une meilleure maintenabilité.
- Les deux environnements héritent maintenant des paramètres communs.
- Environnement par défaut défini sur `esp32devkit`.

---

## [0.10.0] – Refactorisation de la configuration GPIO (2026-01-09)
### Ajouté
- Nouvelle section de configuration commune `[env]` dans `platformio.ini`.
- Toutes les dépendances centralisées dans la section commune.
- Flags de compilation et vitesses de monitoring unifiés.

### Modifié
- `esp32devkit` et `esp32s3_n16r8` héritent maintenant de `[env]`.
- Réduction de la duplication de configuration.
- Structure de projet plus propre et maintenable.

---

## [0.9.0] – Architecture multi-environnements (2026-01-09)
### Ajouté
- **Nouvel environnement ESP32-S3 DevKitC-1 N16R8** avec support PSRAM.
- Section `[env]` commune dans `platformio.ini` pour mutualiser les dépendances et flags.
- Système de mapping GPIO multi-environnements dans `board_config.h`.
- Flag de compilation `-D ENV_UPESY_WROOM` et `-D ENV_ESP32S3_N16R8` pour sélection automatique du mapping.
- Mapping GPIO sécurisé pour ESP32-S3 (GPIO 1-14) évitant les GPIO sensibles au boot et USB/JTAG.
- Librairies complètes ajoutées : Adafruit BusIO, GFX, ST7735/ST7789, TinyGPSPlus, U8g2.

### Modifié
- Restructuration complète de `platformio.ini` avec héritage des configurations communes.
- `board_config.h` maintenant avec deux mappings distincts protégés par `#ifdef`.
- Mapping UPESY_WROOM conservé strictement à l'identique (aucune modification).
- Version incrémentée de 0.8.0 → 0.9.0.

### Impact utilisateur
- Le projet compile désormais pour deux cartes ESP32 différentes.
- Possibilité de choisir l'environnement via PlatformIO : `upesy_wroom` ou `esp32s3_n16r8`.
- Aucun impact sur le comportement des modes lumineux existants.

### Impact développeur
- Ajout de nouveaux environnements facilité via la section `[env]` commune.
- Mapping GPIO modulaire et extensible.
- Meilleure organisation du code avec séparation claire des configurations matérielles.

---

## [0.8.0] – Effet K2000 avec traînée lumineuse (2026-01-08)
### Ajouté
- Nouveau mode **K2000 avec “queue lumineuse”** utilisant le PWM pour créer une traînée réaliste.
- Balayage fluide aller‑retour (0→3→0) avec intensités dégressives.
- Compatibilité totale avec les sous‑modes (lent / normal / rapide).

### Modifié
- Réécriture complète du mode K2000 pour supprimer le redémarrage brutal à gauche.

---

## [0.7.0] – Balayage K2000 bidirectionnel (2026-01-08)
### Ajouté
- Animation K2000 réelle : gauche → droite → gauche.
- Gestion des vitesses via sous‑modes.

---

## [0.6.0] – Réécriture complète du système PWM (2026-01-08)
### Ajouté
- Nouveau système PWM complet pour 12 canaux (4 modules × 3 couleurs).
- Nouvelles fonctions :
  - `setRed(module, value)`
  - `setYellow(module, value)`
  - `setGreen(module, value)`
  - `setRGB(module, r, y, g)`
  - `clearModule()`, `clearAll()`
  - `initTrafficLightPWM()`

### Supprimé
- Anciennes versions booléennes de `setRed()` et `setYellow()`.

---

## [0.5.0] – Refonte des modes Pulse (2026-01-08)
### Ajouté
- Vrais fades PWM pour :
  - **Pulse Rouge**
  - **Pulse Jaune**
  - **Pulse Vert**

### Corrigé
- Suppression des faux pulses basés sur le vert.
- Unification du moteur de fade sinus.

---

## [0.4.0] – Nouveau mapping GPIO sécurisé (2026-01-08)
### Ajouté
- Nouveau mapping GPIO compatible PWM pour ESP32 DevKit.
- 12 GPIO dédiés aux feux tricolores.
- 2 GPIO dédiés aux boutons physiques.

---

## [0.3.0] – Ajout des boutons Web (2026-01-08)
### Ajouté
- Deux nouveaux boutons dans l’interface web :
  - **Mode suivant**
  - **Sous‑mode suivant**
- Ajout des routes HTTP `/nextmode` et `/nextsub`.

---

## [0.2.0] – Extension du système de modes (2026-01-08)
### Ajouté
- Ajout de tous les modes principaux :
  - Zen  
  - Ambiance Douce  
  - Vague  
  - Arc‑en‑Ciel  
  - Pulse Vert / Jaune / Rouge  
  - Rush  
  - K2000  
  - Disco  
  - Jackpot  
  - FDJ Winner  
  - Client Gagnant  
  - Client Perdant  
  - Ouverture / Fermeture  
  - Pause Café  
  - Maintenance  
  - Arc‑en‑Ciel Turbo  
  - Humeur du Patron  

---

## [0.1.0] – Première logique de contrôle (2026-01-08)
### Ajouté
- Première version de `modes.cpp`.
- Première version de l’interface web.
- Contrôle basique des LED.

---

## [0.0.0] – Début du projet (2026-01-08)
### Ajouté
- Initialisation du projet.
- Définition de l’architecture et des objectifs.
