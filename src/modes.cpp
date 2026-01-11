
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

// --- Persistance du mode actuel et sous-mode (NVS) ---
static Preferences modePrefs;

void loadModeFromNVS() {
    modePrefs.begin("mode", true); // lecture seule
    int m = modePrefs.getInt("current", (int)MODE_PULSE_VERT);
    int sub = modePrefs.getInt("submode", 0);
    int hum = modePrefs.getInt("humeur", 0);
    modePrefs.end();
    
    currentMode = (Mode)m;
    subMode = sub;
    humeurColor = hum;
}

void saveCurrentModeToNVS() {
    modePrefs.begin("mode", false); // écriture
    modePrefs.putInt("current", (int)currentMode);
    modePrefs.putInt("submode", subMode);
    modePrefs.putInt("humeur", humeurColor);
    modePrefs.end();
}
#include "modes.h"
#include "wifi_manager.h"
#include "light_helpers.h"
#include <Arduino.h>

// ---------------------------------------------------------
// VARIABLES GLOBALES
// ---------------------------------------------------------


Mode currentMode = MODE_PULSE_VERT;
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
            showMatrix();
        } else {
            clearAll();
        }
        currentDisplayType = t;
        saveDisplayTypeToNVS();
        delay(50); // Laisser le temps au hardware de se stabiliser
        initLightsUniversal(); // Réinitialise PWM ou matrice selon le mode
        clearAllUniversal(); // Clear avec le nouveau type
        showUniversal();
        delay(50);
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
        showUniversal();

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
        showUniversal();

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
        showUniversal();

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
    saveCurrentModeToNVS(); // Sauvegarder le nouveau mode
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
        
        // Vague diagonale avec fading (jamais complètement éteint)
        unsigned long now = millis();
        static unsigned long lastWaveUpdate = 0;
        static int wavePhase = 0;
        
        if (now - lastWaveUpdate > 100) {
            lastWaveUpdate = now;
            wavePhase = (wavePhase + 1) % 16;
        }
        
        // Remplir la matrice 8x8 avec vague diagonale
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                int diag = (x + y) % 8;
                int distance = abs(diag - (wavePhase % 8));
                if (distance > 4) distance = 8 - distance;
                
                // Fading de 30% à 100%
                uint8_t brightness = (30 + (70 * (4 - distance)) / 4);
                brightness = constrain(brightness, 30, 255);
                
                uint8_t scaled_r = (r * brightness) / 255;
                uint8_t scaled_g = (g * brightness) / 255;
                uint8_t scaled_b = (b * brightness) / 255;
                
                setPixelXY(x, y, scaled_r, scaled_g, scaled_b);
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
    showUniversal();
}

// --- Fonctions helper pour animations matrice ---
static void drawSmileySmiley(uint8_t r, uint8_t g, uint8_t b) {
    // Remplir tout en couleur
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            setPixelXY(x, y, r, g, b);
        }
    }
    // Yeux (pixels éteints)
    setPixelXY(2, 2, 0, 0, 0);
    setPixelXY(5, 2, 0, 0, 0);
    // Sourire (pixels éteints) - arc de cercle
    setPixelXY(2, 5, 0, 0, 0);
    setPixelXY(3, 6, 0, 0, 0);
    setPixelXY(4, 6, 0, 0, 0);
    setPixelXY(5, 5, 0, 0, 0);
}

static void drawSmileyNeutral(uint8_t r, uint8_t g, uint8_t b) {
    // Remplir tout en couleur
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            setPixelXY(x, y, r, g, b);
        }
    }
    // Yeux (pixels éteints)
    setPixelXY(2, 2, 0, 0, 0);
    setPixelXY(5, 2, 0, 0, 0);
    // Bouche neutre (pixels éteints) - ligne horizontale
    setPixelXY(2, 5, 0, 0, 0);
    setPixelXY(3, 5, 0, 0, 0);
    setPixelXY(4, 5, 0, 0, 0);
    setPixelXY(5, 5, 0, 0, 0);
}

static void drawAnimationOuverture() {
    // Matrice verte avec smiley heureux
    drawSmileySmiley(0, 255, 0);
}

static void drawAnimationFermeture() {
    // Matrice rouge avec smiley neutre
    drawSmileyNeutral(255, 0, 0);
}

static void drawAnimationPauseCafe() {
    unsigned long now = millis();
    static unsigned long lastCoffeeUpdate = 0;
    static int coffeeStep = 0;
    
    if (now - lastCoffeeUpdate > 200) {
        lastCoffeeUpdate = now;
        coffeeStep = (coffeeStep + 1) % 4;
    }
    
    // Animation café avec bulles remontantes et couleur chaude
    clearAllUniversal();
    uint8_t hue = (now / 10) % 256;
    
    // Fond marron/orange chaud
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int brightness = 150 + (50 * sin((x + y + coffeeStep * 2) * 0.5)) / 1;
            brightness = constrain(brightness, 100, 200);
            setPixelXY(x, y, brightness, brightness / 2, 0); // Marron chaud
        }
    }
    
    // Bulles montantes
    for (int i = 0; i < 3; i++) {
        int bubbleY = (coffeeStep * 2 + i * 3) % 8;
        int bubbleX = 2 + i * 2;
        if (bubbleX < 8 && bubbleY < 8) {
            setPixelXY(bubbleX, bubbleY, 200, 200, 255); // Blanc/bleu clair
        }
    }
}

static void drawAnimationClientGagnant() {
    unsigned long now = millis();
    static unsigned long lastWinUpdate = 0;
    static int winStep = 0;
    
    if (now - lastWinUpdate > 80) {
        lastWinUpdate = now;
        winStep = (winStep + 1) % 8;
    }
    
    clearAllUniversal();
    
    // Animation de joie : feu d'artifice de couleurs
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int dist = abs(x - 3.5) + abs(y - 3.5);
            int wave = ((dist + winStep * 2) % 8);
            
            if (wave < 2) {
                // Éclair jaune/blanc
                setPixelXY(x, y, 255, 255, 0);
            } else if (wave < 4) {
                // Transition vers vert
                setPixelXY(x, y, 0, 255, 100);
            } else {
                // Bleu/magenta
                setPixelXY(x, y, (sin(x * 0.5 + winStep) + 1) * 127, 0, (cos(y * 0.5 + winStep) + 1) * 127);
            }
        }
    }
}

static void drawAnimationClientPerdant() {
    unsigned long now = millis();
    static unsigned long lastLoseUpdate = 0;
    static int loseStep = 0;
    
    if (now - lastLoseUpdate > 150) {
        lastLoseUpdate = now;
        loseStep = (loseStep + 1) % 16;
    }
    
    clearAllUniversal();
    
    // Animation de tristesse : pluie rouge/bleu grise
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int rainPos = (y + loseStep * 3) % 16;
            
            if (rainPos == 0 || rainPos == 1) {
                // Gouttes qui tombent
                if ((x + rainPos) % 3 == 0) {
                    setPixelXY(x, y, 100, 100, 200); // Bleu grisé
                } else {
                    setPixelXY(x, y, 80, 20, 80); // Violet sombre
                }
            } else {
                setPixelXY(x, y, 40, 40, 80); // Fond gris bleuté
            }
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
    // MODE_AMBIANCE_DOUCE
    // -----------------------------------------------------
    case MODE_AMBIANCE_DOUCE:
        if (now - lastUpdate > 30) {
            int b = (sin(animStep * 0.04) + 1) * 100;
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setYellowUniversal(i, 80);
                setGreenUniversal(i, b);
            }
            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // MODE_VAGUE
    // -----------------------------------------------------
    case MODE_VAGUE:
        if (now - lastUpdate > 180) {
            clearAllUniversal();
            int pos = animStep % 4;
            setGreenUniversal(pos, 255);
            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // MODE_ARC_EN_CIEL (avec sous-modes de vitesse)
    // -----------------------------------------------------
    case MODE_ARC_EN_CIEL: {
        int delayMs = (subMode == 0 ? 150 : subMode == 1 ? 100 : 50);
        
        if (now - lastUpdate > (unsigned long)delayMs) {

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

            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;
    }

    // -----------------------------------------------------
    // MODE_PULSE_VERT
    // -----------------------------------------------------
    case MODE_PULSE_VERT:
        fadeGreen();
        break;

    // -----------------------------------------------------
    // MODE_PULSE_JAUNE
    // -----------------------------------------------------
    case MODE_PULSE_JAUNE:
        fadeYellow();
        break;

    // -----------------------------------------------------
    // MODE_PULSE_ROUGE
    // -----------------------------------------------------
    case MODE_PULSE_ROUGE:
        fadeRed();
        break;

    // -----------------------------------------------------
    // MODE_RUSH
    // -----------------------------------------------------
    case MODE_RUSH:
        if (now - lastUpdate > 120) {
            bool on = animStep % 2;
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setRedUniversal(i, on ? 255 : 0);
            }
            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // MODE_K2000 — vitesse corrigée
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

            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;
    }



    // -----------------------------------------------------
    // MODE_JACKPOT
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

            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;
    }

    // -----------------------------------------------------
    // MODE_FDJ_WINNER
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

            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // 13. MODE_CLIENT_GAGNANT
    case MODE_CLIENT_GAGNANT:
        if (getDisplayType() == DISPLAY_MATRIX) {
            drawAnimationClientGagnant();
            showUniversal();
        } else {
            if (now - lastUpdate > 120) {
                if (animStep < 12) {
                    for (int i = 0; i < 4; i++) {
                        clearModuleUniversal(i);
                        setRedUniversal(i, random(255));
                        setYellowUniversal(i, random(255));
                        setGreenUniversal(i, random(255));
                    }
                } else {
                    for (int i = 0; i < 4; i++) {
                        clearModuleUniversal(i);
                        setGreenUniversal(i, 255);
                    }
                }
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        }
        break;

    // -----------------------------------------------------
    // 14. MODE_CLIENT_PERDANT
    case MODE_CLIENT_PERDANT:
        if (getDisplayType() == DISPLAY_MATRIX) {
            drawAnimationClientPerdant();
            showUniversal();
        } else {
            if (now - lastUpdate > 180) {
                bool flash = animStep % 2;
                for (int i = 0; i < 4; i++) {
                    clearModuleUniversal(i);
                    setRedUniversal(i, 255);
                    if (flash) setYellowUniversal(i, 255);
                }
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        }
        break;

    // -----------------------------------------------------
    // 15. MODE_OUVERTURE
    case MODE_OUVERTURE:
        if (getDisplayType() == DISPLAY_MATRIX) {
            drawAnimationOuverture();
            showUniversal();
        } else {
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setGreenUniversal(i, 255);
            }
            showUniversal();
        }
        break;

    // -----------------------------------------------------
    // 16. MODE_FERMETURE
    case MODE_FERMETURE:
        if (getDisplayType() == DISPLAY_MATRIX) {
            drawAnimationFermeture();
            showUniversal();
        } else {
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setRedUniversal(i, 255);
            }
            showUniversal();
        }
        break;

    // -----------------------------------------------------
    // 17. MODE_PAUSE_CAFE
    case MODE_PAUSE_CAFE:
        if (getDisplayType() == DISPLAY_MATRIX) {
            drawAnimationPauseCafe();
            showUniversal();
        } else {
            if (now - lastUpdate > 300) {
                bool blink = animStep % 2;
                for (int i = 0; i < 4; i++) {
                    clearModuleUniversal(i);
                    setYellowUniversal(i, 255);
                    if (blink) setGreenUniversal(i, 255);
                }
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
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

            showUniversal();
            animStep++;
            lastUpdate = now;
        }
        break;

    // -----------------------------------------------------
    // MODE_HUMEUR_PATRON
    // -----------------------------------------------------
    case MODE_HUMEUR_PATRON:
        applyHumeurColor();
        break;

    default:
        clearAllUniversal();
        showUniversal();
        break;
    }
}

// ---------------------------------------------------------
// SOUS-MODES
// ---------------------------------------------------------

void nextSubMode() {

    switch (currentMode) {

        case MODE_ARC_EN_CIEL:
        case MODE_PULSE_VERT:
        case MODE_PULSE_JAUNE:
        case MODE_PULSE_ROUGE:
        case MODE_K2000:
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
    saveCurrentModeToNVS(); // Sauvegarder les changements de sous-mode/humeur
}
