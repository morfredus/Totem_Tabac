# Architecture du projet — Totem Feux du Tabac

Ce document présente une vue d’ensemble complète de l’architecture interne du projet **Totem Feux du Tabac**.  
Il explique comment le firmware est structuré, comment les modules interagissent, et comment l’ESP32 contrôle les 4 feux tricolores via le PWM.

Ce document est conçu pour être accessible aux débutants, tout en restant utile aux développeurs avancés.

---

# 1. Vue d’ensemble

Totem Feux du Tabac repose sur quatre couches principales :

```
+------------------------------------------------------+
|                 Interface Web                        |
+------------------------------------------------------+
|                 Moteur de Modes                      |
+------------------------------------------------------+
|           Couche de Contrôle Lumineux                |
+------------------------------------------------------+
|             Couche Matérielle / GPIO                 |
+------------------------------------------------------+
```

### Interface Web  
Permet de changer de mode, sous‑mode, et configurer le WiFi.

### Moteur de Modes  
Contient toutes les animations (K2000, Arc‑en‑ciel, Pulse, etc.).

### Couche de Contrôle Lumineux  
Abstraction du PWM pour les 12 LEDs.

### Couche Matérielle  
Définit le mapping GPIO et le câblage physique.

---

# 2. Structure du dépôt

```
/src
  main.cpp
  modes.cpp
  light_helpers.cpp

/include
  board_config.h
  light_helpers.h

/docs
  (fichiers de documentation)

/platformio.ini
/README_FR.md
/CHANGELOG_FR.md
```

---

# 3. Architecture du firmware

## 3.1 main.cpp

`main.cpp` gère :

- L’initialisation du matériel  
- L’initialisation des canaux PWM  
- Le WiFi Manager  
- Les interruptions des boutons physiques  
- La boucle principale  
- L’appel à `updateMode()` à chaque frame  

### Responsabilités

```
setup():
  - initLights()
  - clearAll()
  - initWiFiManager()
  - attacher les interruptions
  - définir le mode par défaut

loop():
  - updateMode()
```

---

## 3.2 modes.cpp

Contient toutes les animations lumineuses.

Chaque mode est implémenté dans un grand `switch(mode)`.

### Responsabilités

- Gérer le mode courant  
- Gérer les sous‑modes (vitesse, variations)  
- Implémenter la logique d’animation  
- Utiliser les helpers PWM  
- Gérer le timing (`lastUpdate`, `animStep`)  

### Exemples de modes

- Zen  
- Pulse Rouge / Jaune / Vert  
- Arc‑en‑ciel  
- K2000 bidirectionnel  
- K2000 avec traînée lumineuse  
- Jackpot  
- FDJ Winner  
- Client Gagnant / Perdant  
- Ouverture / Fermeture  
- Maintenance  

---

## 3.3 light_helpers.cpp / .h

Cette couche abstrait tout le contrôle LED.

### Responsabilités

- Initialiser les canaux PWM  
- Fournir des fonctions simples :  
  - `setRed(module, value)`  
  - `setYellow(module, value)`  
  - `setGreen(module, value)`  
  - `clearModule()`  
  - `clearAll()`  
- Fournir un helper RGB :  
  - `setRGB(module, r, y, g)`  
- Garantir un usage sécurisé des GPIO  

Les modes ne manipulent jamais les GPIO directement.

---

## 3.4 board_config.h

Définit tous les éléments matériels :

- Mapping GPIO pour 4 modules × 3 couleurs  
- Pins des boutons  
- Numéros de canaux PWM  
- Notes de sécurité (pins sensibles au boot)  

### Support multi-environnements (v0.11.0+)

Depuis la version 0.11.0, `board_config.h` gère **plusieurs cartes ESP32** via un système de macros conditionnelles.

Le mapping GPIO approprié est automatiquement sélectionné lors de la compilation en fonction du flag `-D ENV_xxx` défini dans `platformio.ini`.

#### Structure du fichier :

```cpp
#ifdef ENV_ESP32_DEVKIT
    // Mapping pour ESP32 classique (DevKit)
    #define TL1_RED 4
    #define TL1_YELLOW 5
    // ...
#endif

#ifdef ENV_ESP32S3_N16R8
    // Mapping pour ESP32-S3 DevKitC-1 N16R8 (v0.11.2+)
    #define TL1_RED 3
    #define TL1_YELLOW 4
    // ...
#endif

// Structure commune
struct TrafficLightPins { int red, yellow, green; };
static const TrafficLightPins TRAFFIC_LIGHTS[4] = { ... };
```

#### Environnements supportés :

**1. ENV_ESP32_DEVKIT (ESP32 classique)**

- Environnement : `esp32devkit`
- Mapping éprouvé et validé
- GPIO 4, 5, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23
- Boutons : GPIO 25, 26


**2. ENV_ESP32S3_N16R8 (ESP32-S3 DevKitC-1) — v0.11.3+**

- Environnement : `esp32s3_n16r8`
- Nouveau mapping sécurisé (conforme firmware 0.11.3)
- GPIO :
  - Module 0 : Rouge 1, Jaune 2, Vert 42
  - Module 1 : Rouge 41, Jaune 40, Vert 39
  - Module 2 : Rouge 4, Jaune 5, Vert 6
  - Module 3 : Rouge 7, Jaune 15, Vert 16
- Boutons : GPIO 21 (mode), 20 (sous-mode)

Exemple (ESP32 DevKit) :

```
TRAFFIC_LIGHTS[0].red    = GPIO 4
TRAFFIC_LIGHTS[0].yellow = GPIO 5
TRAFFIC_LIGHTS[0].green  = GPIO 12
```

Exemple (ESP32-S3 N16R8 v0.11.3+) :

```
TRAFFIC_LIGHTS[0].red    = GPIO 1
TRAFFIC_LIGHTS[0].yellow = GPIO 2
TRAFFIC_LIGHTS[0].green  = GPIO 42
```

---

# 4. Architecture PWM

Chaque LED est contrôlée via un PWM 8 bits (0–255).

### Canaux PWM

```
RED_CH    = {0, 1, 2, 3}
YELLOW_CH = {4, 5, 6, 7}
GREEN_CH  = {8, 9, 10, 11}
```

Chaque module possède :

- 1 LED rouge  
- 1 LED jaune  
- 1 LED verte  

Total : **12 canaux PWM**

---

# 5. Architecture du moteur de modes

Chaque mode suit ce schéma :

```
if (now - lastUpdate > delayMs) {
    clearAll();
    // dessiner la frame
    lastUpdate = now;
}
```

### Sous‑modes

Les sous‑modes permettent :

- Variations de vitesse  
- Variations de direction  
- Variations de couleur  
- Effets spéciaux  

Exemple :

```
subMode 0 = lent
subMode 1 = normal
subMode 2 = rapide
```

---

# 6. Architecture de l’interface Web

L’ESP32 héberge un mini serveur HTTP.

### Routes

- `/` → interface principale  
- `/nextmode` → mode suivant  
- `/nextsub` → sous‑mode suivant  
- `/status` → statut JSON  
- `/wifi` → configuration WiFi  

### Fonctionnalités

- Sélection du mode  
- Sélection du sous‑mode  
- Aperçu en direct  
- Configuration WiFi  

---

# 7. Boutons physiques

Deux boutons sont connectés :

- Bouton 1 → Mode suivant  
- Bouton 2 → Sous‑mode suivant  

Gérés via interruptions pour une réactivité immédiate.

---

# 8. Étendre le projet

Pour ajouter un mode :

1. Ajouter une constante dans `modes.h`  
2. Ajouter un `case` dans `updateMode()`  
3. Utiliser les helpers PWM  
4. Ajouter le support dans l’UI (optionnel)  

Pour ajouter du matériel :

- Modifier `board_config.h`  
- Adapter `initLights()` si nécessaire  

---

# 9. Résumé

Totem Feux du Tabac repose sur une architecture claire et modulaire :

- `main.cpp` → orchestration  
- `modes.cpp` → animations  
- `light_helpers` → abstraction PWM  
- `board_config` → matériel  
- Interface Web → contrôle à distance  

Cette structure rend le projet :

- Facile à comprendre  
- Facile à étendre  
- Accessible aux débutants  
- Robuste et maintenable  
