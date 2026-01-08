# ✅ **/docs/troubleshooting_FR.md**

```markdown
# Dépannage — Totem Feux du Tabac

Ce document regroupe les problèmes les plus courants rencontrés lors de l’installation, du câblage, de la compilation ou de l’utilisation de **Totem Feux du Tabac**, ainsi que leurs solutions.

Il est conçu pour être simple, pratique et accessible aux débutants.

---

# 1. Problèmes matériels

## 1.1 Une LED ne s’allume pas
**Causes possibles :**
- Mauvais câblage GPIO  
- Polarité inversée  
- LED défectueuse  

**Solutions :**
- Vérifier le câblage avec `/docs/hardware_setup_FR.md`  
- Vérifier anode (+) et cathode (–)  
- Tester la LED avec un sketch simple  

---

## 1.2 Toutes les LEDs restent allumées
**Cause :**  
Masse non connectée ou flottante.

**Solution :**  
Relier **toutes les masses ensemble** :  
ESP32 GND ↔ LED GND ↔ GND alimentation

---

## 1.3 LEDs qui scintillent
**Cause :**  
Alimentation instable ou masse manquante.

**Solution :**
- Utiliser une alimentation 5V stable (2A recommandé)  
- Vérifier la masse commune  

---

## 1.4 L’ESP32 redémarre ou plante
**Causes possibles :**
- Mauvais câble USB  
- Alimentation insuffisante  
- Court‑circuit  

**Solutions :**
- Essayer un autre câble USB  
- Utiliser une alimentation 5V dédiée  
- Vérifier le câblage  

---

## 1.5 Le PWM ne fonctionne pas sur certaines pins
**Cause :**  
Certaines GPIO sont **entrée‑seulement** ou **sensibles au boot**.

**Solution :**  
Utiliser uniquement des pins compatibles PWM (voir `board_config.h`).

---

# 2. Problèmes logiciels

## 2.1 PlatformIO ne trouve pas la carte
**Cause :**  
Plateforme ESP32 non installée.

**Solution :**  
Installer la plateforme ESP32 depuis PlatformIO Home → Platforms.

---

## 2.2 Upload impossible
**Causes possibles :**
- Mauvais port COM  
- Câble USB défectueux  
- Carte nécessitant le bouton BOOT  

**Solutions :**
- Sélectionner le bon port COM  
- Essayer un autre câble  
- Maintenir **BOOT** pendant l’upload  

---

## 2.3 Texte illisible dans le moniteur série
**Cause :**  
Mauvais baud rate.

**Solution :**  
Régler sur **115200**.

---

## 2.4 Erreurs de compilation
**Causes possibles :**
- Bibliothèques manquantes  
- Installation PlatformIO corrompue  
- Mauvais environnement sélectionné  

**Solutions :**
- Réouvrir le projet  
- Supprimer le dossier `.pio` puis recompiler  
- Vérifier l’environnement dans `platformio.ini`  

---

# 3. Problèmes WiFi

## 3.1 Réseau WiFi Manager introuvable
**Cause :**  
L’ESP32 est déjà connecté à un WiFi enregistré.

**Solutions :**
- Redémarrer l’ESP32  
- Effacer les identifiants WiFi (si prévu)  
- Se rapprocher de l’ESP32  

---

## 3.2 Le portail captif ne s’ouvre pas
**Solution :**  
Ouvrir manuellement :  
```
http://192.168.4.1/
```

---

## 3.3 L’ESP32 ne se connecte pas au WiFi du tabac
**Causes possibles :**
- Mot de passe incorrect  
- Réseau 5 GHz (ESP32 = 2.4 GHz uniquement)  
- Signal faible  

**Solutions :**
- Vérifier le mot de passe  
- Utiliser un réseau 2.4 GHz  
- Rapprocher l’ESP32 du routeur  

---

# 4. Problèmes interface Web

## 4.1 L’interface ne charge pas
**Solutions :**
- Essayer `http://totem.local`  
- Utiliser l’adresse IP de l’ESP32  
- Vider le cache du navigateur  

---

## 4.2 Les boutons de l’interface ne fonctionnent pas
**Causes possibles :**
- ESP32 hors ligne  
- Cache navigateur  

**Solutions :**
- Rafraîchir la page  
- Redémarrer l’ESP32  
- Vérifier la connexion WiFi  

---

# 5. Problèmes d’animation

## 5.1 Le mode change mais les LEDs restent éteintes
**Cause :**  
PWM non initialisé ou mauvais mapping GPIO.

**Solution :**  
Vérifier :

- `initTrafficLightPWM()`  
- `board_config.h`  

---

## 5.2 Animations lentes ou saccadées
**Cause :**  
Boucle principale trop chargée.

**Solution :**  
Optimiser `updateMode()`.

---

## 5.3 Mauvaises couleurs affichées
**Cause :**  
Fils inversés (Rouge/Jaune/Vert).

**Solution :**  
Vérifier câblage et mapping.

---

# 6. Problèmes avec les boutons

## 6.1 Le bouton ne fait rien
**Causes possibles :**
- Mauvais GPIO  
- Pas de pull‑up  
- Mauvais câblage  

**Solutions :**
- Utiliser les pull‑ups internes  
- Vérifier le câblage  
- Tester avec un sketch simple  

---

## 6.2 Le bouton déclenche plusieurs fois
**Cause :**  
Rebond mécanique.

**Solution :**  
Ajouter un debounce logiciel (10–50 ms).

---

# 7. Débogage avancé

## 7.1 Activer les logs
Ajouter des `Serial.println()` dans :

- `main.cpp`  
- `modes.cpp`  
- `light_helpers.cpp`  

---

## 7.2 Vérifier les valeurs PWM
Exemple :

```
Serial.println(value);
```

---

## 7.3 Vérifier l’état WiFi
```
WiFi.status()
```

---

# 8. Résumé

Ce guide de dépannage couvre :

- Problèmes matériels  
- Problèmes logiciels  
- Problèmes WiFi  
- Problèmes interface Web  
- Problèmes d’animation  
- Problèmes de boutons  
- Techniques de débogage  

Si un problème persiste, vérifier :

- Le câblage  
- L’alimentation  
- `board_config.h`  
- Les logs du moniteur série  

Tout peut être résolu avec méthode et patience.
