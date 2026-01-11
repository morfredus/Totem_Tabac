## [0.20.0]  Configuration utilisateur et gestion mDNS (2026-01-11)
### Ajout�
- **\include/config.h\** : Param�tres centralis�s configurables par l'utilisateur (nom mDNS, port HTTP, param�tres OTA, mode/luminosit� par d�faut).
- **Configuration du nom d'h�te mDNS** : Changez le nom d'accessibilit� de l'appareil via \MDNS_NAME\ (d�faut : \Totem-Tabac\).
- **Configuration du nom d'h�te et port OTA** : Personnalisez les param�tres ArduinoOTA via \OTA_HOSTNAME\ et \OTA_PORT\.
- **Basculement mot de passe OTA** : Protection optionnelle par mot de passe via \OTA_PASSWORD\ (comment�e par d�faut).
- **Param�tres d'affichage et mode par d�faut** : Configurez le type d'affichage au d�marrage (PWM/Matrice), le mode initial, la luminosit� matrice.
- **\include/secrets_example.h\** : Fichier de mod�le d�montrant la structure de configuration WiFi (jamais engag� � Git).
- **Documentation utilisateur** :
  - \docs/configuration.md\ et \docs/configuration_FR.md\  Guide complet de configuration.
  - \docs/getting_started.md\ et \docs/getting_started_FR.md\  Guides de d�marrage rapide pour la premi�re utilisation.

### Modifi�
- **\src/main.cpp\** : Int�gration des includes \config.h\ ; initialisation mDNS utilise \MDNS_NAME\ et \MDNS.addService()\ pour l'enregistrement du service HTTP.
- **Configuration ArduinoOTA** : R�f�rence d�sormais \OTA_HOSTNAME\ et \OTA_PASSWORD\ optionnel depuis \config.h\ (compatible r�trograde).
- **Instantiation WebServer** : Le port utilise la macro \HTTP_SERVER_PORT\.

### D�tails techniques
- Tous les param�tres de configuration accessibles � l'utilisateur dans un seul fichier d'en-t�te (\config.h\).
- Service mDNS correctement annonc� (http, tcp, port 80) pour la d�couverte sur le r�seau local.
- Compatibilit� r�trograde maintenue ; les valeurs par d�faut correspondent aux param�tres pr�c�dents cod�s en dur.
- Sortie s�rie maintenant enregistre : \mDNS started: http://Totem-Tabac.local\ pour la commodit� de l'utilisateur.

### Documentation
- README.md et README_FR.md mis � jour avec les modifications v0.20.0, les liens de configuration et les r�f�rences de d�marrage rapide.
- Les guides de configuration et de d�marrage maintenant les points d'entr�e principaux pour les nouveaux utilisateurs.
- Tous les docs maintiennent une �quivalence stricte (EN/FR) selon les r�gles \.copilot\.


## [0.19.0] – Modes doux adaptés à la matrice (2026-01-11)
### Modifié
- **Ambiance douce (matrice)** : fond chaud avec respiration verte pleine matrice, accent visuel près des colonnes 0/3/6 (compatible masque 3 feux).
- **Vague (matrice)** : onde verte diagonale traversant la matrice, relief près des colonnes 0/3/6.
- **Arc‑en‑ciel (matrice)** : bandes verticales défilantes (rouge→violet) sur toute la matrice avec modulation verticale.
- **Pulse Vert/Jaune/Rouge (matrice)** : respiration uniforme sur toute la matrice avec légère variation spatiale.

### Détails techniques
- Utilisation complète des 64 LEDs en mode matrice pour les six modes doux.
- Respect du brightness global via `applyMatrixBrightnessToRGB()`.
- Compatibilité visuelle avec un cache matérialisant 3 feux (colonnes 0/3/6 accentuées).

### Documentation
- README et README_FR mis à jour (0.19.0), ajout de la page OTA personnalisée.
- Références de modes mises à jour pour refléter l’adaptation à la matrice.

## [0.18.0] – Mises à jour firmware OTA (Over-The-Air) (2026-01-11)
### Ajouté
- **Mises à jour OTA** : Le firmware peut maintenant être mis à jour sans fil via WiFi sans câble USB.
- **Intégration ArduinoOTA** : Implémentation OTA native ESP32 avec protection par mot de passe.
- **Surveillance d'état OTA** : Retour en temps réel de la progression et gestion des erreurs pendant les mises à jour.
- **Extinction des LEDs pendant MAJ** : Toutes les LEDs s'éteignent automatiquement pendant la mise à jour OTA pour retour visuel.

### Détails techniques
- Nom d'hôte OTA : `Totem-Tabac`
- Mot de passe OTA : `totem2026` (configurable)
- Support mDNS pour découverte de l'appareil
- Progression de mise à jour affichée via moniteur série
- Gestion d'erreurs complète (Auth, Begin, Connect, Receive, End)
- Utilisation Flash : 67.8% (888 973 octets) - inclut bibliothèques OTA
- Utilisation RAM : 15.3% (50 092 octets)

### Utilisation
- Se connecter au même réseau WiFi que le totem
- Utiliser Arduino IDE : Outils → Port → Totem-Tabac (port réseau)
- Ou utiliser PlatformIO : `pio run -t upload --upload-port Totem-Tabac.local`
- Entrer le mot de passe `totem2026` quand demandé

## [0.17.0] – Animations matrice améliorées pour Rush, K2000, Jackpot, FDJ Winner et Maintenance (2026-01-11)
### Ajouté
- **Mode Rush** : Lignes horizontales se déplaçant rapidement à différentes vitesses, créant un effet dynamique de vitesse avec couleurs rouge-orange et jaune.
- **Mode K2000** : Scanner classique style Kitt avec colonnes verticales balayant de gauche à droite avec effet de traînée rouge.
- **Mode Jackpot** : Animation de machine à sous avec 3 colonnes de symboles défilants (Dollar, 7, Cerise, Étoile) avec flash doré lors d'un gain.
- **Mode FDJ Winner** : Animation de victoire en 3 phases : flash doré, explosion de confettis depuis le centre, et pluie de pièces dorées.
- **Mode Maintenance** : Test complet de la matrice avec cycle de 8 couleurs unies, scan horizontal de lignes (cyan), et scan vertical de colonnes (orange).

### Modifié
- Les 5 modes ont maintenant des animations matrice 8x8 dédiées qui utilisent l'intégralité de l'affichage.
- Les animations matrice respectent le paramètre de luminosité global via `applyMatrixBrightnessToRGB()`.
- Les animations PWM restent inchangées et pleinement fonctionnelles.
- Animations conçues pour fonctionner avec ou sans masque sur les colonnes/lignes 2 et 5.

### Détails techniques
- Rush : Défilement horizontal à double vitesse avec effets de traînée (rafraîchissement 50ms).
- K2000 : Scanner de colonnes verticales avec traînée à 3 niveaux de dégradé (vitesses 100/60/35ms).
- Jackpot : Machine à sous à 4 symboles avec symboles codés par couleur et flash doré périodique (vitesses 120/80/50ms).
- FDJ Winner : Boucle d'animation de 40 frames avec physique d'explosion et effets de particules (rafraîchissement 80ms).
- Maintenance : Motif de test en 24 phases pour validation complète des LED (200ms par phase).

## [0.16.1] – Correction mise à l'échelle de luminosité pour toutes les animations (2026-01-11)
### Corrigé
- **Luminosité maintenant appliquée à TOUTES les animations matrice** : Les 6 animations personnalisées (Ouverture, Fermeture, Pause Café, Gagnant, Perdant, Humeur Patron) respectent maintenant correctement le paramètre de luminosité global.
- Correction de la luminosité des smileys en modes Ouverture/Fermeture.
- Correction de la luminosité de l'animation café en mode Pause Café.
- Correction de la luminosité du feu d'artifice en mode Gagnant.
- Correction de la luminosité de la pluie en mode Perdant.
- Correction de la luminosité de la vague diagonale en mode Humeur Patron.
- La luminosité peut maintenant être réglée à 0 (matrice complètement éteinte) sans problèmes.

### Détails techniques
- Application de `applyMatrixBrightnessToRGB()` à toutes les couleurs de pixels d'animation avant affichage.
- Chaque animation met maintenant à l'échelle les valeurs RGB par la luminosité globale avant d'appeler `setPixelXY()`.
- Assure un contrôle de luminosité cohérent sur tous les types d'animations.

## [0.16.0] – Persistance complète et contrôle de luminosité (2026-01-11)
### Ajouté
- **Persistance NVS complète** : Le mode d'animation actuel, le sous-mode et la couleur d'humeur sont maintenant sauvegardés et restaurés au démarrage.
- **Plage de luminosité 0-255** : La luminosité de la matrice peut maintenant être réglée de 0% (off) à 100% (luminosité maximale).
- **Luminosité dynamique dans les animations** : La valeur de luminosité est maintenant appliquée à toutes les animations matrice pour un contrôle d'intensité cohérent.

### Modifié
- Minimum de luminosité changé de 10 à 0 (permet d'éteindre complètement la matrice).
- Toutes les animations mettent maintenant à l'échelle les couleurs des pixels en fonction du paramètre de luminosité global.
- Persistance NVS inclut maintenant : type d'affichage, luminosité, mode actuel, sous-mode et couleur d'humeur.

### Détails techniques
- Ajout des fonctions `loadModeFromNVS()` et `saveCurrentModeToNVS()`.
- Ajout de la fonction helper `applyMatrixBrightnessToRGB()` pour la mise à l'échelle cohérente de la luminosité.
- Persistance du mode sauvegardée à chaque changement de mode/sous-mode/humeur.
- Validation de la plage de luminosité : 0 (off) à 255 (max).

## [0.15.0] – Animations matrice avancées (2026-01-11)
### Ajouté
- **Humeur du patron** : Effet de vague diagonale sur toute la matrice avec fading progressif (30-100% de luminosité, jamais éteint).
- **Ouverture** : Matrice verte complète avec animation smiley heureux (yeux et sourire courbe éteints).
- **Fermeture** : Matrice rouge complète avec animation smiley neutre (yeux et bouche droite éteints).
- **Pause café** : Animation créative avec effet de café chaud, bulles montantes et gradient marron/orange (imite la vapeur de café).
- **Gagnant** : Animation de joie avec vagues de couleurs et effet feu d'artifice sur toute la matrice (pulsations jaune/vert/magenta).
- **Perdant** : Animation de tristesse avec pluie de gouttes en bleu-gris et violet sombre.

### Modifié
- Les 6 animations utilitaires utilisent maintenant l'intégralité de la matrice 8x8 pour plus d'impact visuel en mode matrice.
- Les animations en mode PWM restent inchangées et indépendantes.
- Fonctions d'animation modularisées pour une meilleure maintenabilité.

### Détails techniques
- Les animations matrice utilisent la mise à l'échelle de la luminosité et les effets d'onde pour un flux visuel fluide.
- Suivi d'état d'animation statique par mode pour des transitions d'animation transparentes.
- Calcul d'onde diagonale optimisé pour les performances sur une matrice de 64 LEDs.

## [0.14.1] – Correction initialisation matrice 8x8 (2026-01-11)
### Corrigé
- **Pin GPIO matrice** : Changement du GPIO 27 vers GPIO 15 (plus stable au démarrage, pas de conflit boot).
- **Séquence d'initialisation matrice** : Ordre corrigé en `begin() → clear() → setBrightness() → show()` avec délai de stabilisation de 10ms.
- **Changement d'affichage** : Ajout de désactivation explicite des pins PWM lors du passage en mode matrice (état haute impédance).
- **Stabilité changement de mode** : Ajout de délais de 50ms lors des changements de type d'affichage pour assurer la stabilisation hardware.
- **Organisation du code** : Déplacement de la déclaration du strip NeoPixel en début de fichier pour corriger les problèmes d'ordre de compilation.
- **LEDs fantômes** : Correction des LEDs PWM résiduelles qui s'allumaient lorsque la matrice était sélectionnée.
- **Contrôle de luminosité** : Correction de l'application de la luminosité matrice lors de l'initialisation.

### Détails techniques
- Les pins PWM sont maintenant correctement détachés et mis en mode INPUT lorsque la matrice est active.
- Le buffer de la matrice est correctement effacé et affiché lors des transitions de mode.
- Les appels `showUniversal()` assurent que toutes les animations mettent à jour l'affichage correctement.

## [0.14.0] – Nettoyage et optimisation des modes (2026-01-11)
### Supprimé
- **MODE_ZEN** : Mode redondant supprimé (doublon de Pulse Vert).
- **MODE_DISCO** : Supprimé (similaire à Jackpot).
- **MODE_ARC_EN_CIEL_TURBO** : Supprimé (fusionné dans Arc-en-ciel avec sous-modes de vitesse).

### Modifié
- **MODE_ARC_EN_CIEL** : Utilise maintenant des sous-modes de vitesse (Lent/Moyen/Rapide) au lieu de l'inversion de direction.
- Mode de démarrage par défaut changé de ZEN à PULSE_VERT.
- Enum Mode réindexé pour cohérence (17 modes au lieu de 20).
- Boutons de l'UI web correctement alignés avec les nouveaux indices de modes.

### Corrigé
- La sélection de mode dans l'UI web met maintenant correctement en surbrillance le mode actif.
- Logique d'affichage des sous-modes mise à jour pour la nouvelle structure.

## [0.13.0] – Refonte complète de l'interface web festive (2026-01-11)
### Ajouté
- Refonte complète de l'interface web avec un style moderne, festif et professionnel.
- Design glassmorphism avec fonds dégradés et effets de flou.
- Animations fluides (effets float, pulse, glow).
- Intégration de Google Fonts (police Poppins).
- Amélioration des boutons de palette de couleurs (plus grands, parfaitement ronds, infobulles).
- Style dédié pour les boutons de sous-modes avec espace réservé pour éviter les sauts d'interface.
- Effets de survol améliorés et retour visuel renforcé.
- Design responsive optimisé pour mobile et ordinateur.

### Modifié
- L'interface web utilise maintenant des dégradés CSS modernes et des filtres backdrop.
- Les zones de sous-modes ont une hauteur fixe (60px) pour maintenir une mise en page cohérente.
- Boutons d'humeur du patron agrandis de 48px à 60px pour une meilleure accessibilité.
- Titre de l'interface avec dégradé animé et décorations emoji.

### Corrigé
- Les sous-modes s'affichent maintenant correctement lors de la sélection d'un mode.
- Les sous-modes sont cliquables et fonctionnels avec un style dédié.
- L'interface ne saute plus lorsque les sous-modes apparaissent/disparaissent.

## [1.0.0] – Refonte UI web moderne (2026-01-11)
### Ajouté
- Nouvelle interface web moderne, interactive et responsive.
- Sélection exclusive du type d’affichage (PWM ou matrice) via l’UI.
- Section paramètres dédiée.

## [1.1.0] – Persistance des réglages (2026-01-11)
### Ajouté
- Sauvegarde/restauration du type d’affichage (NVS).
- Sauvegarde/restauration de la luminosité matrice.

## [1.2.0] – Endpoints AJAX robustes (2026-01-11)
### Ajouté
- Endpoints /mode, /display, /brightness, /humeur, /status, /auto (supprimé ensuite).
- Gestion complète des actions UI côté firmware.

## [1.2.1] – Correction JS/C++ et robustesse (2026-01-11)
### Corrigé
- Correction des conversions JS/C++ pour la génération de page web.
- Correction des bugs de string et d’initialisation.

## [1.3.0] – Parité PWM/matrice et extinction propre (2026-01-11)
### Ajouté
- Extinction automatique des LEDs lors du changement d’affichage.
- Réinitialisation hardware lors du switch PWM/matrice.

## [1.4.0] – Humeur du Patron RGB sur matrice (2026-01-11)
### Ajouté
- Affichage de la couleur sélectionnée sur les trois feux de la matrice (palette RGB complète).
- Parité totale PWM/matrice pour ce mode.

## [1.4.1] – Suppression du mode automatique horaire (2026-01-11)
### Supprimé
- Suppression complète du mode automatique dépendant de l’horaire (backend, UI, endpoints).

## [1.4.2] – Nettoyage commentaires et historique (2026-01-11)
### Corrigé
- Suppression de toute référence à Copilot dans les commentaires et changelogs.

## Historique — Branche dev/8x8
# Historique :
#   - v0.12.0-dev8x8 : Ajout matrice NeoPixel 8x8, mapping feux, doc synchronisée
#   - v0.11.x et antérieures : PWM modules classiques uniquement
#
## [0.12.0-dev8x8] – Intégration matrice NeoPixel 8x8 (2026-01-10)
### Ajouté

## [0.12.0-dev8x8] – Sélection d’affichage PWM/Matrice, UI web, persistance (2026-01-10)
### Ajouté
- **Sélection exclusive du système d’affichage** : modules PWM classiques *ou* matrice NeoPixel 8x8, jamais simultanés.
- **Choix modifiable à chaud via l’interface web** (radio bouton).
- **Persistance automatique** du choix d’affichage (sauvegarde/restauration en mémoire NVS).
- **Helpers universels** : toute la logique d’animation utilise désormais des helpers abstraits, compatibles PWM et matrice.
- **Synchronisation complète de la documentation** (FR/EN).

### Modifié
- Refactorisation de tout le code d’animation pour utiliser les helpers universels.
- Web UI : nouvelle section pour le choix d’affichage, header simplifié.

### Impact utilisateur
- Le firmware démarre toujours avec le dernier affichage choisi (PWM ou matrice).
- Changement immédiat via l’UI web, sans redémarrage.
- Documentation et guides mis à jour.

---

- README, guides hardware et changelogs mis à jour pour la matrice

#
## [0.11.3] – Nouveau mapping GPIO ESP32-S3 (2026-01-09)
### Modifié
- Mise à jour du mapping GPIO pour l'environnement `esp32s3_n16r8` (ESP32-S3 DevKitC-1 N16R8) :
  - Module 0 : Rouge 1, Jaune 2, Vert 42
  - Module 1 : Rouge 41, Jaune 40, Vert 39
  - Module 2 : Rouge 4, Jaune 5, Vert 6
  - Module 3 : Rouge 7, Jaune 15, Vert 16
  - Boutons : 21 (mode), 20 (sous-mode)
- Tous les documents utilisateur (FR + EN) ont été mis à jour pour refléter ce mapping et garantir la cohérence avec le code source.

# Journal des modifications — Totem Feux du Tabac
Toutes les évolutions importantes du projet sont documentées ici.

Le projet suit le schéma **Semantic Versioning (SemVer)** :  
**MAJEUR.MINEUR.CORRECTIF**

---

## [0.11.2] – Corrections anti-bootloop ESP32-S3 (2026-01-09)
### Corrigé
- **Problème critique de bootloop sur ESP32-S3** causé par le choix de GPIO non sécurisés.
- GPIO 1, 2 maintenant évités (UART0).
- GPIO 0 maintenant évité (risque bouton boot).
- GPIO 45, 46 maintenant évités (strapping pins).
- GPIO 26-32 maintenant évités (input-only sur S3).

### Modifié
- Mapping GPIO ESP32-S3 mise à jour vers GPIO 3-16 (100% sécurisé pour PWM).
- Nouveau mapping : Module 1 (GPIO 3-5), Module 2 (GPIO 6-8), Module 3 (GPIO 9-11), Module 4 (GPIO 12-14), Boutons (GPIO 15-16).
- Documentation mise à jour pour refléter l'allocation réelle des GPIO.

### Impact utilisateur
- ESP32-S3 maintenant stable sans risque de bootloop.
- Le câblage matériel doit utiliser GPIO 3-16 pour les LEDs.

---

## [0.11.1] – Nettoyage des noms d'environnements (2026-01-09)
### Modifié
- Environnement renommé de `upesy_wroom` à `esp32devkit` pour la clarté.
- Spécification de la carte changée à `esp32doit-devkit1` (board standard PlatformIO).
- Flag de compilation changé de `-D ENV_ESP32_CLASSIC` à `-D ENV_ESP32_DEVKIT`.

---

## [0.11.0] – Stabilisation de l'architecture multi-environnements (2026-01-09)
### Ajouté
- Section commune `[env]` dans `platformio.ini` pour partager la configuration.
- Système d'héritage basé sur les flags (`${env.build_flags}`, `${env.lib_deps}`).
- Décodeur d'exceptions pour le débogage ESP32-S3.

### Modifié
- `platformio.ini` restructuré pour une meilleure maintenabilité.
- Les deux environnements héritent maintenant des paramètres communs.
- Environnement par défaut défini sur `esp32devkit`.

---

## [0.10.0] – Refactorisation de la configuration GPIO (2026-01-09)
### Ajouté
- Nouvelle section de configuration commune `[env]` dans `platformio.ini`.
- Toutes les dépendances centralisées dans la section commune.
- Flags de compilation et vitesses de monitoring unifiés.

### Modifié
- `esp32devkit` et `esp32s3_n16r8` héritent maintenant de `[env]`.
- Réduction de la duplication de configuration.
- Structure de projet plus propre et maintenable.

---

## [0.9.0] – Architecture multi-environnements (2026-01-09)
### Ajouté
- **Nouvel environnement ESP32-S3 DevKitC-1 N16R8** avec support PSRAM.
- Section `[env]` commune dans `platformio.ini` pour mutualiser les dépendances et flags.
- Système de mapping GPIO multi-environnements dans `board_config.h`.
- Flag de compilation `-D ENV_UPESY_WROOM` et `-D ENV_ESP32S3_N16R8` pour sélection automatique du mapping.
- Mapping GPIO sécurisé pour ESP32-S3 (GPIO 1-14) évitant les GPIO sensibles au boot et USB/JTAG.
- Librairies complètes ajoutées : Adafruit BusIO, GFX, ST7735/ST7789, TinyGPSPlus, U8g2.

### Modifié
- Restructuration complète de `platformio.ini` avec héritage des configurations communes.
- `board_config.h` maintenant avec deux mappings distincts protégés par `#ifdef`.
- Mapping UPESY_WROOM conservé strictement à l'identique (aucune modification).
- Version incrémentée de 0.8.0 → 0.9.0.

### Impact utilisateur
- Le projet compile désormais pour deux cartes ESP32 différentes.
- Possibilité de choisir l'environnement via PlatformIO : `upesy_wroom` ou `esp32s3_n16r8`.
- Aucun impact sur le comportement des modes lumineux existants.

### Impact développeur
- Ajout de nouveaux environnements facilité via la section `[env]` commune.
- Mapping GPIO modulaire et extensible.
- Meilleure organisation du code avec séparation claire des configurations matérielles.

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

