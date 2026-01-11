// Persistance du choix d'affichage (NVS)
void loadDisplayTypeFromNVS();
void saveDisplayTypeToNVS();
#ifndef MODES_H
#define MODES_H

#include <Arduino.h>
#include "board_config.h"

enum Mode {
    MODE_AMBIANCE_DOUCE,      // 0
    MODE_VAGUE,               // 1
    MODE_ARC_EN_CIEL,         // 2 (avec sous-modes vitesse)
    MODE_PULSE_VERT,          // 3
    MODE_PULSE_JAUNE,         // 4
    MODE_PULSE_ROUGE,         // 5
    MODE_RUSH,                // 6
    MODE_K2000,               // 7
    MODE_JACKPOT,             // 8
    MODE_FDJ_WINNER,          // 9
    MODE_CLIENT_GAGNANT,      // 10
    MODE_CLIENT_PERDANT,      // 11
    MODE_OUVERTURE,           // 12
    MODE_FERMETURE,           // 13
    MODE_PAUSE_CAFE,          // 14
    MODE_MAINTENANCE,         // 15
    MODE_HUMEUR_PATRON,       // 16
    MODE_MAX
};

extern Mode currentMode;


extern int humeurColor; // 0..5
extern int subMode;     // sous-mode courant


// Sélection du type d'affichage : PWM (modules) ou matrice NeoPixel
enum DisplayType {
    DISPLAY_PWM = 0,
    DISPLAY_MATRIX = 1
};

extern DisplayType currentDisplayType;

void setDisplayType(DisplayType t);
DisplayType getDisplayType();

void initLights();
void setMode(Mode m);
void updateMode();
void allOff();
void nextMode();

#endif
