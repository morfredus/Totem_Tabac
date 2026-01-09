#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// ========================================
// CONFIGURATION MULTI-ENVIRONNEMENTS
// ========================================
// Ce fichier définit le mapping GPIO pour différentes cartes ESP32.
// Le mapping est automatiquement sélectionné selon l'environnement PlatformIO compilé.

// ========================================
// ENVIRONNEMENT 1 : ESP32 DevKit (ESP32 classique)
// ========================================
// Mapping validé et éprouvé - NE PAS MODIFIER
#ifdef ENV_ESP32_DEVKIT

// MODULE 1
#define TL1_RED     4
#define TL1_YELLOW  5
#define TL1_GREEN   12

// MODULE 2
#define TL2_RED     13
#define TL2_YELLOW  14
#define TL2_GREEN   16

// MODULE 3
#define TL3_RED     17
#define TL3_YELLOW  18
#define TL3_GREEN   19

// MODULE 4
#define TL4_RED     21
#define TL4_YELLOW  22
#define TL4_GREEN   23

// Boutons physiques
#define BUTTON_PIN   25   // change de mode
#define BUTTON2_PIN  26   // change de sous-mode

#endif

// ========================================
// ENVIRONNEMENT 2 : ESP32-S3 DevKitC-1 N16R8
// ========================================
// Mapping ANTI-BOOTLOOP pour ESP32-S3
// ⚠️ ÉVITER ABSOLUMENT :
// ✗ GPIO 0: Bouton BOOT (provoque bootloop si en sortie)
// ✗ GPIO 45, 46: Strapping pins (danger critique)
// ✗ GPIO 26-32: Input-only sur S3
// ✗ GPIO 1, 2: UART0 (communication série)
// ✗ GPIO 19, 20: USB/JTAG sur certaines variantes
// ✓ GPIO 3-18: PWM safe et disponibles
// ✓ GPIO 21-25: PWM safe
// ✓ GPIO 33-44: PWM safe
//
// Arrangement physique : côté droit de la carte DevKitC-1
#ifdef ENV_ESP32S3_N16R8

// --- MODULE 1 (Haut Droit) ---
#define TL1_RED       1     // Haut droite
#define TL1_YELLOW    2     // Juste en dessous de 1
#define TL1_GREEN     42    // Juste en dessous de 2 (Safe)

// --- MODULE 2 (Milieu Droit) ---
#define TL2_RED       41    // Bloc milieu droite
#define TL2_YELLOW    40    // 
#define TL2_GREEN     39    // 

// --- MODULE 3 (Haut Gauche) ---
#define TL3_RED       4     // Haut gauche (sous 3V3/RST)
#define TL3_YELLOW    5     // 
#define TL3_GREEN     6     // 

// --- MODULE 4 (Milieu Gauche) ---
#define TL4_RED       7     // Bloc milieu gauche
#define TL4_YELLOW    15    // 
#define TL4_GREEN     16    // 

// --- BOUTONS (Bas Droit - Zone 19-21) ---
#define BUTTON_PIN    21    // Près des GND du bas
#define BUTTON2_PIN   20    //

#endif

// ========================================
// STRUCTURE COMMUNE À TOUS LES ENVIRONNEMENTS
// ========================================
struct TrafficLightPins {
    int red;
    int yellow;
    int green;
};

static const TrafficLightPins TRAFFIC_LIGHTS[4] = {
    { TL1_RED, TL1_YELLOW, TL1_GREEN },
    { TL2_RED, TL2_YELLOW, TL2_GREEN },
    { TL3_RED, TL3_YELLOW, TL3_GREEN },
    { TL4_RED, TL4_YELLOW, TL4_GREEN }
};

#endif
