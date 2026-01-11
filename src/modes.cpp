
#include "modes.h"
#include <Preferences.h>
// --- Persistance du choix d'affichage (NVS) ---
static Preferences displayPrefs;

void loadDisplayTypeFromNVS() {
    displayPrefs.begin("display", true); // lecture seule
    int val = displayPrefs.getInt("type", (int)DISPLAY_PWM);
    currentDisplayType = (val == (int)DISPLAY_MATRIX) ? DISPLAY_MATRIX : DISPLAY_PWM;
    displayPrefs.end();
}

void saveDisplayTypeToNVS() {
    displayPrefs.begin("display", false); // écriture
    displayPrefs.putInt("type", (int)currentDisplayType);
    displayPrefs.end();
}
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

// Variable globale pour le type d'affichage (PWM ou matrice)
DisplayType currentDisplayType = DISPLAY_PWM;
// --- Getter/setter pour le type d'affichage ---
void setDisplayType(DisplayType t) {
    if (t != currentDisplayType) {
        // Éteint tout lors du changement d’affichage
        if (currentDisplayType == DISPLAY_MATRIX) {
            clearMatrix();
        } else {
            clearAll();
        }
        currentDisplayType = t;
        saveDisplayTypeToNVS();
        initLightsUniversal(); // Réinitialise PWM ou matrice selon le mode
        setMode(currentMode); // Relance l'animation courante avec le bon moteur
    }
}

DisplayType getDisplayType() {
    return currentDisplayType;
}

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
            clearModuleUniversal(i);
            setGreenUniversal(i, b);
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
            clearModuleUniversal(i);
            setYellowUniversal(i, b);
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
            clearModuleUniversal(i);
            setRedUniversal(i, b);
        }

        fadeStep++;
        lastFadeUpdate = now;
    }
}

// ---------------------------------------------------------
// INITIALISATION DES FEUX
// ---------------------------------------------------------

void initLights() {
    initLightsUniversal();
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
    clearAllUniversal();
}

void nextMode() {
    int m = (int)currentMode;
    m = (m + 1) % MODE_MAX;
    setMode((Mode)m);
}



// ---------------------------------------------------------
// HUMEUR DU PATRON
// ---------------------------------------------------------

static void applyHumeurColor() {
    clearAllUniversal();
    if (getDisplayType() == DISPLAY_MATRIX) {
        // Palette RGB complète pour la matrice (correspond à humeurColor)
        uint8_t colors[6][3] = {
            {0, 255, 0},      // Vert
            {255, 255, 0},    // Jaune
            {255, 0, 0},      // Rouge
            {0, 0, 255},      // Bleu
            {255, 0, 255},    // Magenta
            {255, 255, 255}   // Blanc
        };
        uint8_t r = colors[humeurColor][0];
        uint8_t g = colors[humeurColor][1];
        uint8_t b = colors[humeurColor][2];
        // Pour chaque feu (3 feux sur la matrice)
        for (int feu = 0; feu < 3; feu++) {
            // Chaque feu a 4 pixels pour chaque couleur (rouge, jaune, vert)
            // On éclaire tous les pixels du feu avec la couleur sélectionnée
            for (int i = 0; i < 4; i++) {
                extern const uint8_t RED_PIXELS[3][4];
                extern const uint8_t YELLOW_PIXELS[3][4];
                extern const uint8_t GREEN_PIXELS[3][4];
                // Allume tous les pixels du feu
                setPixelXY(RED_PIXELS[feu][i] % 8, RED_PIXELS[feu][i] / 8, r, g, b);
                setPixelXY(YELLOW_PIXELS[feu][i] % 8, YELLOW_PIXELS[feu][i] / 8, r, g, b);
                setPixelXY(GREEN_PIXELS[feu][i] % 8, GREEN_PIXELS[feu][i] / 8, r, g, b);
            }
        }
    } else {
        // PWM classique : couleurs limitées
        switch (humeurColor) {
            case 0: setGreenUniversal(3, 255); break;
            case 1: setYellowUniversal(3, 255); break;
            case 2: setRedUniversal(3, 255); break;
            case 3: setRGBUniversal(3, false, false, 255); break;
            case 4: setRGBUniversal(3, true, false, 80); break;
            case 5: setRGBUniversal(3, true, true, 255); break;
        }
    }
}

// ---------------------------------------------------------
// UPDATE MODE
// ---------------------------------------------------------

void updateMode() {
    unsigned long now = millis();


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
                clearModuleUniversal(i);
                setYellowUniversal(i, 80);
                setGreenUniversal(i, b);
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
            clearAllUniversal();
            int pos = animStep % 4;
            setGreenUniversal(pos, 255);
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
                clearModuleUniversal(i);

                int s = (step + (subMode == 1 ? -i : i)) % 6;
                if (s < 0) s += 6;

                switch (s) {
                    case 0: setRedUniversal(i, 255); break;
                    case 1: setYellowUniversal(i, 255); break;
                    case 2: setGreenUniversal(i, 255); break;
                    case 3: setRGBUniversal(i, true, true, 0); break;
                    case 4: setRGBUniversal(i, true, false, 80); break;
                    case 5: setRGBUniversal(i, true, true, 255); break;
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
                clearModuleUniversal(i);
                setRedUniversal(i, on ? 255 : 0);
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

            clearAllUniversal();

            // Intensités de la queue lumineuse
            const uint8_t T0 = 255;  // point principal
            const uint8_t T1 = 150;  // 1er niveau de fade
            const uint8_t T2 = 60;   // 2e niveau de fade

            // Allume le point principal
            setRedUniversal(pos, T0);
            setYellowUniversal(pos, T0);
            setGreenUniversal(pos, T0);

            // Queue lumineuse derrière le point
            int p1 = pos - dir;      // juste derrière
            int p2 = pos - 2 * dir;  // encore derrière

            if (p1 >= 0 && p1 < 4) {
                setRedUniversal(p1, T1);
                setYellowUniversal(p1, T1);
                setGreenUniversal(p1, T1);
            }

            if (p2 >= 0 && p2 < 4) {
                setRedUniversal(p2, T2);
                setYellowUniversal(p2, T2);
                setGreenUniversal(p2, T2);
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
                clearModuleUniversal(i);
                setRedUniversal(i, random(255));
                setYellowUniversal(i, random(255));
                setGreenUniversal(i, random(255));
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
                    clearModuleUniversal(i);
                    setRGBUniversal(i, true, true, 255);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    clearModuleUniversal(i);
                    setRedUniversal(i, random(255));
                    setYellowUniversal(i, random(255));
                    setGreenUniversal(i, random(255));
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
                    clearModuleUniversal(i);
                    setYellowUniversal(i, on ? 255 : 0);
                }
            }
            else if (animStep < 20) {
                clearAllUniversal();
                int pos = animStep - 10;
                if (pos < 4) setGreenUniversal(pos, 255);
            }
            else {
                for (int i = 0; i < 4; i++) {
                    clearModuleUniversal(i);
                    setGreenUniversal(i, 255);
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
                    clearModuleUniversal(i);
                    setRedUniversal(i, random(255));
                    setYellowUniversal(i, random(255));
                    setGreenUniversal(i, random(255));
                }
            }
            else {
                for (int i = 0; i < 4; i++) {
                    clearModuleUniversal(i);
                    setGreenUniversal(i, 255);
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
                clearModuleUniversal(i);
                setRedUniversal(i, 255);
                if (flash) setYellowUniversal(i, 255);
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
            clearModuleUniversal(i);
            setGreenUniversal(i, 255);
        }
        break;

    // -----------------------------------------------------
    // 16. MODE_FERMETURE
    // -----------------------------------------------------
    case MODE_FERMETURE:
        for (int i = 0; i < 4; i++) {
            clearModuleUniversal(i);
            setRedUniversal(i, 255);
        }
        break;

    // -----------------------------------------------------
    // 17. MODE_PAUSE_CAFE
    // -----------------------------------------------------
    case MODE_PAUSE_CAFE:
        if (now - lastUpdate > 300) {
            bool blink = animStep % 2;

            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setYellowUniversal(i, 255);
                if (blink) setGreenUniversal(i, 255);
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

            for (int i = 0; i < 4; i++) clearModuleUniversal(i);

            switch (phase) {
                case 0: for (int i = 0; i < 4; i++) setRedUniversal(i, 255); break;
                case 1: for (int i = 0; i < 4; i++) setYellowUniversal(i, 255); break;
                case 2: for (int i = 0; i < 4; i++) setGreenUniversal(i, 255); break;
                case 3: for (int i = 0; i < 4; i++) setRGBUniversal(i, true, true, 255); break;
                case 4: for (int i = 0; i < 4; i++) setRGBUniversal(i, true, false, 80); break;
                case 5: for (int i = 0; i < 4; i++) setRGBUniversal(i, false, false, 255); break;
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
                clearModuleUniversal(i);

                int s = (step + i) % 6;

                switch (s) {
                    case 0: setRedUniversal(i, 255); break;
                    case 1: setYellowUniversal(i, 255); break;
                    case 2: setGreenUniversal(i, 255); break;
                    case 3: setRGBUniversal(i, true, true, 0); break;
                    case 4: setRGBUniversal(i, true, false, 80); break;
                    case 5: setRGBUniversal(i, true, true, 255); break;
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
        clearAllUniversal();
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
