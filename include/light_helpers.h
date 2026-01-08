#ifndef LIGHT_HELPERS_H
#define LIGHT_HELPERS_H

#include <Arduino.h>
#include "board_config.h"

// PWM channels
static const int RED_CH[4]    = {0, 1, 2, 3};
static const int YELLOW_CH[4] = {4, 5, 6, 7};
static const int GREEN_CH[4]  = {8, 9, 10, 11};

void initTrafficLightPWM(int module);
void clearModule(int module);
void clearAll();

void setRed(int module, uint8_t value);
void setYellow(int module, uint8_t value);
void setGreen(int module, uint8_t value);

void setRGB(int module, bool r, bool y, uint8_t g);

#endif
