# Démarrage Rapide — Intégration NeoPixel

## Quoi de Neuf en v0.12.0 ?

Le projet supporte maintenant les **modules NeoPixel RGB** comme alternative aux feux tricolores PWM traditionnels, **sans aucune modification de code** dans vos animations.

---

## Pour les Utilisateurs Restant en PWM (Par Défaut)

**Rien à faire !** Le système continue de fonctionner exactement comme avant. Tout le câblage et les configurations existants restent valides.

---

## Pour les Utilisateurs Passant aux NeoPixel

### 1. Configuration Matérielle
Remplacez vos modules de feux tricolores 3 fils par des modules NeoPixel :
- **Total :** 12 LEDs NeoPixel (WS2812B ou compatible) en bande adressable unique
- **Organisation :** 4 modules × 3 LEDs chacun (Module 0 : LEDs 0-2, Module 1 : LEDs 3-5, etc.)
- **Câblage :** **1 pin data** + 5V + GND pour les 12 LEDs (au lieu de 12 pins PWM avant)

### 2. Configuration Logicielle

#### Étape A : Définir le Pin dans `board_config.h`
Décommentez et configurez le pin data NeoPixel :

```cpp
// Pour ESP32 DevKit
#define NEOPIXEL_DATA_PIN    27

// Pour ESP32-S3
// #define NEOPIXEL_DATA_PIN    8
```

**Note :** Les NeoPixels sont adressables — un seul GPIO contrôle les 12 LEDs !

#### Étape B : Activer le Mode NeoPixel dans `platformio.ini`
Ajoutez le flag dans les `build_flags` de votre environnement :

```ini
[env:esp32devkit]
build_flags =
    ${env.build_flags}
    -D ENV_ESP32_DEVKIT
    -D USE_NEOPIXEL_LIGHTS    # Ajoutez cette ligne
```

#### Étape C : Compiler et Téléverser
```bash
pio run -e esp32devkit -t upload
```

---

## Avantages Clés

✅ **Câblage Extrêmement Simplifié :** 1 pin au lieu de 12 !  
✅ **Couleurs Plus Riches :** Contrôle RGB complet par LED  
✅ **Mêmes Animations :** Tous les modes fonctionnent identiquement  
✅ **Basculement Facile :** Ajoutez/retirez le flag pour changer de système  

---

## Documentation Complète

- [Guide Complet NeoPixel (FR)](docs/neopixel_integration_FR.md)
- [Complete NeoPixel Guide (EN)](docs/neopixel_integration.md)

---

## Résumé de l'Architecture

```
       Votre Code d'Animation
                  ↓
        TrafficLightManager
        (Interface Unifiée)
                  ↓
         ┌────────┴────────┐
         ↓                 ↓
   Système PWM      Système NeoPixel
   (12 canaux)       (1 pin data)
                    (Chaîne 12 LEDs)
```

**Le gestionnaire gère tout automatiquement selon votre choix à la compilation.**

---

## Dépannage

**Les LEDs ne fonctionnent pas ?**
1. Vérifiez l'alimentation (5V stable)
2. Vérifiez que les définitions de pins correspondent à votre câblage
3. Confirmez la présence du flag `-D USE_NEOPIXEL_LIGHTS`
4. Vérifiez les connexions de la ligne data

**Besoin de revenir au PWM ?**
1. Retirez `-D USE_NEOPIXEL_LIGHTS` de `platformio.ini`
2. Recompilez et téléversez

---

## Questions ?

Consultez la documentation complète ou ouvrez une issue sur le dépôt du projet.
