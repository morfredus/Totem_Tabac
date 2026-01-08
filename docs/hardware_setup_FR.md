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

### Exemple de mapping (depuis board_config.h)

```
Module 0 :
  Rouge  → GPIO 13
  Jaune  → GPIO 26
  Vert   → GPIO 33

Module 1 :
  Rouge  → GPIO 14
  Jaune  → GPIO 27
  Vert   → GPIO 32

Module 2 :
  Rouge  → GPIO 16
  Jaune  → GPIO 17
  Vert   → GPIO 18

Module 3 :
  Rouge  → GPIO 19
  Jaune  → GPIO 21
  Vert   → GPIO 22
```

*(Votre mapping réel peut varier selon la carte ESP32.)*

---

# 4. Schéma de câblage (version texte)

```
ESP32 GPIO 13  → Module 0 Rouge (+)
ESP32 GPIO 26  → Module 0 Jaune (+)
ESP32 GPIO 33  → Module 0 Vert (+)

ESP32 GPIO 14  → Module 1 Rouge (+)
ESP32 GPIO 27  → Module 1 Jaune (+)
ESP32 GPIO 32  → Module 1 Vert (+)

ESP32 GPIO 16  → Module 2 Rouge (+)
ESP32 GPIO 17  → Module 2 Jaune (+)
ESP32 GPIO 18  → Module 2 Vert (+)

ESP32 GPIO 19  → Module 3 Rouge (+)
ESP32 GPIO 21  → Module 3 Jaune (+)
ESP32 GPIO 22  → Module 3 Vert (+)

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
