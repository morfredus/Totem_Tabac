#include "light_helpers.h"

// Fonctions wrapper pour maintenir la compatibilité avec le code existant
// Elles redirigent simplement vers le gestionnaire unifié

void initTrafficLightPWM(int module) {
    // L'initialisation est maintenant gérée par le gestionnaire via initLights()
    // Cette fonction est conservée pour compatibilité mais ne fait rien
    (void)module;
}

void setRed(int module, uint8_t value) {
    trafficLights.setRed(module, value);
}

void setYellow(int module, uint8_t value) {
    trafficLights.setYellow(module, value);
}

void setGreen(int module, uint8_t value) {
    trafficLights.setGreen(module, value);
}

void setRGB(int module, bool r, bool y, uint8_t g) {
    trafficLights.setRGB(module, r, y, g);
}

void clearModule(int module) {
    trafficLights.clearModule(module);
}

void clearAll() {
    trafficLights.clearAll();
}
