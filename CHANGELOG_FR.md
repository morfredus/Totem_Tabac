# Journal des modifications — Totem Feux du Tabac
Toutes les évolutions importantes du projet sont documentées ici.

Le projet suit le schéma **Semantic Versioning (SemVer)** :  
**MAJEUR.MINEUR.CORRECTIF**

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
