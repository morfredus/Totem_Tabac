/*
 * .copilot: Suivi des évolutions — Branche dev/8x8
 *
 * Fichier : light_helpers.cpp
 * Version projet : 0.12.0-dev8x8
 * Dernière modif : 2026-01-10
 * Auteur : Fred & Copilot
 *
 * - Helpers PWM pour modules classiques (4 modules × 3 couleurs)
 * - Helpers et mapping pour matrice NeoPixel 8x8 (3 feux tricolores)
 * - Mapping conforme à la doc et au changelog 0.12.0-dev8x8
 * - Toute évolution doit être synchronisée dans README, hardware_setup, changelog (FR/EN)
 *
 * Branche active : dev/8x8
 *
 * Historique :
 *   - v0.12.0-dev8x8 : Ajout helpers NeoPixel 8x8, mapping feux, correction header guard, compatibilité PlatformIO
 *   - v0.11.x et antérieures : PWM modules classiques uniquement
 */
#include "light_helpers.h"
#include <Adafruit_NeoPixel.h>
#include "board_config.h"

// --- Objet strip global pour matrice 8x8 ---
#ifndef NEOPIXEL_MATRIX_PIN
#define NEOPIXEL_MATRIX_PIN 27 // fallback sécurité
#endif
static Adafruit_NeoPixel strip(64, NEOPIXEL_MATRIX_PIN, NEO_GRB + NEO_KHZ800);

void initNeoPixelMatrix() {
    strip.begin();
    strip.show();
    strip.clear();
}

void clearMatrix() {
    strip.clear();
    strip.show();
}

void setRedMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(RED_PIXELS[feu][i], strip.Color(value, 0, 0));
    }
    strip.show();
}

void setYellowMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(YELLOW_PIXELS[feu][i], strip.Color(value, value, 0));
    }
    strip.show();
}

void setGreenMatrix(int feu, uint8_t value) {
    for (uint8_t i = 0; i < 4; i++) {
        strip.setPixelColor(GREEN_PIXELS[feu][i], strip.Color(0, value, 0));
    }
    strip.show();
}

void setPixelXY(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 8 || y >= 8) return;
    uint8_t idx = y * 8 + x;
    strip.setPixelColor(idx, strip.Color(r, g, b));
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
