# Référence des modes — Totem Feux du Tabac

Ce document décrit tous les modes lumineux disponibles dans **Totem Feux du Tabac**.  
Il explique le comportement de chaque mode, son objectif, et les sous‑modes associés.

Ce guide est conçu pour être clair et accessible, même pour un débutant.

---

# 1. Vue d'ensemble

Le système inclut **16 modes lumineux**, regroupés en catégories :

- Modes d'ambiance (2 modes)
- Mode Arc-en-ciel (1 mode)
- Modes Pulse (3 modes)
- Animations dynamiques (3 modes)
- Effets spéciaux (2 modes)
- Modes fonctionnels (4 modes)
- Mode humeur (1 mode)

Chaque mode peut être sélectionné via :

- L'interface Web  
- Le bouton physique (Mode suivant)  
- Les routes API  

Les sous‑modes permettent de varier la vitesse, la direction ou les effets.

---

# 2. Modes d'ambiance

## 2.1 Éclairage Doux (Ambiance Douce)
**Index : 0**

Cycle de couleurs doux et progressif.

- Transitions légères entre vert et jaune
- Atmosphère relaxante et chaleureuse
- Animation douce en continu

**Pas de sous‑modes**

---

## 2.2 Vague
**Index : 1**

Une vague lumineuse verte qui traverse les 4 modules.

- Activation séquentielle des modules
- Effet apaisant et fluide
- Mouvement constant de gauche à droite

**Pas de sous‑modes**

---

# 3. Mode Arc‑en‑ciel

## 3.1 Arc‑en‑ciel
**Index : 2**

Cycle RGB dynamique et coloré.

- Rotation complète des couleurs de l'arc-en-ciel
- Modules décalés pour effet de vague
- 6 couleurs : Rouge, Jaune, Vert, Cyan, Violet, Blanc

**Sous‑modes :**  
- 0 = Normal (120 ms entre les étapes)
- 1 = Turbo (60 ms entre les étapes)

---

# 4. Modes Pulse (PWM)

Ces modes utilisent un **fade PWM réel** pour une respiration douce et fluide.

## 4.1 Pulse Vert  
**Index : 3**

Respiration verte sinusoïdale sur tous les modules.

**Sous‑modes :**  
- 0 = Lent 🐢 (40 ms par step)
- 1 = Normal 🚶 (20 ms par step)
- 2 = Rapide 🏃 (10 ms par step)

---

## 4.2 Pulse Jaune  
**Index : 4**

Respiration jaune sinusoïdale sur tous les modules.

**Sous‑modes :**  
- 0 = Lent 🐢 (40 ms par step)
- 1 = Normal 🚶 (20 ms par step)
- 2 = Rapide 🏃 (10 ms par step)

---

## 4.3 Pulse Rouge  
**Index : 5**

Respiration rouge sinusoïdale sur tous les modules.

**Sous‑modes :**  
- 0 = Lent 🐢 (40 ms par step)
- 1 = Normal 🚶 (20 ms par step)
- 2 = Rapide 🏃 (10 ms par step)

---

# 5. Animations dynamiques

## 5.1 Rush
**Index : 6**

Effet de clignotement rouge rapide et énergique.

- Flashs rouges synchronisés sur tous les modules
- Animation très dynamique
- Idéal pour attirer l'attention ou période de rush

**Pas de sous‑modes**

---

## 5.2 K2000 (Bidirectionnel)
**Index : 7**

Effet Knight Rider classique avec point lumineux blanc et traînée.

- Point principal blanc intense (255)
- Traînée lumineuse derrière (150 puis 60)
- Mouvement bidirectionnel fluide
- Inversion automatique aux extrémités

**Sous‑modes :**  
- 0 = Avant ➡️ (150 ms par step)
- 1 = Arrière ⬅️ (80 ms par step)
- Note : Le sous-mode 2 accélère davantage (40 ms)

---

## 5.3 Jackpot
**Index : 8**

Effet "machine à sous" très festif.

- Couleurs RGB aléatoires qui changent rapidement
- Flash blanc complet toutes les 8 étapes
- Animation continue et énergique

**Sous‑modes :**  
- 0 = Lent 🐢 (150 ms par step)
- 1 = Normal 🚶 (100 ms par step)
- 2 = Rapide 🏃 (60 ms par step)

---

# 6. Effets spéciaux

## 6.1 Gagnant 🎉
**Index : 9**

Animation de célébration complète qui fusionne l'ancien FDJ Winner et Client Gagnant.

**Déroulement en 4 phases :**

1. **Phase 1** (étapes 0-7) : Clignotement jaune rapide et festif
   - Alternance jaune plein / éteint à 90 ms
   
2. **Phase 2** (étapes 8-15) : Vague verte montante
   - Point vert qui monte avec traînée
   - Effet de progression vers le haut
   
3. **Phase 3** (étapes 16-27) : Couleurs aléatoires lumineuses
   - RGB aléatoire dans les valeurs hautes (200-255)
   - Effet très festif et énergique
   
4. **Phase 4** (étapes 28+) : Vert stable final
   - Tous les modules en vert fixe
   - Confirmation de la victoire

**Caractéristiques :**
- Plus festif que l'ancien FDJ Winner seul
- Moins intense et plus long que Jackpot
- Animation complète et satisfaisante
- Durée totale : environ 2,5 secondes

**Pas de sous‑modes**

---

# 7. Modes interaction client

## 7.1 Client Perdant
**Index : 10**

Flashs rouges avec jaune intermittent pour indiquer une perte.

- Rouge fixe en continu
- Jaune qui clignote en alternance
- Animation claire mais pas agressive
- Délai de 180 ms entre les changements

**Pas de sous‑modes**

---

# 8. Modes fonctionnels

## 8.1 Ouverture
**Index : 11**

Signal d'ouverture du commerce.

- Vert fixe sur tous les modules
- Signal clair et accueillant
- Visible de loin

---

## 8.2 Fermeture
**Index : 12**

Signal de fermeture du commerce.

- Rouge fixe sur tous les modules
- Signal clair de fermeture
- Visible de loin

---

## 8.3 Pause Café
**Index : 13**

Indication d'une pause temporaire.

- Jaune fixe en continu
- Vert qui clignote toutes les 300 ms
- Signal clair mais pas urgent

---

## 8.4 Maintenance
**Index : 14**

Signal de maintenance technique.

- Cycle complet de 6 couleurs
- Rouge → Jaune → Vert → Blanc → Violet → Bleu
- Changement toutes les 250 ms
- Signal technique et visible

---

# 9. Mode humeur

## 9.1 Humeur du Patron
**Index : 15**

Mode fun représentant l'humeur du patron sur le module 4 uniquement.

**Couleurs disponibles (sélectionnables via l'interface web) :**

- 0 = Heureux 😊 (vert)
- 1 = Calme 😌 (jaune)
- 2 = Énervé 😡 (rouge)
- 3 = Serein 😇 (bleu)
- 4 = Créatif 🎨 (violet)
- 5 = Neutre 😐 (blanc)

**Note :** Seul le module 4 (le plus haut) est allumé dans ce mode.

---

# 10. Tableau récapitulatif

```
Index | Catégorie      | Mode                    | Sous‑modes | Description
------|----------------|-------------------------|------------|-------------------------------
0     | Ambiance       | Éclairage doux          | Non        | Cycle vert/jaune doux
1     | Ambiance       | Vague                   | Non        | Vague verte séquentielle
2     | Arc‑en‑ciel    | Arc‑en‑ciel             | Oui (0-1)  | Cycle RGB coloré
3     | Pulse          | Pulse Vert              | Oui (0-2)  | Respiration verte PWM
4     | Pulse          | Pulse Jaune             | Oui (0-2)  | Respiration jaune PWM
5     | Pulse          | Pulse Rouge             | Oui (0-2)  | Respiration rouge PWM
6     | Dynamique      | Rush                    | Non        | Clignotement rouge rapide
7     | Dynamique      | K2000                   | Oui (0-1)  | Balayage blanc avec traînée
8     | Dynamique      | Jackpot                 | Oui (0-2)  | Couleurs aléatoires + flash
9     | Spécial        | Gagnant 🎉              | Non        | Animation festive 4 phases
10    | Client         | Client Perdant          | Non        | Flash rouge/jaune
11    | Fonctionnel    | Ouverture               | Non        | Vert fixe
12    | Fonctionnel    | Fermeture               | Non        | Rouge fixe
13    | Fonctionnel    | Pause Café              | Non        | Jaune + vert clignotant
14    | Fonctionnel    | Maintenance             | Non        | Cycle 6 couleurs
15    | Humeur         | Humeur du Patron        | Oui (0-5)  | Couleur module 4
```

---

# 11. Changements par rapport aux versions précédentes

## Modes supprimés

- **MODE_ZEN** : Supprimé car identique à Pulse Vert. Utilisez Pulse Vert à la place.
- **MODE_ARC_EN_CIEL (classique)** : Supprimé car Arc-en-ciel Turbo suffit. Le mode restant offre maintenant 2 vitesses via sous-modes.
- **MODE_DISCO** : Supprimé car identique à Jackpot. Utilisez Jackpot à la place.
- **MODE_FDJ_WINNER** : Fusionné dans le nouveau mode Gagnant.
- **MODE_CLIENT_GAGNANT** : Fusionné dans le nouveau mode Gagnant.

## Modes modifiés

- **Gagnant 🎉** : Nouveau mode qui combine les meilleurs aspects de FDJ Winner et Client Gagnant, avec une animation en 4 phases plus festive et complète.

## Impact sur l'interface web

Tous les boutons ont été réorganisés pour refléter la nouvelle structure :
- Les indices des modes ont été mis à jour
- Les sous-modes correspondent aux bons modes
- Le mode automatique dispose maintenant d'une route fonctionnelle `/auto`

---

# 12. Mode automatique

Le système inclut un mode automatique qui change automatiquement entre :

- **Fermeture** (rouge) : avant l'heure d'ouverture et après l'heure de fermeture
- **Pulse Vert** (par défaut) : pendant les heures d'ouverture

Configuration via l'interface web :
- Heure d'ouverture (par défaut : 8h)
- Heure de fermeture (par défaut : 18h)
- Activation/désactivation

---

# 13. Conclusion

Cette référence couvre tous les 16 modes disponibles dans **Totem Feux du Tabac**.  
Chaque mode peut être modifié ou étendu dans [modes.cpp](../src/modes.cpp).

Pour aller plus loin :

- [/docs/pwm_system_FR.md](pwm_system_FR.md) — Détails techniques sur le système PWM
- [/docs/architecture_FR.md](architecture_FR.md) — Architecture du projet
- [/docs/troubleshooting_FR.md](troubleshooting_FR.md) — Résolution de problèmes

---

**Dernière mise à jour :** Janvier 2026  
**Version :** Compatible avec la version actuelle du firmware
