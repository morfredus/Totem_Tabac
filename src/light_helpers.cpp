#include "modes.h"
#include "light_helpers.h"
#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
#include "board_config.h"

// --- Objet strip global pour matrice 8x8 (déclaré en premier) ---
#ifndef NEOPIXEL_MATRIX_PIN
#define NEOPIXEL_MATRIX_PIN 27 // fallback sécurité
#endif
static Adafruit_NeoPixel strip(64, NEOPIXEL_MATRIX_PIN, NEO_GRB + NEO_KHZ800);
static uint8_t matrixBrightness = 128;
static Preferences matrixPrefs;

// --- Helpers universels PWM/matrice ---
void initLightsUniversal() {
    if (getDisplayType() == DISPLAY_MATRIX) {
        // Désactiver PWM avant d'initialiser la matrice
        int allPins[] = {TL1_RED, TL1_YELLOW, TL1_GREEN, 
                         TL2_RED, TL2_YELLOW, TL2_GREEN,
                         TL3_RED, TL3_YELLOW, TL3_GREEN, 
                         TL4_RED, TL4_YELLOW, TL4_GREEN};
        for (int i = 0; i < 12; i++) {
            ledcDetachPin(allPins[i]);
            pinMode(allPins[i], INPUT); // Mettre en haute impédance
        }
        initNeoPixelMatrix();
        clearMatrix();
        showMatrix(); // Afficher le buffer vide
    } else {
        // S'assurer que la matrice est éteinte
        strip.clear();
        strip.show();
        // Initialiser PWM
        for (int i = 0; i < 4; i++) initTrafficLightPWM(i);
        clearAll();
    }
}

void clearModuleUniversal(int module) {
    if (getDisplayType() == DISPLAY_MATRIX) {
        if (module < 3) {
            setRedMatrix(module, 0);
            setYellowMatrix(module, 0);
            setGreenMatrix(module, 0);
        }
    } else {
        clearModule(module);
    }
}

void clearAllUniversal() {
    if (getDisplayType() == DISPLAY_MATRIX) {
        for (int i = 0; i < 3; i++) clearModuleUniversal(i);
        clearMatrix();
    } else {
        clearAll();
    }
}

void setRedUniversal(int module, uint8_t value) {
    if (getDisplayType() == DISPLAY_MATRIX) {
        if (module < 3) setRedMatrix(module, value);
    } else {
        setRed(module, value);
    }
}

void setYellowUniversal(int module, uint8_t value) {
    if (getDisplayType() == DISPLAY_MATRIX) {
        if (module < 3) setYellowMatrix(module, value);
    } else {
        setYellow(module, value);
    }
}

void setGreenUniversal(int module, uint8_t value) {
    if (getDisplayType() == DISPLAY_MATRIX) {
        if (module < 3) setGreenMatrix(module, value);
    } else {
        setGreen(module, value);
    }
}

void setRGBUniversal(int module, bool r, bool y, uint8_t g) {
    if (getDisplayType() == DISPLAY_MATRIX) {
        setRedUniversal(module, r ? 255 : 0);
        setYellowUniversal(module, y ? 255 : 0);
        setGreenUniversal(module, g);
    } else {
        setRGB(module, r, y, g);
    }
}

void showUniversal() {
    if (getDisplayType() == DISPLAY_MATRIX) {
        showMatrix();
    }
    // Pour PWM, pas besoin d'appeler show(), c'est instantané
}

// --- Fonctions spécifiques à la matrice NeoPixel ---

void initNeoPixelMatrix() {
    strip.begin();
    strip.clear();
    strip.setBrightness(matrixBrightness);
    strip.show();
    delay(10); // Stabilisation
}

void setMatrixBrightness(uint8_t b) {
    matrixBrightness = b;
    strip.setBrightness(matrixBrightness);
    strip.show();
    saveMatrixBrightnessToNVS();
}

uint8_t getMatrixBrightness() {
    return matrixBrightness;
}

void loadMatrixBrightnessFromNVS() {
    matrixPrefs.begin("matrix", true);
    matrixBrightness = matrixPrefs.getUChar("brightness", 128);
    matrixPrefs.end();
}

void saveMatrixBrightnessToNVS() {
    matrixPrefs.begin("matrix", false);
    matrixPrefs.putUChar("brightness", matrixBrightness);
    matrixPrefs.end();
}

void clearMatrix() {
    strip.clear();
    strip.show();
}

void setRedMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(RED_PIXELS[feu][i], strip.Color(value, 0, 0));
    }
}

void setYellowMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(YELLOW_PIXELS[feu][i], strip.Color(value, value, 0));
    }
}

void setGreenMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(GREEN_PIXELS[feu][i], strip.Color(0, value, 0));
    }
}

void setPixelXY(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 8 || y >= 8) return;
    uint8_t idx = y * 8 + x;
    strip.setPixelColor(idx, strip.Color(r, g, b));
}

void showMatrix() {
    strip.show();
}
#include "light_helpers.h"

void initTrafficLightPWM(int module) {
    ledcAttachPin(TRAFFIC_LIGHTS[module].red,    RED_CH[module]);
    ledcAttachPin(TRAFFIC_LIGHTS[module].yellow, YELLOW_CH[module]);
    ledcAttachPin(TRAFFIC_LIGHTS[module].green,  GREEN_CH[module]);

    ledcSetup(RED_CH[module],    5000, 8);
    ledcSetup(YELLOW_CH[module], 5000, 8);
    ledcSetup(GREEN_CH[module],  5000, 8);
}

void setRed(int module, uint8_t value) {
    ledcWrite(RED_CH[module], value);
}

void setYellow(int module, uint8_t value) {
    ledcWrite(YELLOW_CH[module], value);
}

void setGreen(int module, uint8_t value) {
    ledcWrite(GREEN_CH[module], value);
}

void setRGB(int module, bool r, bool y, uint8_t g) {
    setRed(module,   r ? 255 : 0);
    setYellow(module, y ? 255 : 0);
    setGreen(module, g);
}

void clearModule(int module) {
    setRed(module, 0);
    setYellow(module, 0);
    setGreen(module, 0);
}

void clearAll() {
    for (int i = 0; i < 4; i++) {
        clearModule(i);
    }
}
