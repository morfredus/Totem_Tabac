#include <stdint.h>

// --- Brightness matrice NeoPixel ---
void setMatrixBrightness(uint8_t b);
uint8_t getMatrixBrightness();
void loadMatrixBrightnessFromNVS();
void saveMatrixBrightnessToNVS();
// Helpers universels pour PWM ou matrice selon currentDisplayType
void initLightsUniversal();
void clearModuleUniversal(int module);
void clearAllUniversal();
void setRedUniversal(int module, uint8_t value);
void setYellowUniversal(int module, uint8_t value);
void setGreenUniversal(int module, uint8_t value);
void setRGBUniversal(int module, bool r, bool y, uint8_t g);

#ifndef LIGHT_HELPERS_H
#define LIGHT_HELPERS_H

#include <Arduino.h>
#include "board_config.h"

// PWM channels
static const int RED_CH[4]    = {0, 1, 2, 3};
static const int YELLOW_CH[4] = {4, 5, 6, 7};
static const int GREEN_CH[4]  = {8, 9, 10, 11};

// === Helpers et mapping pour matrice NeoPixel 8x8 ===
#include <Adafruit_NeoPixel.h>

// Mapping feux tricolores sur matrice 8x8 (indexation 0–63, haut en bas)
static constexpr int TRAFFIC_LIGHT_COUNT_MATRIX = 3;
static const uint8_t RED_PIXELS[TRAFFIC_LIGHT_COUNT_MATRIX][4] = {
	{0, 1, 8, 9},      // Feu 1
	{3, 4, 11, 12},    // Feu 2
	{6, 7, 14, 15}     // Feu 3
};
static const uint8_t YELLOW_PIXELS[TRAFFIC_LIGHT_COUNT_MATRIX][4] = {
	{24, 25, 32, 33},  // Feu 1
	{27, 28, 35, 36},  // Feu 2
	{30, 31, 38, 39}   // Feu 3
};
static const uint8_t GREEN_PIXELS[TRAFFIC_LIGHT_COUNT_MATRIX][4] = {
	{48, 49, 56, 57},  // Feu 1
	{51, 52, 59, 60},  // Feu 2
	{54, 55, 62, 63}   // Feu 3
};

void initNeoPixelMatrix();
void clearMatrix();
void setRedMatrix(int feu, uint8_t value);
void setYellowMatrix(int feu, uint8_t value);
void setGreenMatrix(int feu, uint8_t value);
void setPixelXY(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

void initTrafficLightPWM(int module);
void clearModule(int module);
void clearAll();

void setRed(int module, uint8_t value);
void setYellow(int module, uint8_t value);
void setGreen(int module, uint8_t value);

void setRGB(int module, bool r, bool y, uint8_t g);

#endif
