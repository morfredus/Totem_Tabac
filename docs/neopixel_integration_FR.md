# Guide d'Intégration NeoPixel

## Vue d'Ensemble

À partir de la version **0.12.0**, le projet Totem Feux du Tabac supporte les **modules NeoPixel** comme alternative aux feux tricolores PWM traditionnels. Cette amélioration apporte :

- 🎨 **Contrôle des couleurs enrichi** avec capacités RGB
- ⚡ **Câblage drastiquement simplifié** (1 pin au lieu de 12 !)
- 🔄 **Transition transparente** du PWM vers NeoPixel sans modification du code
- 🧩 **Interface unifiée** pour les deux systèmes d'éclairage

**Avantage Clé :** Les NeoPixels sont **adressables** — un seul GPIO contrôle les 12 LEDs en chaîne (4 modules × 3 LEDs chacun).

---

## Architecture

### Gestionnaire de Feux Tricolores

Le système utilise un **gestionnaire unifié** (`TrafficLightManager`) qui gère les feux PWM et NeoPixel de manière transparente. Toutes les animations et modes existants fonctionnent identiquement quel que soit le type de feux utilisé.

```
┌─────────────────────────────────────┐
│    TrafficLightManager              │
│  (Interface Unifiée)                │
└──────────────┬──────────────────────┘
               │
      ┌────────┴────────┐
      │                 │
┌─────▼─────┐   ┌──────▼──────────┐
│  Mode PWM │   │  Mode NeoPixel  │
│           │   │                 │
│ 12 pins   │   │ 1 pin seul !   │
│ (3/module)│   │ (Chaîne 12 LEDs)│
└───────────┘   └─────────────────┘
```

### Composants Clés

#### 1. Classe **TrafficLightManager** (Système Unifié)
Située dans `include/traffic_light_manager.h` et `src/traffic_light_manager.cpp`

Fournit un contrôle unifié sur les 4 modules de feux tricolores en utilisant **un seul strip NeoPixel** de 12 LEDs adressables, sélectionnant automatiquement entre PWM et NeoPixel selon la configuration à la compilation.

**Organisation des LEDs :**
- Module 0 : LEDs 0, 1, 2 (Rouge, Jaune, Vert)
- Module 1 : LEDs 3, 4, 5 (Rouge, Jaune, Vert)
- Module 2 : LEDs 6, 7, 8 (Rouge, Jaune, Vert)
- Module 3 : LEDs 9, 10, 11 (Rouge, Jaune, Vert)

**Méthodes Principales :**
```cpp
void begin();                               // Initialiser tous les modules
void setRed(int module, uint8_t value);     // Contrôler module 0-3
void setYellow(int module, uint8_t value);
void setGreen(int module, uint8_t value);
void setRGB(int module, bool r, bool y, uint8_t g);
void clearModule(int module);               // Éteindre un module
void clearAll();                            // Éteindre tous les modules
```

#### 2. **Light Helpers** (Couche de Compatibilité)
Situés dans `include/light_helpers.h` et `src/light_helpers.cpp`

Fonctions wrapper qui redirigent les appels vers le gestionnaire unifié, assurant la rétrocompatibilité avec le code d'animation existant.

---

## Configuration Matérielle

### Spécifications des Modules NeoPixel

Le système complet se compose de :
- **12 LEDs NeoPixel** (WS2812B ou compatible) en un seul strip adressable
- **Configuration :** NEO_GRB + NEO_KHZ800
- **Connexion :** Pin data unique + 5V + GND
- **Organisation :** 4 modules de 3 LEDs chacun, contrôlés par adressage

### Câblage

#### Option 1 : Feux Tricolores PWM (Par Défaut)
Système actuel utilisant 3 pins par module (rouge, jaune, vert) tel que défini dans `board_config.h`.

#### Option 2 : Modules NeoPixel
Nécessite seulement **1 pin data** pour les 12 LEDs. À configurer dans `board_config.h` :

```cpp
// Exemple pour ESP32 DevKit
#define NEOPIXEL_DATA_PIN    27

// Exemple pour ESP32-S3
#define NEOPIXEL_DATA_PIN    8
```

**Câblage :**
```
ESP32 GPIO 27 ──► DATA (première LED)
5V ─────────────► VCC (toutes LEDs)
GND ────────────► GND (toutes LEDs)

Chaîne LEDs : LED0 → LED1 → LED2 → ... → LED11
(Chaque flèche est la connexion DOUT→DIN entre LEDs)
```

---

## Configuration Logicielle

### Étape 1 : Définir le Pin NeoPixel

Éditez `include/board_config.h` et décommentez/définissez le pin data NeoPixel pour votre carte :

```cpp
// Décommentez et configurez selon votre carte
#define NEOPIXEL_DATA_PIN    27
```

**Note :** Un SEUL pin est nécessaire pour les 12 LEDs !

### Étape 2 : Activer le Mode NeoPixel

Éditez `platformio.ini` et ajoutez le flag `USE_NEOPIXEL_LIGHTS` :

```ini
[env:esp32devkit]
platform = espressif32
board = esp32dev

build_flags =
    ${env.build_flags}
    -D ENV_ESP32_DEVKIT
    -D USE_NEOPIXEL_LIGHTS    # Ajoutez cette ligne
```

### Étape 3 : Compiler et Téléverser

```bash
pio run -e esp32devkit -t upload
```

---

## Basculer Entre les Systèmes

Pour revenir au mode PWM :

1. Commentez ou supprimez `-D USE_NEOPIXEL_LIGHTS` de `platformio.ini`
2. Recompilez et téléversez

**Aucune modification du code nécessaire !** Le gestionnaire sélectionne automatiquement le système approprié à la compilation.

---

## Rendu des Couleurs

### LED Jaune en Mode NeoPixel

Le jaune est rendu comme un mélange RGB pour approximer le jaune chaud des LEDs traditionnelles :
- **Rouge :** 100% de la valeur de luminosité
- **Vert :** ~70% de la valeur de luminosité (ratio 180/255)
- **Bleu :** 0%

Cela produit un jaune d'aspect naturel sans être trop vert.

### Contrôle de la Luminosité

Chaque module NeoPixel supporte un contrôle de luminosité globale (0-255) en plus du contrôle d'intensité par LED, permettant un réglage fin de la sortie lumineuse.

---

## Compatibilité des Animations

Toutes les animations existantes fonctionnent identiquement avec les modules NeoPixel :

- ✅ **Modes pulse** (vert, jaune, rouge)
- ✅ **Effet vague**
- ✅ **Scanner K2000**
- ✅ **Arc-en-ciel turbo**
- ✅ **Effet jackpot**
- ✅ **Effets gagnant/perdant**
- ✅ **Tous les modes de statut**

L'interface unifiée garantit que les animations appellent les mêmes fonctions indépendamment du matériel sous-jacent.

---

## Dépannage

### Les LEDs Ne S'Allument Pas

1. **Vérifiez l'alimentation :** Les NeoPixels nécessitent une alimentation 5V stable
2. **Vérifiez les pins :** Assurez-vous que les définitions `NEOPIXEL_PIN_x` correspondent à votre câblage
3. **Vérifiez le flag :** Confirmez que `-D USE_NEOPIXEL_LIGHTS` est dans `platformio.ini`
4. **Vérifiez le câblage :** La ligne data doit se connecter au GPIO défini

### Mauvaises Couleurs

1. **Vérifiez l'ordre des LEDs :** Par défaut NEO_GRB ; ajustez dans `traffic_light_neopixel.cpp` si nécessaire
2. **Vérifiez le type de module :** WS2812B vs SK6812 peuvent avoir des ordres de couleurs différents

### Scintillement

1. **Ajoutez un condensateur :** 1000µF entre 5V et GND près des NeoPixels
2. **Vérifiez l'alimentation :** Une alimentation insuffisante peut causer l'instabilité
3. **Ajoutez une résistance :** 330Ω en série avec la ligne data

---

## Détails Techniques

### Utilisation Mémoire

- **Mode PWM :** ~200 octets statiques + canaux
- **Mode NeoPixel :** ~500 octets pour Adafruit_NeoPixel (strip unique de 12 LEDs)

### Performance

- **PWM :** Contrôle matériel direct, aucune charge CPU
- **NeoPixel :** ~30µs par mise à jour LED via bit-banging

Les deux systèmes fournissent des animations fluides ; choisissez selon vos préférences matérielles.

---

## Référence API

### Instance Globale

```cpp
extern TrafficLightManager trafficLights;
```

Utilisez cette instance globale dans tout votre code.

### Exemple d'Utilisation

```cpp
#include "traffic_light_manager.h"

void setup() {
    trafficLights.begin();  // Initialiser le système
    trafficLights.clearAll();
}

void loop() {
    // Mettre le module 0 en rouge complet
    trafficLights.setRed(0, 255);
    delay(1000);
    
    // Mettre le module 1 en jaune moyen
    trafficLights.setYellow(1, 128);
    delay(1000);
    
    // Tout éteindre
    trafficLights.clearAll();
    delay(1000);
}
```

---

## Historique des Versions

- **0.12.0** (Janvier 2026) : Support NeoPixel ajouté avec architecture de gestionnaire unifié
- **0.11.x** : Système PWM uniquement

---

## Voir Aussi

- [Guide de Configuration Matérielle](hardware_setup_FR.md)
- [Référence des Modes](modes_reference_FR.md)
- [Documentation Système PWM](pwm_system_FR.md)
- [Vue d'Ensemble de l'Architecture](architecture_FR.md)
