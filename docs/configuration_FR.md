# Guide de Configuration

**Valide à partir de la version 0.20.0**

## Vue d'ensemble

Tous les paramètres modifiables par l'utilisateur sont centralisés dans `include/config.h`. Ce guide vous accompagne dans la personnalisation de chaque option.

## Démarrage rapide

1. **Copiez le fichier d'exemple:**
   ```bash
   cp include/secrets_example.h include/secrets.h
   ```

2. **Éditez `include/secrets.h`:**
   Ajoutez vos réseaux WiFi (SSID, mot de passe).

3. **Éditez `include/config.h`:**
   Personnalisez le nom mDNS, le port HTTP, les paramètres OTA et les valeurs par défaut.

4. **Compilez et téléversez:**
   ```bash
   platformio run --environment esp32devkit --target upload
   ```

---

## Paramètres de configuration (`config.h`)

### Nom mDNS
```cpp
#define MDNS_NAME "Totem-Tabac"
```
- **Description:** Le nom d'hôte utilisé pour accéder à l'appareil sur le réseau.
- **Format:** Caractères alphanumériques et tirets uniquement (pas d'espaces).
- **URL d'accès:** `http://<MDNS_NAME>.local`
- **Exemple:** Si réglé sur `mon-totem`, accédez via `http://mon-totem.local`
- **Remarque:** Insensible à la casse sur la plupart des réseaux.

### Port du serveur HTTP
```cpp
#define HTTP_SERVER_PORT 80
```
- **Description:** Port pour l'interface web.
- **Défaut:** 80 (HTTP standard)
- **Avancé:** Changez à 8080 si le port 80 est occupé, puis accédez via `http://<MDNS_NAME>.local:8080`

### Configuration OTA

#### Port OTA
```cpp
#define OTA_PORT 3232
```
- **Description:** Port utilisé par ArduinoOTA pour les mises à jour par voie aérienne.
- **Défaut:** 3232 (port OTA standard)
- **Usage:** PlatformIO l'utilise automatiquement; aucune action manuelle requise.

#### Nom d'hôte OTA
```cpp
#define OTA_HOSTNAME "Totem-Tabac"
```
- **Description:** Le nom visible dans la liste des appareils OTA de PlatformIO.
- **Doit correspondre:** À votre nom mDNS pour la cohérence.

#### Mot de passe OTA (Optionnel)
```cpp
// #define OTA_PASSWORD "totem2026"
```
- **Description:** Protège les mises à jour OTA avec un mot de passe (optionnel).
- **Défaut:** Désactivé (pas de mot de passe requis).
- **Pour activer:** Décommentez la ligne et remplacez `totem2026` par votre mot de passe.
- **Sécurité:** Utilisez un mot de passe fort si vous l'activez.

### Affichage et modes par défaut

#### Type d'affichage par défaut
```cpp
#define DEFAULT_DISPLAY_TYPE DISPLAY_PWM
```
- **Options:**
  - `DISPLAY_PWM` (0) – Modules analogiques (défaut)
  - `DISPLAY_MATRIX` (1) – Matrice LED 8×8
- **Description:** Type d'affichage actif au démarrage (persisté en NVS).

#### Mode par défaut
```cpp
#define DEFAULT_MODE 3  // MODE_PULSE_VERT
```
- **Codes des modes:**
  - 0 = `MODE_AMBIANCE_DOUCE` (Ambiance douce)
  - 1 = `MODE_VAGUE` (Vague)
  - 2 = `MODE_ARC_EN_CIEL` (Arc-en-ciel)
  - 3 = `MODE_PULSE_VERT` (Pulse Vert) ← défaut
  - 4 = `MODE_PULSE_JAUNE` (Pulse Jaune)
  - 5 = `MODE_PULSE_ROUGE` (Pulse Rouge)
  - 6 = `MODE_RUSH` (Rush)
  - 7 = `MODE_K2000` (Scanner K2000)
  - 8 = `MODE_JACKPOT`
  - 9 = `MODE_FDJ_WINNER`
  - 10 = `MODE_CLIENT_GAGNANT` (Client gagnant)
  - 11 = `MODE_CLIENT_PERDANT` (Client perdant)
  - 12 = `MODE_OUVERTURE` (Ouverture)
  - 13 = `MODE_FERMETURE` (Fermeture)
  - 14 = `MODE_PAUSE_CAFE` (Pause café)
  - 15 = `MODE_MAINTENANCE` (Maintenance)
  - 16 = `MODE_HUMEUR_PATRON` (Humeur du patron)

#### Luminosité matrice
```cpp
#define DEFAULT_MATRIX_BRIGHTNESS 200
```
- **Plage:** 0–255
- **Description:** Luminosité par défaut pour la matrice 8×8 (les modules PWM utilisent leurs propres valeurs PWM).
- **200 (défaut):** Bon équilibre entre luminosité et consommation énergétique.
- **Ajustable via l'UI web:** Les modifications persistent en NVS.

---

## Configuration WiFi (`secrets.h`)

**Emplacement du fichier:** `include/secrets.h` (à créer à partir de `secrets_example.h`)

```cpp
static const char* WIFI_NETWORKS[][2] = {
    {"SSID1", "MOT_DE_PASSE1"},
    {"SSID2", "MOT_DE_PASSE2"},
    {"SSID3", "MOT_DE_PASSE3"},
};
```

- **Format:** Tableau de paires `{SSID, mot_de_passe}`.
- **Ordre de connexion:** L'appareil essaie les réseaux séquentiellement; se connecte au premier disponible.
- **Sécurité:** N'engagez jamais `secrets.h` à Git (protégé par `.gitignore`).
- **Fichier de référence:** Utilisez toujours `secrets_example.h` comme référence.

---

## Accédez à votre appareil

### Interface Web
```
http://<MDNS_NAME>.local
```
- Exemple: `http://Totem-Tabac.local`
- IP directe: `http://192.168.x.x` (affichée sur le moniteur série au démarrage)

### Page de mise à jour OTA
```
http://<MDNS_NAME>.local/update
```
- Téléversez directement les fichiers binaires `.bin` depuis le navigateur.

### Endpoints API
- `/status` – État JSON de l'appareil
- `/mode?value=<N>` – Définir le mode
- `/display?value=<0|1>` – PWM (0) ou Matrice (1)
- `/brightness?value=<0-255>` – Définir la luminosité matrice
- `/submode` – Cycler le sous-mode de vitesse

---

## Sortie du moniteur série (Démarrage)

À la mise sous tension, vous verrez:
```
mDNS started: http://Totem-Tabac.local
IP: 192.168.1.100
Serveur HTTP démarré
OTA prêt
```

- **mDNS:** Confirme que le nom d'hôte est accessible.
- **IP:** Adresse IP directe pour accès manuel.
- **OTA prêt:** ArduinoOTA est prêt pour les mises à jour firmware.

---

## Dépannage

### L'appareil n'est pas accessible via mDNS
- Confirmez le nom mDNS dans `config.h` (alphanumériques + tirets uniquement).
- Vérifiez la sortie série: devrait afficher `mDNS started: http://...`.
- Redémarrez l'appareil et réessayez après 30 secondes.
- Secours: Utilisez l'adresse IP directe de la sortie série.

### Conflits de ports
- Si le port 80 est occupé sur votre réseau, changez `HTTP_SERVER_PORT` à 8080 dans `config.h`.
- Recompilez et téléversez.
- Accédez via `http://<MDNS_NAME>.local:8080`

### Impossible de téléverser en OTA
- Assurez-vous que l'appareil est alimenté et connecté au WiFi.
- Vérifiez que le nom d'hôte OTA correspond à `OTA_HOSTNAME` dans `config.h`.
- Si un mot de passe est activé, confirmez-le dans `config.h` (décommenté).
- Utilisez PlatformIO: `platformio run --environment esp32devkit_ota --target upload`

---

## Étapes suivantes

- [Démarrage](getting_started_FR.md) – Guide de configuration initiale
- [Configuration matérielle](hardware_setup_FR.md) – Câblage GPIO et composants
- [Référence des modes](modes_reference_FR.md) – Documentation détaillée des modes
