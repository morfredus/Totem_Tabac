
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

        if (getDisplayType() == DISPLAY_MATRIX) {
            // Pulse vert sur toute la matrice (avec légère variation spatiale)
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    int offset = (x + y) % 4; // ondulation subtile
                    uint8_t gv = constrain(b + offset * 6, 0, 255);
                    uint8_t r = 0, g = gv, bcol = 0;
                    applyMatrixBrightnessToRGB(r, g, bcol);
                    setPixelXY(x, y, r, g, bcol);
                }
            }
            showUniversal();
        } else {
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setGreenUniversal(i, b);
            }
            showUniversal();
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

        if (getDisplayType() == DISPLAY_MATRIX) {
            // Pulse jaune sur toute la matrice
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    int offset = ((x * 2 + y) % 5);
                    uint8_t rv = constrain(b + offset * 4, 0, 255);
                    uint8_t gv = constrain(b + offset * 4, 0, 255);
                    uint8_t bv = 0;
                    applyMatrixBrightnessToRGB(rv, gv, bv);
                    setPixelXY(x, y, rv, gv, bv);
                }
            }
            showUniversal();
        } else {
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setYellowUniversal(i, b);
            }
            showUniversal();
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

        if (getDisplayType() == DISPLAY_MATRIX) {
            // Pulse rouge sur toute la matrice
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    int offset = (abs(3 - (x % 7)) + y) % 5;
                    uint8_t rv = constrain(b + offset * 5, 0, 255);
                    uint8_t gv = 0, bv = 0;
                    applyMatrixBrightnessToRGB(rv, gv, bv);
                    setPixelXY(x, y, rv, gv, bv);
                }
            }
            showUniversal();
        } else {
            for (int i = 0; i < 4; i++) {
                clearModuleUniversal(i);
                setRedUniversal(i, b);
            }
            showUniversal();
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
                
                // Fading de 20% à 100% (plus accentué)
                uint8_t brightness = (20 + (80 * (4 - distance)) / 4);
                brightness = constrain(brightness, 20, 255);
                
                uint8_t scaled_r = (r * brightness) / 255;
                uint8_t scaled_g = (g * brightness) / 255;
                uint8_t scaled_b = (b * brightness) / 255;
                
                // Appliquer le brightness global
                applyMatrixBrightnessToRGB(scaled_r, scaled_g, scaled_b);
                
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
    // Appliquer brightness global
    applyMatrixBrightnessToRGB(r, g, b);
    
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
    // Appliquer brightness global
    applyMatrixBrightnessToRGB(r, g, b);
    
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
            uint8_t r = brightness;
            uint8_t g = brightness / 2;
            uint8_t b = 0;
            applyMatrixBrightnessToRGB(r, g, b);
            setPixelXY(x, y, r, g, b); // Marron chaud
        }
    }
    
    // Bulles montantes
    for (int i = 0; i < 3; i++) {
        int bubbleY = (coffeeStep * 2 + i * 3) % 8;
        int bubbleX = 2 + i * 2;
        if (bubbleX < 8 && bubbleY < 8) {
            uint8_t r = 200, g = 200, b = 255;
            applyMatrixBrightnessToRGB(r, g, b);
            setPixelXY(bubbleX, bubbleY, r, g, b); // Blanc/bleu clair
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
            
            uint8_t r, g, b;
            if (wave < 2) {
                // Éclair jaune/blanc
                r = 255; g = 255; b = 0;
            } else if (wave < 4) {
                // Transition vers vert
                r = 0; g = 255; b = 100;
            } else {
                // Bleu/magenta
                r = (sin(x * 0.5 + winStep) + 1) * 127;
                g = 0;
                b = (cos(y * 0.5 + winStep) + 1) * 127;
            }
            applyMatrixBrightnessToRGB(r, g, b);
            setPixelXY(x, y, r, g, b);
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
            
            uint8_t r, g, b;
            if (rainPos == 0 || rainPos == 1) {
                // Gouttes qui tombent
                if ((x + rainPos) % 3 == 0) {
                    r = 100; g = 100; b = 200; // Bleu grisé
                } else {
                    r = 80; g = 20; b = 80; // Violet sombre
                }
            } else {
                r = 40; g = 40; b = 80; // Fond gris bleuté
            }
            applyMatrixBrightnessToRGB(r, g, b);
            setPixelXY(x, y, r, g, b);
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
        if (getDisplayType() == DISPLAY_MATRIX) {
            if (now - lastUpdate > 40) {
                // Ambiance douce : fond chaud + respiration verte douce sur toute la matrice
                int breath = (sin(animStep * 0.05) + 1) * 100; // 0..200
                clearAllUniversal();
                for (int y = 0; y < 8; y++) {
                    for (int x = 0; x < 8; x++) {
                        // Accentuer légèrement près des colonnes 0,3,6 (masque potentiel)
                        int distCol = min(min(abs(x-0), abs(x-3)), abs(x-6));
                        int accent = max(0, 3 - distCol) * 12; // 0..36
                        uint8_t r = 220, g = 160 + accent, b = 0; // base chaude
                        // respiration verte superposée
                        uint8_t gv = constrain(breath + accent, 0, 255);
                        g = min<uint8_t>(255, g/2 + gv);
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, y, r, g, b);
                    }
                }
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
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
        }
        break;

    // -----------------------------------------------------
    // MODE_VAGUE
    // -----------------------------------------------------
    case MODE_VAGUE:
        if (getDisplayType() == DISPLAY_MATRIX) {
            // Nouvelle "vague" façon mer : sinusoïde horizontale avec crêtes blanches,
            // dégradé bleu/cyan, full-matrix. Vitesse selon sous-mode.
            int delayMs = (subMode == 0 ? 120 : subMode == 1 ? 80 : 55);
            if (now - lastUpdate > (unsigned long)delayMs) {
                clearAllUniversal();
                float phase = animStep * 0.35f; // progression de la vague
                for (int x = 0; x < 8; x++) {
                    // Position de la crête principale (sinus horizontal)
                    float crestYf = 3.5f + 2.5f * sinf(phase + x * 0.7f);
                    // Seconde harmonique déphasée (écume supplémentaire)
                    float crestYf2 = 3.5f + 1.3f * sinf(phase + x * 1.2f + 1.57f);
                    for (int y = 0; y < 8; y++) {
                        float d = fabsf((float)y - crestYf);
                        float d2 = fabsf((float)y - crestYf2);
                        uint8_t r = 0, g = 0, b = 0;
                        if (d < 0.4f) {
                            // Crête blanche (écume)
                            r = 220; g = 235; b = 255;
                        } else if (d < 1.2f) {
                            // Proche de la crête : cyan éclatant
                            r = 0; g = 200; b = 255;
                        } else if (d < 2.2f) {
                            // Corps de vague : bleu soutenu
                            r = 0; g = 100; b = 180;
                        } else {
                            // Profondeur : bleu sombre
                            r = 0; g = 30; b = 90;
                        }
                        // Écume secondaire (harmonique) : éclaircissement subtil si proche crest2
                        if (d2 < 0.6f) {
                            r = min<uint8_t>(255, r + 20);
                            g = min<uint8_t>(255, g + 20);
                            b = min<uint8_t>(255, b + 25);
                        }
                        // Petit accent visuel autour des colonnes 0/3/6 (compat masque)
                        int distCol = min(min(abs(x-0), abs(x-3)), abs(x-6));
                        if (distCol <= 1 && d < 1.2f) {
                            r = min<uint8_t>(255, r + 15);
                            g = min<uint8_t>(255, g + 15);
                            b = min<uint8_t>(255, b + 15);
                        }
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, y, r, g, b);
                    }
                }
                // Option : seconde vague déphasée légère (mélange subtil)
                // (pour garder performance, mix implicite par palette ci-dessus)
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            if (now - lastUpdate > 180) {
                clearAllUniversal();
                int pos = animStep % 4;
                setGreenUniversal(pos, 255);
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        }
        break;

    // -----------------------------------------------------
    // MODE_ARC_EN_CIEL (avec sous-modes de vitesse)
    // -----------------------------------------------------
    case MODE_ARC_EN_CIEL: {
        int delayMs = (subMode == 0 ? 130 : subMode == 1 ? 90 : 60);
        
        if (getDisplayType() == DISPLAY_MATRIX) {
            if (now - lastUpdate > (unsigned long)delayMs) {
                clearAllUniversal();
                int t = animStep;
                for (int y = 0; y < 8; y++) {
                    for (int x = 0; x < 8; x++) {
                        // Bandes verticales arc‑en‑ciel qui défilent vers la droite
                        int idx = (x + (t/2)) % 6;
                        uint8_t r=0,g=0,b=0;
                        switch (idx) {
                            case 0: r=255; g=0;   b=0;   break; // Rouge
                            case 1: r=255; g=150; b=0;   break; // Orange
                            case 2: r=255; g=255; b=0;   break; // Jaune
                            case 3: r=0;   g=255; b=0;   break; // Vert
                            case 4: r=0;   g=100; b=255; break; // Bleu
                            case 5: r=180; g=0;   b=255; break; // Violet
                        }
                        // Légère modulation verticale pour relief
                        uint8_t mod = (uint8_t)(20 * sin((y + t) * 0.3));
                        r = constrain(r - mod, 0, 255);
                        g = constrain(g - mod, 0, 255);
                        b = constrain(b - mod, 0, 255);
                        // Accent visuel proche colonnes 0,3,6
                        int distCol = min(min(abs(x-0), abs(x-3)), abs(x-6));
                        if (distCol <= 1) { r = min(255, (int)r + 20); g = min(255, (int)g + 20); b = min(255, (int)b + 20); }
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, y, r, g, b);
                    }
                }
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
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
    // MODE_RUSH - Animation matrice: lignes rapides qui traversent
    // -----------------------------------------------------
    case MODE_RUSH:
        if (getDisplayType() == DISPLAY_MATRIX) {
            if (now - lastUpdate > 50) {  // Animation rapide
                clearAllUniversal();
                
                // Deux lignes qui descendent à des vitesses différentes
                int pos1 = (animStep / 2) % 10;      // Ligne rapide
                int pos2 = (animStep / 3) % 12;      // Ligne moyenne
                
                // Dessiner les lignes horizontales avec traînée
                for (int x = 0; x < 8; x++) {
                    // Première ligne (rouge-orange)
                    if (pos1 < 8) {
                        uint8_t r = 255, g = 80, b = 0;
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, pos1, r, g, b);
                        // Traînée
                        if (pos1 > 0) {
                            r = 150; g = 40; b = 0;
                            applyMatrixBrightnessToRGB(r, g, b);
                            setPixelXY(x, pos1 - 1, r, g, b);
                        }
                    }
                    
                    // Deuxième ligne (jaune)
                    if (pos2 < 8) {
                        uint8_t r = 255, g = 200, b = 0;
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, pos2, r, g, b);
                    }
                }
                
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            // Animation PWM originale
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
        }
        break;

    // -----------------------------------------------------
    // MODE_K2000 - Scanner style Kitt avec colonnes lumineuses
    // -----------------------------------------------------
    case MODE_K2000: {
        if (getDisplayType() == DISPLAY_MATRIX) {
            // Vitesse selon sous-mode
            int delayMs = (subMode == 0 ? 100 : subMode == 1 ? 60 : 35);
            
            static int k2000Pos = 0;
            static int k2000Dir = 1;  // +1 = droite, -1 = gauche
            
            if (now - lastUpdate > (unsigned long)delayMs) {
                clearAllUniversal();
                
                // Scanner avec 3 colonnes principales (0, 3, 6)
                // Effet de colonnes lumineuses qui balayent
                const uint8_t mainBrightness = 255;
                const uint8_t trail1 = 120;
                const uint8_t trail2 = 40;
                
                // Dessiner la colonne principale (rouge vif)
                for (int y = 0; y < 8; y++) {
                    uint8_t r = mainBrightness, g = 0, b = 0;
                    applyMatrixBrightnessToRGB(r, g, b);
                    setPixelXY(k2000Pos, y, r, g, b);
                }
                
                // Traînée 1 (orange)
                int trail1Pos = k2000Pos - k2000Dir;
                if (trail1Pos >= 0 && trail1Pos < 8) {
                    for (int y = 0; y < 8; y++) {
                        uint8_t r = trail1, g = 50, b = 0;
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(trail1Pos, y, r, g, b);
                    }
                }
                
                // Traînée 2 (rouge sombre)
                int trail2Pos = k2000Pos - 2 * k2000Dir;
                if (trail2Pos >= 0 && trail2Pos < 8) {
                    for (int y = 0; y < 8; y++) {
                        uint8_t r = trail2, g = 0, b = 0;
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(trail2Pos, y, r, g, b);
                    }
                }
                
                // Avance
                k2000Pos += k2000Dir;
                
                // Inversion de direction aux bords
                if (k2000Pos >= 7) k2000Dir = -1;
                if (k2000Pos <= 0) k2000Dir = +1;
                
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            // Animation PWM originale
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
        }
        break;
    }



    // -----------------------------------------------------
    // MODE_JACKPOT - Machine à sous avec symboles qui défilent
    // -----------------------------------------------------
    case MODE_JACKPOT: {
        if (getDisplayType() == DISPLAY_MATRIX) {
            int delayMs = (subMode == 0 ? 120 : subMode == 1 ? 80 : 50);
            
            if (now - lastUpdate > (unsigned long)delayMs) {
                clearAllUniversal();
                
                // Trois colonnes de symboles qui défilent (colonnes 1, 3, 5)
                // Symboles: Dollar ($), 7, Cherry, Star
                int scroll = animStep % 8;
                
                for (int col = 1; col < 8; col += 3) {  // Colonnes 1, 4, 7
                    int symbolOffset = ((animStep / 3) + col) % 4;  // Décalage pour chaque colonne
                    
                    for (int y = 0; y < 8; y++) {
                        int pixelType = ((y + scroll + symbolOffset) % 8);
                        uint8_t r = 0, g = 0, b = 0;
                        
                        // Symbole 1: Dollar (jaune/or)
                        if (pixelType < 2) {
                            r = 255; g = 200; b = 0;
                        }
                        // Symbole 2: 7 chanceux (rouge vif)
                        else if (pixelType < 4) {
                            r = 255; g = 0; b = 0;
                        }
                        // Symbole 3: Cerise (magenta)
                        else if (pixelType < 6) {
                            r = 255; g = 0; b = 100;
                        }
                        // Symbole 4: Étoile (cyan)
                        else {
                            r = 0; g = 255; b = 255;
                        }
                        
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(col, y, r, g, b);
                        
                        // Ajouter aussi les colonnes adjacentes pour un effet plus large
                        if (col > 0) {
                            uint8_t r2 = r / 3, g2 = g / 3, b2 = b / 3;
                            applyMatrixBrightnessToRGB(r2, g2, b2);
                            setPixelXY(col - 1, y, r2, g2, b2);
                        }
                        if (col < 7) {
                            uint8_t r2 = r / 3, g2 = g / 3, b2 = b / 3;
                            applyMatrixBrightnessToRGB(r2, g2, b2);
                            setPixelXY(col + 1, y, r2, g2, b2);
                        }
                    }
                }
                
                // Flash de victoire toutes les 20 frames
                if (animStep % 20 == 0) {
                    for (int x = 0; x < 8; x++) {
                        for (int y = 0; y < 8; y++) {
                            uint8_t r = 255, g = 215, b = 0;  // Or
                            applyMatrixBrightnessToRGB(r, g, b);
                            setPixelXY(x, y, r, g, b);
                        }
                    }
                }
                
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            // Animation PWM originale
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
        }
        break;
    }

    // -----------------------------------------------------
    // MODE_FDJ_WINNER - Animation de victoire avec explosion de confettis
    // -----------------------------------------------------
    case MODE_FDJ_WINNER:
        if (getDisplayType() == DISPLAY_MATRIX) {
            if (now - lastUpdate > 80) {
                clearAllUniversal();
                
                int phase = animStep % 40;
                
                // Phase 1 (0-10): Flash initial de victoire
                if (phase < 10) {
                    bool on = phase % 2;
                    if (on) {
                        for (int x = 0; x < 8; x++) {
                            for (int y = 0; y < 8; y++) {
                                uint8_t r = 255, g = 215, b = 0;  // Or
                                applyMatrixBrightnessToRGB(r, g, b);
                                setPixelXY(x, y, r, g, b);
                            }
                        }
                    }
                }
                // Phase 2 (10-30): Explosion de confettis du centre
                else if (phase < 30) {
                    int explosionStep = phase - 10;
                    
                    // Confettis qui partent du centre
                    for (int i = 0; i < 12; i++) {
                        float angle = (i * 30.0) * PI / 180.0;  // 12 directions
                        int dist = explosionStep / 3;
                        
                        int cx = 4 + (int)(cos(angle) * dist);
                        int cy = 4 + (int)(sin(angle) * dist);
                        
                        if (cx >= 0 && cx < 8 && cy >= 0 && cy < 8) {
                            uint8_t r, g, b;
                            // Couleurs variées pour confettis
                            switch (i % 5) {
                                case 0: r = 255; g = 0; b = 0; break;      // Rouge
                                case 1: r = 0; g = 255; b = 0; break;      // Vert
                                case 2: r = 0; g = 0; b = 255; break;      // Bleu
                                case 3: r = 255; g = 255; b = 0; break;    // Jaune
                                case 4: r = 255; g = 0; b = 255; break;    // Magenta
                            }
                            applyMatrixBrightnessToRGB(r, g, b);
                            setPixelXY(cx, cy, r, g, b);
                        }
                    }
                    
                    // Centre qui pulse
                    if (explosionStep < 5) {
                        uint8_t r = 255, g = 255, b = 255;
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(3, 3, r, g, b);
                        setPixelXY(3, 4, r, g, b);
                        setPixelXY(4, 3, r, g, b);
                        setPixelXY(4, 4, r, g, b);
                    }
                }
                // Phase 3 (30-40): Pluie de pièces dorées
                else {
                    int coinStep = phase - 30;
                    
                    for (int i = 0; i < 5; i++) {
                        int x = (i * 2 + coinStep) % 8;
                        int y = (coinStep + i) % 8;
                        
                        uint8_t r = 255, g = 215, b = 0;  // Or
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, y, r, g, b);
                        
                        // Traînée
                        if (y > 0) {
                            r = 200; g = 150; b = 0;
                            applyMatrixBrightnessToRGB(r, g, b);
                            setPixelXY(x, y - 1, r, g, b);
                        }
                    }
                }
                
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            // Animation PWM originale
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
    // 18. MODE_MAINTENANCE - Test de toutes les couleurs et pixels
    // -----------------------------------------------------
    case MODE_MAINTENANCE:
        if (getDisplayType() == DISPLAY_MATRIX) {
            if (now - lastUpdate > 200) {
                clearAllUniversal();
                
                int phase = animStep % 24;  // 8 phases pour tester tous les pixels
                
                // Phase 0-7: Allumer toute la matrice d'une couleur à la fois
                if (phase < 8) {
                    uint8_t r = 0, g = 0, b = 0;
                    switch (phase) {
                        case 0: r = 255; break;                    // Rouge
                        case 1: g = 255; break;                    // Vert
                        case 2: b = 255; break;                    // Bleu
                        case 3: r = 255; g = 255; break;          // Jaune
                        case 4: r = 255; b = 255; break;          // Magenta
                        case 5: g = 255; b = 255; break;          // Cyan
                        case 6: r = 255; g = 255; b = 255; break; // Blanc
                        case 7: r = 128; g = 64; b = 0; break;    // Orange
                    }
                    
                    for (int x = 0; x < 8; x++) {
                        for (int y = 0; y < 8; y++) {
                            uint8_t rt = r, gt = g, bt = b;
                            applyMatrixBrightnessToRGB(rt, gt, bt);
                            setPixelXY(x, y, rt, gt, bt);
                        }
                    }
                }
                // Phase 8-15: Scanner ligne par ligne (horizontal)
                else if (phase < 16) {
                    int line = phase - 8;
                    for (int x = 0; x < 8; x++) {
                        uint8_t r = 0, g = 255, b = 255;  // Cyan
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(x, line, r, g, b);
                    }
                }
                // Phase 16-23: Scanner colonne par colonne (vertical)
                else {
                    int col = phase - 16;
                    for (int y = 0; y < 8; y++) {
                        uint8_t r = 255, g = 100, b = 0;  // Orange
                        applyMatrixBrightnessToRGB(r, g, b);
                        setPixelXY(col, y, r, g, b);
                    }
                }
                
                showUniversal();
                animStep++;
                lastUpdate = now;
            }
        } else {
            // Animation PWM originale
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
