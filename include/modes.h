#ifndef MODES_H
#define MODES_H

#include <Arduino.h>
#include "board_config.h"

enum Mode {
    MODE_ZEN,
    MODE_AMBIANCE_DOUCE,
    MODE_VAGUE,
    MODE_ARC_EN_CIEL,
    MODE_ARC_EN_CIEL_TURBO,
    MODE_PULSE_VERT,
    MODE_PULSE_JAUNE,
    MODE_PULSE_ROUGE,
    MODE_RUSH,
    MODE_K2000,
    MODE_DISCO,
    MODE_JACKPOT,
    MODE_FDJ_WINNER,
    MODE_CLIENT_GAGNANT,
    MODE_CLIENT_PERDANT,
    MODE_OUVERTURE,
    MODE_FERMETURE,
    MODE_PAUSE_CAFE,
    MODE_MAINTENANCE,
    MODE_HUMEUR_PATRON,
    MODE_MAX
};

extern Mode currentMode;

extern bool autoModeEnabled;
extern int autoMorningHour;
extern int autoEveningHour;

extern int humeurColor; // 0..5
extern int subMode;     // sous-mode courant

void initLights();
void setMode(Mode m);
void updateMode();
void allOff();
void nextMode();

#endif
