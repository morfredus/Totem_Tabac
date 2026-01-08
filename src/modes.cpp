#include "modes.h"
#include "wifi_manager.h"
#include "light_helpers.h"
#include <Arduino.h>

// ---------------------------------------------------------
// VARIABLES GLOBALES
// ---------------------------------------------------------

Mode currentMode = MODE_ZEN;
int subMode = 0;
int humeurColor = 0;

bool autoModeEnabled = false;
int autoMorningHour = 8;
int autoEveningHour = 18;

static unsigned long lastUpdate = 0;
static int animStep = 0;

static unsigned long lastFadeUpdate = 0;
static int fadeStep = 0;

// ---------------------------------------------------------
// HELPERS : FADE / RESPIRATION
// ---------------------------------------------------------

static int getPulseDelayMs() {
    return (subMode == 0 ? 40 : subMode == 1 ? 20 : 10);
}

// Fade VERT
static void fadeGreen() {
    unsigned long now = millis();
    int delayMs = getPulseDelayMs();

    if (now - lastFadeUpdate > (unsigned long)delayMs) {
        int b = (sin(fadeStep * 0.06) + 1) * 127;

        for (int i = 0; i < 4; i++) {
            clearModule(i);
            setGreen(i, b);
        }

        fadeStep++;
        lastFadeUpdate = now;
    }
}

// Fade JAUNE (PWM jaune pur)
static void fadeYellow() {
    unsigned long now = millis();
    int delayMs = getPulseDelayMs();

    if (now - lastFadeUpdate > (unsigned long)delayMs) {
        int b = (sin(fadeStep * 0.06) + 1) * 127;

        for (int i = 0; i < 4; i++) {
            clearModule(i);
            setYellow(i, b);   // JAUNE PWM
        }

        fadeStep++;
        lastFadeUpdate = now;
    }
}

// Fade ROUGE (PWM rouge pur)
static void fadeRed() {
    unsigned long now = millis();
    int delayMs = getPulseDelayMs();

    if (now - lastFadeUpdate > (unsigned long)delayMs) {
        int b = (sin(fadeStep * 0.06) + 1) * 127;

        for (int i = 0; i < 4; i++) {
            clearModule(i);
            setRed(i, b);   // ROUGE PWM
        }

        fadeStep++;
        lastFadeUpdate = now;
    }
}

// ---------------------------------------------------------
// INITIALISATION DES FEUX
// ---------------------------------------------------------

void initLights() {
    for (int i = 0; i < 4; i++) {
        initTrafficLightPWM(i);
    }
    clearAll();
}

// ---------------------------------------------------------
// CHANGEMENT DE MODE
// ---------------------------------------------------------

void setMode(Mode m) {
    currentMode = m;
    animStep = 0;
    subMode = 0;
    fadeStep = 0;
    lastUpdate = millis();
    lastFadeUpdate = millis();
    clearAll();
}

void nextMode() {
    int m = (int)currentMode;
    m = (m + 1) % MODE_MAX;
    setMode((Mode)m);
}

// ---------------------------------------------------------
// AUTO-MODE
// ---------------------------------------------------------

static void handleAutoMode() {
    if (!autoModeEnabled) return;

    int hour;
    if (!getLocalHour(hour)) return;

    if (hour < autoMorningHour) {
        if (currentMode != MODE_FERMETURE) setMode(MODE_FERMETURE);
    }
    else if (hour < autoEveningHour) {
        if (currentMode != MODE_ZEN) setMode(MODE_ZEN);
    }
    else {
        if (currentMode != MODE_FERMETURE) setMode(MODE_FERMETURE);
    }
}

// ---------------------------------------------------------
// HUMEUR DU PATRON
// ---------------------------------------------------------

static void applyHumeurColor() {
    clearAll();
    switch (humeurColor) {
        case 0: setGreen(3, 255); break;
        case 1: setYellow(3, 255); break;
        case 2: setRed(3, 255); break;
        case 3: setRGB(3, false, false, 255); break;
        case 4: setRGB(3, true, false, 80); break;
        case 5: setRGB(3, true, true, 255); break;
    }
}

// ---------------------------------------------------------
// UPDATE MODE
// ---------------------------------------------------------

void updateMode() {
    unsigned long now = millis();
    handleAutoMode();

    switch (currentMode) {

    // -----------------------------------------------------
    // 1. MODE_ZEN — respiration verte lente
    // -----------------------------------------------------
    case MODE_ZEN:
        fadeGreen();
        break;

    // -----------------------------------------------------
    // 2. MODE_AMBIANCE_DOUCE
    // -----------------------------------------------------
    case MODE_AMBIANCE_DOUCE:
        if (now - lastUpdate > 30) {
            int b = (sin(animStep * 0.04) + 1) * 100;
            for (int i = 0; i < 4; i++) {
                clearModule(i);
                setYellow(i, 80);
                setGreen(i, b);
            }
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 3. MODE_VAGUE
    // -----------------------------------------------------
    case MODE_VAGUE:
        if (now - lastUpdate > 180) {
            clearAll();
            int pos = animStep % 4;
            setGreen(pos, 255);
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 4. MODE_ARC_EN_CIEL
    // -----------------------------------------------------
    case MODE_ARC_EN_CIEL:
        if (now - lastUpdate > 150) {

            int step = animStep % 6;

            for (int i = 0; i < 4; i++) {
                clearModule(i);

                int s = (step + (subMode == 1 ? -i : i)) % 6;
                if (s < 0) s += 6;

                switch (s) {
                    case 0: setRed(i, 255); break;
                    case 1: setYellow(i, 255); break;
                    case 2: setGreen(i, 255); break;
                    case 3: setRGB(i, true, true, 0); break;
                    case 4: setRGB(i, true, false, 80); break;
                    case 5: setRGB(i, true, true, 255); break;
                }
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 5. MODE_PULSE_VERT
    // -----------------------------------------------------
    case MODE_PULSE_VERT:
        fadeGreen();
        break;

    // -----------------------------------------------------
    // 6. MODE_PULSE_JAUNE
    // -----------------------------------------------------
    case MODE_PULSE_JAUNE:
        fadeYellow();
        break;

    // -----------------------------------------------------
    // 7. MODE_PULSE_ROUGE
    // -----------------------------------------------------
    case MODE_PULSE_ROUGE:
        fadeRed();
        break;

    // -----------------------------------------------------
    // 8. MODE_RUSH
    // -----------------------------------------------------
    case MODE_RUSH:
        if (now - lastUpdate > 120) {
            bool on = animStep % 2;
            for (int i = 0; i < 4; i++) {
                clearModule(i);
                setRed(i, on ? 255 : 0);
            }
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 9. MODE_K2000 — vitesse corrigée
    // -----------------------------------------------------
    case MODE_K2000: {
    // Vitesse selon sous-mode
    int delayMs = (subMode == 0 ? 150 : subMode == 1 ? 80 : 40);

    static int pos = 0;
    static int dir = 1;  // +1 = droite, -1 = gauche

    if (now - lastUpdate > (unsigned long)delayMs) {

            clearAll();

            // Intensités de la queue lumineuse
            const uint8_t T0 = 255;  // point principal
            const uint8_t T1 = 150;  // 1er niveau de fade
            const uint8_t T2 = 60;   // 2e niveau de fade

            // Allume le point principal
            setRed(pos, T0);
            setYellow(pos, T0);
            setGreen(pos, T0);

            // Queue lumineuse derrière le point
            int p1 = pos - dir;      // juste derrière
            int p2 = pos - 2 * dir;  // encore derrière

            if (p1 >= 0 && p1 < 4) {
                setRed(p1, T1);
                setYellow(p1, T1);
                setGreen(p1, T1);
            }

            if (p2 >= 0 && p2 < 4) {
                setRed(p2, T2);
                setYellow(p2, T2);
                setGreen(p2, T2);
            }

            // Avance
            pos += dir;

            // Inversion de direction
            if (pos >= 3) dir = -1;
            if (pos <= 0) dir = +1;

            animStep++;
            lastUpdate = now;
        }
        break;
    }



    // -----------------------------------------------------
    // 10. MODE_DISCO
    // -----------------------------------------------------
    case MODE_DISCO: {
        int delayMs = (subMode == 0 ? 180 : subMode == 1 ? 120 : 70);

        if (now - lastUpdate > (unsigned long)delayMs) {
            for (int i = 0; i < 4; i++) {
                clearModule(i);
                setRed(i, random(255));
                setYellow(i, random(255));
                setGreen(i, random(255));
            }
            animStep++;
            lastUpdate = now;
        }
        break;
    }

    // -----------------------------------------------------
    // 11. MODE_JACKPOT
    // -----------------------------------------------------
    case MODE_JACKPOT: {
        int delayMs = (subMode == 0 ? 150 : subMode == 1 ? 100 : 60);

        if (now - lastUpdate > (unsigned long)delayMs) {

            if (animStep % 8 == 0) {
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setRGB(i, true, true, 255);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setRed(i, random(255));
                    setYellow(i, random(255));
                    setGreen(i, random(255));
                }
            }

            animStep++;
            lastUpdate = now;
        }
        break;
    }

    // -----------------------------------------------------
    // 12. MODE_FDJ_WINNER
    // -----------------------------------------------------
    case MODE_FDJ_WINNER:
        if (now - lastUpdate > 100) {

            if (animStep < 10) {
                bool on = animStep % 2;
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setYellow(i, on ? 255 : 0);
                }
            }
            else if (animStep < 20) {
                clearAll();
                int pos = animStep - 10;
                if (pos < 4) setGreen(pos, 255);
            }
            else {
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setGreen(i, 255);
                }
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 13. MODE_CLIENT_GAGNANT
    // -----------------------------------------------------
    case MODE_CLIENT_GAGNANT:
        if (now - lastUpdate > 120) {

            if (animStep < 12) {
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setRed(i, random(255));
                    setYellow(i, random(255));
                    setGreen(i, random(255));
                }
            }
            else {
                for (int i = 0; i < 4; i++) {
                    clearModule(i);
                    setGreen(i, 255);
                }
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 14. MODE_CLIENT_PERDANT
    // -----------------------------------------------------
    case MODE_CLIENT_PERDANT:
        if (now - lastUpdate > 180) {

            bool flash = animStep % 2;

            for (int i = 0; i < 4; i++) {
                clearModule(i);
                setRed(i, 255);
                if (flash) setYellow(i, 255);
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 15. MODE_OUVERTURE
    // -----------------------------------------------------
    case MODE_OUVERTURE:
        for (int i = 0; i < 4; i++) {
            clearModule(i);
            setGreen(i, 255);
        }
        break;

    // -----------------------------------------------------
    // 16. MODE_FERMETURE
    // -----------------------------------------------------
    case MODE_FERMETURE:
        for (int i = 0; i < 4; i++) {
            clearModule(i);
            setRed(i, 255);
        }
        break;

    // -----------------------------------------------------
    // 17. MODE_PAUSE_CAFE
    // -----------------------------------------------------
    case MODE_PAUSE_CAFE:
        if (now - lastUpdate > 300) {
            bool blink = animStep % 2;

            for (int i = 0; i < 4; i++) {
                clearModule(i);
                setYellow(i, 255);
                if (blink) setGreen(i, 255);
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 18. MODE_MAINTENANCE
    // -----------------------------------------------------
    case MODE_MAINTENANCE:
        if (now - lastUpdate > 250) {

            int phase = animStep % 6;

            for (int i = 0; i < 4; i++) clearModule(i);

            switch (phase) {
                case 0: for (int i = 0; i < 4; i++) setRed(i, 255); break;
                case 1: for (int i = 0; i < 4; i++) setYellow(i, 255); break;
                case 2: for (int i = 0; i < 4; i++) setGreen(i, 255); break;
                case 3: for (int i = 0; i < 4; i++) setRGB(i, true, true, 255); break;
                case 4: for (int i = 0; i < 4; i++) setRGB(i, true, false, 80); break;
                case 5: for (int i = 0; i < 4; i++) setRGB(i, false, false, 255); break;
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 19. MODE_ARC_EN_CIEL_TURBO
    // -----------------------------------------------------
    case MODE_ARC_EN_CIEL_TURBO:
        if (now - lastUpdate > (subMode == 0 ? 120 : 60)) {

            int step = animStep % 6;

            for (int i = 0; i < 4; i++) {
                clearModule(i);

                int s = (step + i) % 6;

                switch (s) {
                    case 0: setRed(i, 255); break;
                    case 1: setYellow(i, 255); break;
                    case 2: setGreen(i, 255); break;
                    case 3: setRGB(i, true, true, 0); break;
                    case 4: setRGB(i, true, false, 80); break;
                    case 5: setRGB(i, true, true, 255); break;
                }
            }

            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 20. MODE_HUMEUR_PATRON
    // -----------------------------------------------------
    case MODE_HUMEUR_PATRON:
        applyHumeurColor();
        break;

    default:
        clearAll();
        break;
    }
}

// ---------------------------------------------------------
// SOUS-MODES
// ---------------------------------------------------------

void nextSubMode() {

    switch (currentMode) {

        case MODE_PULSE_VERT:
        case MODE_PULSE_JAUNE:
        case MODE_PULSE_ROUGE:
            subMode = (subMode + 1) % 3;
            break;

        case MODE_ARC_EN_CIEL:
        case MODE_ARC_EN_CIEL_TURBO:
        case MODE_K2000:
            subMode = (subMode + 1) % 2;
            break;

        case MODE_DISCO:
        case MODE_JACKPOT:
            subMode = (subMode + 1) % 3;
            break;

        case MODE_HUMEUR_PATRON:
            humeurColor = (humeurColor + 1) % 6;
            break;

        default:
            subMode = 0;
            break;
    }
}
