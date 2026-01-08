#ifndef SUBMODE_H
#define SUBMODE_H

#include "modes.h"

inline void nextSubMode() {
    subMode++;

    switch (currentMode) {

        case MODE_HUMEUR_PATRON:
            humeurColor = (humeurColor + 1) % 6;
            break;

        case MODE_PULSE_VERT:
        case MODE_PULSE_JAUNE:
        case MODE_PULSE_ROUGE:
            subMode %= 3; // 3 vitesses
            break;

        case MODE_ARC_EN_CIEL:
            subMode %= 2; // normal / inversé
            break;

        case MODE_K2000:
            subMode %= 2; // direction
            break;

        case MODE_DISCO:
        case MODE_JACKPOT:
            subMode %= 3; // 3 vitesses
            break;

        default:
            subMode = 0;
            break;
    }
}

#endif
