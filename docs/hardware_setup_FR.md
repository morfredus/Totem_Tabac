# Installation matérielle — Totem Feux du Tabac

Ce guide explique comment câbler et assembler le matériel du projet **Totem Feux du Tabac**.  
Il est conçu pour être accessible aux débutants, sans connaissances préalables en électronique.

---

# 1. Composants nécessaires

## Obligatoires
- 1 × ESP32 DevKit (WROOM ou S3)
- 4 × modules de feux tricolores (Rouge / Jaune / Vert)
- 12 × GPIO compatibles PWM
- 1 × alimentation 5V (2A recommandé)
- Fils Dupont
- Breadboard ou borniers

## Optionnels
- 2 × boutons poussoirs (Mode / Sous‑mode)
- Résistances 10kΩ (si pull‑ups externes nécessaires)
- Boîtier imprimé en 3D
- Support rail DIN

---

# 2. Comprendre les modules de feux tricolores

Chaque module contient :

- 1 LED rouge  
- 1 LED jaune  
- 1 LED verte  

Chaque LED possède :

- 1 anode (positif)
- 1 cathode (négatif)

L’ESP32 contrôle chaque LED via **PWM** (luminosité 0–255).

---

# 3. Mapping GPIO

Le projet utilise **12 GPIO** pour les 4 modules.

```
Module 0 → Rouge / Jaune / Vert
Module 1 → Rouge / Jaune / Vert
Module 2 → Rouge / Jaune / Vert
Module 3 → Rouge / Jaune / Vert
```

## 3.1 Support multi-environnements (v0.11.0+)

Depuis la version 0.11.0, le projet supporte **deux cartes ESP32** avec des mappings GPIO différents.

Le mapping est automatiquement sélectionné lors de la compilation selon l'environnement PlatformIO choisi.

### Mapping A : ESP32 DevKit (ESP32 classique)

**Environnement PlatformIO :** `esp32devkit`  
**Board :** esp32doit-devkit1

```
Module 0 :
  Rouge  → GPIO 4
  Jaune  → GPIO 5
  Vert   → GPIO 12

Module 1 :
  Rouge  → GPIO 13
  Jaune  → GPIO 14
  Vert   → GPIO 16

Module 2 :
  Rouge  → GPIO 17
  Jaune  → GPIO 18
  Vert   → GPIO 19

Module 3 :
  Rouge  → GPIO 21
  Jaune  → GPIO 22
  Vert   → GPIO 23

Boutons :
  Mode      → GPIO 25
  Sous-mode → GPIO 26
```


### Mapping B : ESP32-S3 DevKitC-1 N16R8 (v0.11.3+)

**Environnement PlatformIO :** `esp32s3_n16r8`  
**Board :** esp32-s3-devkitc-1

⚠️ **Mise à jour 0.11.3** : Nouveau mapping GPIO conforme au firmware.

```
Module 0 :
  Rouge  → GPIO 1
  Jaune  → GPIO 2
  Vert   → GPIO 42

Module 1 :
  Rouge  → GPIO 41
  Jaune  → GPIO 40
  Vert   → GPIO 39

Module 2 :
  Rouge  → GPIO 4
  Jaune  → GPIO 5
  Vert   → GPIO 6

Module 3 :
  Rouge  → GPIO 7
  Jaune  → GPIO 15
  Vert   → GPIO 16

Boutons :
  Mode      → GPIO 21
  Sous-mode → GPIO 20
```

**Note :** Ce mapping évite les GPIO dangereux :
- ✗ GPIO 0, 1, 2 : Boot/UART0
- ✗ GPIO 45, 46 : Strapping pins
- ✗ GPIO 26-32 : Input-only
- ✓ GPIO 3-16 : 100% PWM safe

---

# 4. Schéma de câblage (version texte)

Utilisez le schéma correspondant à votre carte ESP32 (voir section 3 pour les mappings).

### Pour ESP32 DevKit (esp32devkit) :

```
ESP32 GPIO 4   → Module 0 Rouge (+)
ESP32 GPIO 5   → Module 0 Jaune (+)
ESP32 GPIO 12  → Module 0 Vert (+)

ESP32 GPIO 13  → Module 1 Rouge (+)
ESP32 GPIO 14  → Module 1 Jaune (+)
ESP32 GPIO 16  → Module 1 Vert (+)

ESP32 GPIO 17  → Module 2 Rouge (+)
ESP32 GPIO 18  → Module 2 Jaune (+)
ESP32 GPIO 19  → Module 2 Vert (+)

ESP32 GPIO 21  → Module 3 Rouge (+)
ESP32 GPIO 22  → Module 3 Jaune (+)
ESP32 GPIO 23  → Module 3 Vert (+)

ESP32 GPIO 25  → Bouton Mode
ESP32 GPIO 26  → Bouton Sous-mode

TOUTES LES CATHODES (–) → GND
ESP32 GND               → GND alimentation
```


### Pour ESP32-S3 DevKitC-1 N16R8 (esp32s3_n16r8) — v0.11.3+ :

```
ESP32 GPIO 1   → Module 0 Rouge (+)
ESP32 GPIO 2   → Module 0 Jaune (+)
ESP32 GPIO 42  → Module 0 Vert (+)

ESP32 GPIO 41  → Module 1 Rouge (+)
ESP32 GPIO 40  → Module 1 Jaune (+)
ESP32 GPIO 39  → Module 1 Vert (+)

ESP32 GPIO 4   → Module 2 Rouge (+)
ESP32 GPIO 5   → Module 2 Jaune (+)
ESP32 GPIO 6   → Module 2 Vert (+)

ESP32 GPIO 7   → Module 3 Rouge (+)
ESP32 GPIO 15  → Module 3 Jaune (+)
ESP32 GPIO 16  → Module 3 Vert (+)

ESP32 GPIO 21  → Bouton Mode
ESP32 GPIO 20  → Bouton Sous-mode

TOUTES LES CATHODES (–) → GND
ESP32 GND               → GND alimentation
```

---

# 5. Alimentation du système

### Option A — Alimentation via USB  
Idéal pour les tests.

### Option B — Alimentation externe 5V  
Recommandée pour l’installation finale.

**Important :**  
Tous les GND doivent être reliés ensemble :

```
ESP32 GND ↔ LED GND ↔ GND alimentation
```

---

# 6. Câblage des boutons

Deux boutons sont utilisés :

- Bouton 1 → Mode suivant  
- Bouton 2 → Sous‑mode suivant  

### Câblage

```
Bouton → GPIO (ex : 0 ou 35)
Bouton → GND
```

Les pull‑ups internes de l’ESP32 sont utilisés.

---

# 7. Notes de sécurité

- Évitez les GPIO 34–39 pour le PWM (entrée uniquement).
- Évitez les GPIO 0, 2, 15 au boot sauf si nécessaire.
- Toujours relier tous les GND ensemble.
- Ne jamais alimenter les LEDs via le 3.3V de l’ESP32.
- Utiliser une alimentation 5V stable pour une installation durable.

---

# 8. Dépannage

### LED toujours allumée  
→ Polarité inversée

### LED qui scintille  
→ Masse commune manquante

### ESP32 qui redémarre  
→ Alimentation insuffisante

### PWM inactif  
→ GPIO non compatible PWM

---

# 9. Résumé

Vous avez maintenant :

- L’ESP32 câblé aux 4 modules de feux  
- 12 canaux PWM connectés  
- Les boutons optionnels installés  
- Une alimentation stable et sécurisée  

Votre matériel est prêt pour le firmware.
