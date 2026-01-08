# ✅ **14 — `/docs/faq_FR.md`**

```markdown
# FAQ — Totem Feux du Tabac

Cette FAQ répond aux questions les plus fréquentes concernant l’installation, la configuration et l’utilisation de **Totem Feux du Tabac**.

---

# 1. Questions générales

## 1.1 Qu’est‑ce que Totem Feux du Tabac ?
Un système lumineux basé sur ESP32 contrôlant 4 modules de feux tricolores avec plus de 20 animations.

---

## 1.2 Quelles cartes ESP32 sont compatibles ?
- ESP32 DevKit (WROOM)  
- ESP32‑S3 DevKitC‑1 N16R8  
- ESP32‑S3 N8R8  

Toute carte ESP32 compatible Arduino/PlatformIO fonctionne.

---

## 1.3 Puis‑je ajouter plus de modules de feux ?
Oui, mais il faudra :

- Ajouter des GPIO  
- Ajouter des canaux PWM  
- Modifier `board_config.h`  
- Mettre à jour `initTrafficLightPWM()`  

---

# 2. Questions matérielles

## 2.1 Ai‑je besoin de résistances ?
Les modules de feux tricolores en possèdent généralement déjà.  
Si vous utilisez des LEDs nues : ajouter des résistances 220–330 Ω.

---

## 2.2 Puis‑je tout alimenter via USB ?
Pour les tests : **oui**  
Pour l’installation finale : **non**

Utiliser une alimentation 5V stable (2A recommandé).

---

## 2.3 Pourquoi mes LEDs scintillent ?
Causes fréquentes :

- Masse commune manquante  
- Alimentation insuffisante  
- Fils mal fixés  

---

## 2.4 Puis‑je utiliser les GPIO 34–39 ?
Non.  
Ces pins sont **entrée‑seulement** et ne supportent pas le PWM.

---

# 3. Questions logicielles

## 3.1 Dois‑je utiliser PlatformIO ?
Oui.  
Le projet ne compile pas dans l’IDE Arduino.

---

## 3.2 Comment changer le mode par défaut ?
Modifier dans `main.cpp` :

```
currentMode = MODE_ZEN;
```

---

## 3.3 Comment ajouter un nouveau mode ?
1. Ajouter une constante dans `modes.h`  
2. Ajouter un `case` dans `updateMode()`  
3. Implémenter l’animation  
4. Ajouter le support dans l’interface Web (optionnel)  

---

# 4. Questions WiFi

## 4.1 Je ne vois pas le réseau WiFi Manager
L’ESP32 est peut‑être déjà connecté à un WiFi enregistré.

Solutions :

- Redémarrer l’ESP32  
- Effacer les identifiants WiFi  

---

## 4.2 Le portail captif ne s’ouvre pas
Ouvrir manuellement :

```
http://192.168.4.1/
```

---

## 4.3 Puis‑je désactiver le WiFi ?
Oui.  
Commenter l’initialisation WiFi dans `main.cpp`.

---

# 5. Questions interface Web

## 5.1 L’interface ne charge pas
Essayer :

- `http://totem.local`  
- L’adresse IP de l’ESP32  
- Vider le cache du navigateur  

---

## 5.2 Les boutons ne fonctionnent pas
Causes possibles :

- ESP32 hors ligne  
- Cache navigateur  

---

# 6. Questions sur les animations

## 6.1 Pourquoi certains modes ont des sous‑modes ?
Pour permettre :

- Variations de vitesse  
- Variations de direction  
- Variations de couleurs  

---

## 6.2 Puis‑je changer la vitesse d’une animation ?
Oui.  
Modifier la valeur `delayMs` dans le mode correspondant.

---

## 6.3 Puis‑je changer les couleurs ?
Oui.  
Utiliser :

```
setRGB(module, r, y, g);
```

dans `modes.cpp`.

---

# 7. Questions sur les boutons

## 7.1 Puis‑je ajouter plus de boutons ?
Oui.  
Ajouter des GPIO et mettre à jour la gestion dans `main.cpp`.

---

## 7.2 Mon bouton déclenche plusieurs fois
Ajouter un debounce logiciel (10–50 ms).

---

# 8. Questions avancées

## 8.1 Puis‑je contrôler le système via HTTP ?
Oui.  
Routes disponibles :

- `/nextmode`  
- `/nextsub`  
- `/status`  

---

## 8.2 Puis‑je intégrer le système à Home Assistant ?
Oui, via des requêtes HTTP ou un portage manuel vers ESPHome.

---

## 8.3 Puis‑je alimenter le système sur batterie ?
Non recommandé.  
Les LEDs + ESP32 consomment trop.

---

# 9. Résumé

Cette FAQ couvre :

- Matériel  
- Logiciel  
- WiFi  
- Interface Web  
- Animations  
- Boutons  
- Utilisation avancée  

Pour plus de détails, consulter les autres fichiers du dossier `/docs/`.
