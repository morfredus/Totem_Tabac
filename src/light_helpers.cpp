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
