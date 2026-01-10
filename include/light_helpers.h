#ifndef LIGHT_HELPERS_H
#define LIGHT_HELPERS_H

#include <Arduino.h>
#include "traffic_light_manager.h"

// Fonctions wrapper pour compatibilité avec le code existant
// Ces fonctions redirigent vers le gestionnaire unifié

void initTrafficLightPWM(int module);
void clearModule(int module);
void clearAll();

void setRed(int module, uint8_t value);
void setYellow(int module, uint8_t value);
void setGreen(int module, uint8_t value);

void setRGB(int module, bool r, bool y, uint8_t g);

#endif
