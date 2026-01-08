# ✅ **10 — `/docs/pwm_system_FR.md`**

```markdown
# Système PWM — Totem Feux du Tabac

Ce document explique le fonctionnement du système PWM (Pulse Width Modulation) utilisé dans **Totem Feux du Tabac**.  
Il couvre l’allocation des canaux, la fréquence, la résolution, les fonctions utilitaires et les bonnes pratiques pour créer des animations lumineuses fluides.

Ce guide s’adresse aussi bien aux débutants qu’aux utilisateurs avancés.

---

# 1. Qu’est‑ce que le PWM ?

Le PWM (modulation de largeur d’impulsion) permet de contrôler la luminosité d’une LED en allumant et éteignant le signal très rapidement.

- **0** = LED éteinte  
- **255** = LED à pleine puissance  
- Valeurs intermédiaires = niveaux de luminosité  

L’ESP32 génère ces signaux via le périphérique matériel **LEDC**.

---

# 2. Configuration PWM

Le projet utilise :

- **12 canaux PWM**
- **Résolution 8 bits** (0–255)
- **Fréquence 1 kHz**

### Pourquoi 8 bits ?

- Transitions suffisamment fluides  
- Calcul rapide  
- Compatible avec toutes les variantes ESP32  

### Pourquoi 1 kHz ?

- Aucun scintillement visible  
- Stable pour une utilisation continue  
- Fonctionne bien avec les modules LED  

---

# 3. Allocation des canaux

Chaque module de feu tricolore possède :

- 1 LED rouge  
- 1 LED jaune  
- 1 LED verte  

Total : **4 modules × 3 LEDs = 12 canaux**

```
RED_CH    = {0, 1, 2, 3}
YELLOW_CH = {4, 5, 6, 7}
GREEN_CH  = {8, 9, 10, 11}
```

Exemple :

```
Module 0 → canal rouge 0
Module 1 → canal rouge 1
Module 2 → canal rouge 2
Module 3 → canal rouge 3
```

---

# 4. Mapping GPIO

Chaque canal PWM est associé à un GPIO défini dans `board_config.h`.

Exemple :

```
TRAFFIC_LIGHTS[0].red    = GPIO 13
TRAFFIC_LIGHTS[0].yellow = GPIO 26
TRAFFIC_LIGHTS[0].green  = GPIO 33
```

Le mapping peut être modifié selon votre carte ESP32.

---

# 5. Initialisation

Le PWM est initialisé dans `initTrafficLightPWM()` :

- Configuration des 12 canaux  
- Association de chaque canal à son GPIO  
- Définition de la fréquence et de la résolution  

Pseudo‑code :

```
for each channel:
    ledcSetup(channel, 1000 Hz, 8 bits)
    ledcAttachPin(gpio, channel)
```

---

# 6. Fonctions utilitaires

Le système PWM est encapsulé dans `light_helpers.cpp`.

## 6.1 setRed(module, value)

Définit la luminosité de la LED rouge d’un module.

```
setRed(0, 255);  // pleine puissance
setRed(2, 128);  // demi puissance
```

## 6.2 setYellow(module, value)

Même principe pour la LED jaune.

## 6.3 setGreen(module, value)

Même principe pour la LED verte.

## 6.4 setRGB(module, r, y, g)

Définit les trois LEDs d’un module en une seule fonction.

```
setRGB(1, 255, 128, 0);
```

## 6.5 clearModule(module)

Éteint toutes les LEDs d’un module.

## 6.6 clearAll()

Éteint toutes les LEDs de tous les modules.

---

# 7. Moteur de fade

De nombreux modes utilisent un fade sinusoidal :

```
value = (sin(angle) + 1) * 127.5
```

Cela produit :

- Des transitions très fluides  
- Un effet naturel  
- Aucun “palier” visible  

Utilisé dans :

- Zen  
- Pulse  
- Vague  
- Transitions arc‑en‑ciel  

---

# 8. Timing et animation

Les animations utilisent :

- `millis()` pour le timing  
- `lastUpdate` pour contrôler la fréquence des frames  
- `animStep` pour suivre la progression  

Exemple :

```
if (now - lastUpdate > delayMs) {
    animStep++;
    lastUpdate = now;
}
```

---

# 9. Bonnes pratiques

### Utiliser clearAll() avant de dessiner une nouvelle frame  
Évite les résidus lumineux.

### Ne jamais écrire directement sur les GPIO  
Toujours utiliser les fonctions utilitaires.

### Garder les valeurs PWM entre 0 et 255  
Ne jamais dépasser 255.

### Utiliser les sous‑modes pour les variations de vitesse  
Code plus propre.

### Utiliser des courbes sinusoïdales pour les fades  
Les fades linéaires sont trop abrupts.

---

# 10. Étendre le système PWM

Pour ajouter une nouvelle LED ou un nouveau module :

1. Ajouter les nouveaux GPIO dans `board_config.h`  
2. Ajouter les nouveaux canaux PWM  
3. Mettre à jour `initTrafficLightPWM()`  
4. Ajouter des helpers si nécessaire  

Pour ajouter de nouvelles animations :

- Utiliser `setRed()`, `setYellow()`, `setGreen()`, `setRGB()`  
- Utiliser fades, vagues, patterns  
- Modifier `modes.cpp`  

---

# 11. Résumé

Le système PWM fournit :

- 12 canaux indépendants  
- Un contrôle fluide de la luminosité  
- Des fonctions utilitaires simples  
- Une architecture propre pour les animations  

Ce système est la base de tous les effets lumineux de **Totem Feux du Tabac**.
