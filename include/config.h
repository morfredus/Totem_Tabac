#ifndef CONFIG_H
#define CONFIG_H

// =========================================================
// CONFIGURATION UTILISATEUR — MODIFIEZ CES PARAMÈTRES
// =========================================================

// Nom mDNS: accessible via http://<MDNS_NAME>.local
// Exemples: "Totem-Tabac", "mon-totem", "tabac-neon"
// (Utilise uniquement des lettres, chiffres et tirets)
#define MDNS_NAME "Totem-Tabac"

// Port du serveur web HTTP (80 par défaut)
#define HTTP_SERVER_PORT 80

// Port OTA ArduinoOTA (3232 par défaut)
#define OTA_PORT 3232

// Nom du hostname ArduinoOTA (utilisé aussi pour mDNS)
#define OTA_HOSTNAME "Totem-Tabac"

// Type d'affichage par défaut au démarrage (DISPLAY_PWM ou DISPLAY_MATRIX)
// DISPLAY_PWM = modules PWM (0)
// DISPLAY_MATRIX = matrice 8x8 NeoPixel (1)
#define DEFAULT_DISPLAY_TYPE DISPLAY_PWM

// Mode par défaut au démarrage (voir enum Mode dans modes.h)
// 0=AMBIANCE_DOUCE, 1=VAGUE, 2=ARC_EN_CIEL, 3=PULSE_VERT, etc.
#define DEFAULT_MODE 3  // MODE_PULSE_VERT

// Luminosité matrice par défaut (0-255)
#define DEFAULT_MATRIX_BRIGHTNESS 200

// Activation du mot de passe OTA (décommentez pour activer)
// #define OTA_PASSWORD "totem2026"

#endif // CONFIG_H
