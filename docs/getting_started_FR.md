# Démarrage rapide

**Valide à partir de la version 0.20.0**

Bienvenue dans **Totem Feux du Tabac** – un système d'animation LED intelligent pour commerces de détail. Ce guide vous aide à démarrer en 5 minutes.

## Ce que vous avez

- **Firmware Totem Tabac** (v0.20.0+)
- **ESP32 DevKit** microcontrôleur
- **Affichage LED** (modules PWM ou matrice 8×8 NeoPixel)
- **Interface web** accessible par WiFi
- **Mises à jour OTA** (téléversement firmware par réseau)

---

## 1. Assemblage matériel (5 min)

### Checklist du câblage
- [ ] Soudez/connectez les broches GPIO selon `docs/hardware_setup_FR.md`
- [ ] Connectez l'alimentation (5V recommandé)
- [ ] Vérifiez toutes les connexions LED

**Référence GPIO** (voir `include/board_config.h`):
- Bouton 1: GPIO 0 (mode suivant)
- Bouton 2: GPIO 35 (sous-mode suivant)
- PWM/LEDs: Voir guide matériel
- Données matrice: GPIO 14 (WS2812B)

---

## 2. Préparez le firmware

### Installez PlatformIO
```bash
pip install platformio
```

### Clonez ou téléchargez
```bash
git clone <repository>
cd Totem_Tabac
```

### Configurez les secrets
```bash
cp include/secrets_example.h include/secrets.h
```
Éditez `include/secrets.h` et ajoutez vos réseaux WiFi:
```cpp
static const char* WIFI_NETWORKS[][2] = {
    {"VotreSSID", "VotreMotDePasse"},
    {"SecondWiFi", "SecondMotDePasse"},
};
```

### (Optionnel) Personnalisez la configuration
Éditez `include/config.h` pour ajuster:
- Nom mDNS: `#define MDNS_NAME "Totem-Tabac"`
- Port HTTP: `#define HTTP_SERVER_PORT 80`
- Mode/luminosité par défaut

---

## 3. Téléversez le firmware

### Via USB (première fois)
```bash
platformio run --environment esp32devkit --target upload
```

### Via OTA (après la connexion WiFi)
```bash
platformio run --environment esp32devkit_ota --target upload
```

### Moniteur série
```bash
platformio device monitor
```

Sortie attendue:
```
mDNS started: http://Totem-Tabac.local
IP: 192.168.1.100
Serveur HTTP démarré
OTA prêt
```

---

## 4. Accédez à votre appareil

### Interface Web
Ouvrez dans votre navigateur:
```
http://Totem-Tabac.local
```

Ou utilisez l'IP directe (du moniteur série):
```
http://192.168.1.100
```

### Fonctionnalités que vous verrez
- **Sélecteur de modes** – Modes doux, dynamiques, utilitaires
- **Basculer l'affichage** – Modules PWM ou matrice 8×8
- **Curseur de luminosité** – Ajustez l'intensité LED
- **Contrôles de vitesse** – Sous-modes de vitesse pour les modes doux
- **Sélecteur de couleur** – Couleur d'humeur (Humeur du patron)
- **Mise à jour OTA** – Téléversez un nouveau firmware depuis le navigateur

---

## 5. Première utilisation

### Mise sous tension initiale
1. L'appareil se connecte au premier WiFi connu
2. Le moniteur série affiche l'IP et l'URL mDNS
3. Mode par défaut: Pulse Vert (modules PWM)
4. Luminosité par défaut: 200/255

### Navigation
- **Boutons physiques:**
  - Bouton 1 (GPIO 0): Cycler les modes
  - Bouton 2 (GPIO 35): Cycler les sous-modes de vitesse
- **UI web:**
  - Cliquez sur les boutons de mode pour basculer instantanément
  - Ajustez la luminosité avec le curseur
  - Les modifications persistent après redémarrage

---

## 6. Aperçu des modes (Avancé)

| Mode | Code | Type | Vitesses? |
|------|------|------|-----------|
| Ambiance Douce | 0 | Doux | ✓ |
| Vague (Onde) | 1 | Doux | ✓ |
| Arc-en-ciel | 2 | Doux | ✓ |
| Pulse Vert | 3 | Doux | ✓ |
| Pulse Jaune | 4 | Doux | ✓ |
| Pulse Rouge | 5 | Doux | ✓ |
| Rush | 6 | Dynamique | ✗ |
| Scanner K2000 | 7 | Dynamique | ✓ |
| Jackpot | 8 | Dynamique | ✗ |
| FDJ Gagnant | 9 | Dynamique | ✗ |
| Client Gagnant | 10 | Utilitaire | ✗ |
| Client Perdant | 11 | Utilitaire | ✗ |
| Ouverture | 12 | Utilitaire | ✗ |
| Fermeture | 13 | Utilitaire | ✗ |
| Pause Café | 14 | Utilitaire | ✗ |
| Maintenance | 15 | Utilitaire | ✗ |
| Humeur du Patron | 16 | Utilitaire | ✗ |

Voir [Référence des modes](modes_reference_FR.md) pour les descriptions détaillées.

---

## 7. Réseau et sécurité

### mDNS (réseau sans configuration)
Votre appareil est automatiquement détectable en tant que:
```
Totem-Tabac.local
```
Changez le nom dans `include/config.h`.

### Réseaux WiFi
Ajoutez plusieurs réseaux dans `include/secrets.h`; l'appareil se connecte au premier disponible.

### Mot de passe OTA (Optionnel)
Décommentez dans `include/config.h` pour exiger un mot de passe pour les mises à jour OTA:
```cpp
#define OTA_PASSWORD "votre_mot_de_passe_securise"
```

---

## 8. Dépannage

| Problème | Solution |
|----------|----------|
| L'appareil n'apparaît pas en WiFi | Vérifiez `secrets.h`; confirmez SSID et mot de passe |
| Impossible d'accéder à `http://Totem-Tabac.local` | Utilisez l'IP directe du moniteur série |
| UI web lent/saccadé | Redémarrez l'appareil; vérifiez le signal WiFi |
| Téléversement OTA échoue | Assurez-vous que l'appareil est alimenté et sur le même WiFi |
| Les LED n'éclairent pas | Vérifiez le câblage GPIO; vérifiez l'alimentation |
| Les boutons ne réagissent pas | Vérifiez les connexions GPIO 0 et 35 |

---

## Étapes suivantes

- [Guide de configuration](configuration_FR.md) – Référence des paramètres détaillés
- [Configuration matérielle](hardware_setup_FR.md) – Câblage GPIO et composants
- [Référence des modes](modes_reference_FR.md) – Tous les détails des animations
- [FAQ](faq_FR.md) – Questions et réponses courantes
- [Dépannage](troubleshooting_FR.md) – Débogage avancé

---

## Référence rapide

| Commande | Objectif |
|----------|----------|
| `platformio run --environment esp32devkit --target upload` | Téléverser via USB |
| `platformio run --environment esp32devkit_ota --target upload` | Téléverser via WiFi (OTA) |
| `platformio device monitor` | Afficher les journaux série |
| `http://Totem-Tabac.local/update` | Page de téléversement firmware manuel |

---

**Profitez de votre Totem Feux du Tabac ! 🎉**

Pour obtenir de l'aide, consultez [FAQ](faq_FR.md) ou [Dépannage](troubleshooting_FR.md).
