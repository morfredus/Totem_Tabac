# ✅ **8 — `/docs/modes_reference_FR.md`**

```markdown
# Référence des modes — Totem Feux du Tabac

Ce document décrit tous les modes lumineux disponibles dans **Totem Feux du Tabac**.  
Il explique le comportement de chaque mode, son objectif, et les sous‑modes associés.

Ce guide est conçu pour être clair et accessible, même pour un débutant.

---

# 1. Vue d’ensemble

Le système inclut **plus de 20 modes lumineux**, regroupés en catégories :

- Modes d’ambiance  
- Modes Pulse  
- Animations dynamiques  
- Effets spéciaux  
- Modes fonctionnels  
- Modes fun / spécifiques au tabac  

Chaque mode peut être sélectionné via :

- L’interface Web  
- Le bouton physique (Mode suivant)  
- Les routes API  

Les sous‑modes permettent de varier :

- La vitesse  
- La direction  
- Les couleurs  
- Les effets  

---

# 2. Modes d’ambiance

## 2.1 Respiration Zen
Effet de respiration douce sur tous les modules.

- Fade sinusoidal  
- Très calme  
- Idéal pour une ambiance discrète  

**Sous‑modes :**  
0 = très lent  
1 = lent  
2 = normal  

---

## 2.2 Ambiance Douce
Cycle de couleurs doux et progressif.

- Transitions légères  
- Atmosphère relaxante  

**Sous‑modes :**  
0 = tons chauds  
1 = tons froids  
2 = mixte  

---

## 2.3 Vague
Une vague lumineuse qui traverse les 4 modules.

- Activation séquentielle  
- Fade fluide  

**Sous‑modes :**  
0 = vague lente  
1 = vague moyenne  
2 = vague rapide  

---

# 3. Modes Arc‑en‑ciel

## 3.1 Arc‑en‑ciel
Cycle RGB classique.

- Rotation douce des teintes  
- Modules synchronisés  

**Sous‑modes :**  
0 = lent  
1 = normal  
2 = rapide  

---

## 3.2 Arc‑en‑ciel Turbo
Version plus rapide et énergique.

- Cycle très rapide  
- Effet dynamique  

**Sous‑modes :**  
0 = turbo  
1 = hyper  
2 = extrême  

---

# 4. Modes Pulse (PWM)

Ces modes utilisent un **fade PWM réel**.

## 4.1 Pulse Vert  
## 4.2 Pulse Jaune  
## 4.3 Pulse Rouge  

Chaque mode :

- Fait varier une couleur en fade  
- Utilise une courbe sinus  
- Tous les modules pulsent ensemble  

**Sous‑modes :**  
0 = lent  
1 = normal  
2 = rapide  

---

# 5. Animations dynamiques

## 5.1 Rush
Effet de poursuite rapide.

- Flashs rapides en séquence  
- Animation énergique  

**Sous‑modes :**  
0 = sens horaire  
1 = sens antihoraire  
2 = aléatoire  

---

## 5.2 K2000 (Bidirectionnel)
Effet Knight Rider classique.

- Point rouge qui va gauche → droite → gauche  
- Mouvement fluide  

**Sous‑modes :**  
0 = lent  
1 = normal  
2 = rapide  

---

## 5.3 K2000 Traînée (Light Tail)
Version améliorée avec traînée lumineuse.

- Point principal rouge  
- Traînée qui s’estompe derrière  
- Effet très fluide en PWM  

**Sous‑modes :**  
0 = traînée courte  
1 = traînée moyenne  
2 = traînée longue  

---

## 5.4 Disco
Clignotements aléatoires multicolores.

- Très aléatoire  
- Effet “soirée”  

**Sous‑modes :**  
0 = chaos léger  
1 = chaos moyen  
2 = chaos total  

---

# 6. Effets spéciaux

## 6.1 Jackpot
Effet “machine à sous”.

- Rotation rapide  
- Fin avec flash gagnant  

**Sous‑modes :**  
0 = rotation lente  
1 = rotation rapide  
2 = rotation extrême  

---

## 6.2 FDJ Winner
Animation de célébration pour gagnants.

- Flashs bleu/blanc  
- Stroboscope rapide  

**Sous‑modes :**  
0 = court  
1 = moyen  
2 = long  

---

# 7. Modes interaction client

## 7.1 Client Gagnant
Célébration verte.

- Flashs verts  
- Effet positif  

---

## 7.2 Client Perdant
Effet rouge “perdu”.

- Flashs rouges  
- Animation courte  

---

# 8. Modes fonctionnels
## 2.2 Ambiance Douce (matrice)
Fond chaud + respiration verte douce sur toute la matrice 8x8.

- Accent visuel près des colonnes 0/3/6 (compatible masque 3 feux)  
- Atmosphère relaxante  
- Accueil chaleureux  
## 2.3 Vague (matrice)
Vague d’eau sinusoïdale bleue/cyan avec crêtes blanches (écume), se déplaçant horizontalement.

- Accent visuel près des colonnes 0/3/6  
- Dégradé de profondeur (bleu sombre → cyan → blanc)  
- **Sous‑modes vitesse** : 0 = Lent, 1 = Moyen, 2 = Rapide  

# 3. Modes Arc‑en‑ciel (adaptés matrice 0.19.0)
- Fade vers extinction  
## 3.1 Arc‑en‑ciel (matrice)
Bandes verticales défilantes (rouge → violet) sur toute la matrice.

- Modulation verticale légère pour le relief  
- Accent visuel près des colonnes 0/3/6  

# 4. Modes Pulse (PWM et matrice)

Ces modes utilisent un fade sinus (PWM) et une respiration uniforme pleine matrice (8x8) avec légère variation spatiale.
---
## 4.1 Pulse Vert (matrice)  
## 4.2 Pulse Jaune (matrice)  
## 4.3 Pulse Rouge (matrice)  
- Fades sinusoidal  
- Très calme  
- Idéal pour une ambiance discrète  

---

# 9. Mode humeur

## 9.1 Humeur du Patron
Mode fun représentant l’humeur du patron.

**Sous‑modes :**  
0 = Heureux (vert)  
1 = Neutre (jaune)  
2 = Énervé (rouge)  
3 = Énergique (arc‑en‑ciel)  
4 = Fatigué (bleu doux)  
5 = Fête (disco)  

---

# 10. Tableau récapitulatif

```
Catégorie            | Mode                | Sous‑modes | Description
---------------------|---------------------|------------|-------------------------------
Ambiance             | Zen                 | Oui        | Respiration douce
Ambiance             | Ambiance Douce      | Oui        | Cycle léger
Ambiance             | Vague               | Oui        | Vague lumineuse
Arc‑en‑ciel          | Arc‑en‑ciel         | Oui        | Cycle RGB
Arc‑en‑ciel          | Arc‑en‑ciel Turbo   | Oui        | Cycle rapide
Pulse                | Pulse Vert          | Oui        | Fade PWM
Pulse                | Pulse Jaune         | Oui        | Fade PWM
Pulse                | Pulse Rouge         | Oui        | Fade PWM
Dynamique            | Rush                | Oui        | Poursuite rapide
Dynamique            | K2000               | Oui        | Balayage rouge
Dynamique            | K2000 Traînée       | Oui        | Balayage + traînée
Dynamique            | Disco               | Oui        | Flashs aléatoires
Spécial              | Jackpot             | Oui        | Effet casino
Spécial              | FDJ Winner          | Oui        | Célébration
Client               | Client Gagnant      | Non        | Flash vert
Client               | Client Perdant      | Non        | Flash rouge
Fonctionnel          | Ouverture           | Non        | Animation verte
Fonctionnel          | Fermeture           | Non        | Animation rouge
Fonctionnel          | Pause Café          | Non        | Pulse jaune
Fonctionnel          | Maintenance         | Non        | Avertissement
Humeur               | Humeur du Patron    | Oui        | 6 humeurs
```

---

# 11. Conclusion

Cette référence couvre tous les modes disponibles dans **Totem Feux du Tabac**.  
Chaque mode peut être modifié ou étendu dans `modes.cpp`.

Pour aller plus loin :

- `/docs/pwm_system_FR.md`  
- `/docs/architecture_FR.md`  
- `/docs/troubleshooting_FR.md`  
