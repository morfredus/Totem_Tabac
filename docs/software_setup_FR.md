# Installation logicielle — Totem Feux du Tabac

Ce guide explique comment installer, configurer et compiler le firmware du projet **Totem Feux du Tabac** avec PlatformIO.  
Il est conçu pour être accessible aux débutants et ne nécessite aucune expérience préalable avec l’ESP32.

---

# 1. Logiciels nécessaires

Vous aurez besoin de :

- **Visual Studio Code**  
  https://code.visualstudio.com/

- **Extension PlatformIO IDE**  
  À installer depuis le marketplace VSCode.

- **Git** (optionnel mais recommandé)  
  https://git-scm.com/

---

# 2. Installation de PlatformIO

1. Ouvrir **Visual Studio Code**  
2. Aller dans **Extensions**  
3. Chercher **PlatformIO IDE**  
4. Cliquer sur **Installer**  
5. Redémarrer VSCode  

PlatformIO installera automatiquement les outils nécessaires.

---

# 3. Récupération du projet

### Option A — Cloner avec Git

```
git clone https://github.com/votrecompte/totem-feux-du-tabac.git
```

### Option B — Télécharger en ZIP

1. Aller sur votre dépôt GitHub  
2. Cliquer **Code → Download ZIP**  
3. Extraire le dossier  

---

# 4. Ouvrir le projet dans PlatformIO

1. Ouvrir VSCode  
2. Cliquer sur **PlatformIO Home**  
3. Choisir **Open Project**  
4. Sélectionner le dossier du projet  
5. Attendre l’installation automatique des dépendances  

---

# 5. Comprendre platformio.ini

Le projet utilise une configuration unifiée compatible avec :

- ESP32 DevKit (WROOM)
- ESP32‑S3 DevKitC‑1 N16R8
- ESP32‑S3 N8R8

Paramètres importants :

```
framework = arduino
monitor_speed = 115200
upload_speed = 921600
board_build.partitions = huge_app.csv
build_flags = -std=gnu++17
```

Dépendances incluses :

- Adafruit NeoPixel  
- Adafruit BusIO  
- Adafruit GFX  
- Adafruit ST7735/ST7789  
- TinyGPSPlus  
- U8g2  

---

# 6. Compiler le firmware

Pour compiler :

1. Ouvrir le projet dans VSCode  
2. Cliquer sur l’icône **check** (Build) en bas  
3. Attendre la fin de la compilation  

Si tout est correct :

```
SUCCESS: Build complete
```

---

# 7. Téléverser le firmware sur l’ESP32

1. Brancher l’ESP32 en USB  
2. Cliquer sur l’icône **flèche** (Upload)  
3. PlatformIO compile (si nécessaire) puis téléverse  
4. L’ESP32 redémarre automatiquement  

Si l’upload échoue :

- Essayer un autre câble USB  
- Maintenir **BOOT** pendant l’upload (selon la carte)  
- Vérifier le bon port COM dans PlatformIO  

---

# 8. Moniteur série

Pour afficher les logs :

1. Cliquer sur l’icône **prise** (Monitor)  
2. Régler la vitesse sur **115200**  
3. Vous verrez :

```
[INFO] Totem Feux du Tabac starting...
[INFO] WiFi Manager ready
[INFO] Current mode: 0
```

---

# 9. Configuration WiFi

Au premier démarrage, l’ESP32 lance le **WiFi Manager**.

1. Se connecter au réseau WiFi :  
   **Totem-Feux-Setup**

2. Le portail captif s’ouvre automatiquement  
   Sinon aller sur :  
   http://192.168.4.1/

3. Choisir votre WiFi  
4. Entrer le mot de passe  
5. L’ESP32 redémarre et se connecte  

Vous pouvez ensuite accéder à l’interface via :

```
http://totem.local
```

ou via son adresse IP.

---

# 10. Structure des fichiers

```
/src
  main.cpp          → Point d’entrée du programme
  modes.cpp         → Toutes les animations lumineuses
  light_helpers.cpp → Abstraction PWM

/include
  board_config.h    → Mapping GPIO
  light_helpers.h   → API de contrôle LED

/docs
  (documentation)

/platformio.ini     → Configuration PlatformIO
```

---

# 11. Dépannage

### PlatformIO ne trouve pas la carte  
→ Installer la plateforme ESP32 depuis PlatformIO Home.

### Upload impossible  
→ Maintenir BOOT pendant l’upload.  
→ Essayer un autre câble USB.

### Texte illisible dans le moniteur série  
→ Mauvais baud rate (doit être 115200).

### WiFi Manager ne s’affiche pas  
→ Redémarrer l’ESP32.  
→ Effacer les identifiants WiFi (si une fonction est prévue).

---

# 12. Résumé

Vous savez maintenant :

- Installer PlatformIO  
- Ouvrir le projet  
- Compiler le firmware  
- Le téléverser sur l’ESP32  
- Configurer le WiFi  
- Utiliser le moniteur série  

Votre environnement logiciel est prêt.
