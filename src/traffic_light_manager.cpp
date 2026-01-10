#include "traffic_light_manager.h"

// PWM channels pour le mode classique
static const int RED_CH[4]    = {0, 1, 2, 3};
static const int YELLOW_CH[4] = {4, 5, 6, 7};
static const int GREEN_CH[4]  = {8, 9, 10, 11};

// Instance globale
TrafficLightManager trafficLights;

TrafficLightManager::TrafficLightManager() : neoPixelStrip(nullptr) {
    // Sélection du type de feux selon la directive de compilation
    #ifdef USE_NEOPIXEL_LIGHTS
        lightType = TRAFFIC_LIGHT_NEOPIXEL;
    #else
        lightType = TRAFFIC_LIGHT_PWM;
    #endif
}

TrafficLightManager::~TrafficLightManager() {
    // Libération de la mémoire du strip NeoPixel si alloué
    if (neoPixelStrip != nullptr) {
        delete neoPixelStrip;
        neoPixelStrip = nullptr;
    }
}

void TrafficLightManager::begin() {
    if (lightType == TRAFFIC_LIGHT_PWM) {
        initPWM();
    } else {
        initNeoPixel();
    }
    clearAll();
}

void TrafficLightManager::initPWM() {
    // Initialisation des 4 modules en PWM classique
    for (int i = 0; i < 4; i++) {
        ledcAttachPin(TRAFFIC_LIGHTS[i].red,    RED_CH[i]);
        ledcAttachPin(TRAFFIC_LIGHTS[i].yellow, YELLOW_CH[i]);
        ledcAttachPin(TRAFFIC_LIGHTS[i].green,  GREEN_CH[i]);

        ledcSetup(RED_CH[i],    5000, 8);
        ledcSetup(YELLOW_CH[i], 5000, 8);
        ledcSetup(GREEN_CH[i],  5000, 8);
    }
}

void TrafficLightManager::initNeoPixel() {
    // Initialisation d'un seul strip NeoPixel avec 12 LEDs (4 modules × 3 LEDs)
    // Le pin est défini dans board_config.h comme NEOPIXEL_DATA_PIN
    #ifdef NEOPIXEL_DATA_PIN
        // 12 LEDs, configuration NEO_GRB + NEO_KHZ800 (WS2812B standard)
        neoPixelStrip = new Adafruit_NeoPixel(12, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);
        neoPixelStrip->begin();
        neoPixelStrip->setBrightness(255); // Luminosité maximale par défaut
        neoPixelStrip->clear();
        neoPixelStrip->show();
    #endif
}

void TrafficLightManager::setRed(int module, uint8_t value) {
    if (module < 0 || module >= 4) return;
    
    if (lightType == TRAFFIC_LIGHT_PWM) {
        setRedPWM(module, value);
    } else if (neoPixelStrip != nullptr) {
        // LED rouge = première LED de chaque module (0, 3, 6, 9)
        int ledIndex = module * 3;
        neoPixelStrip->setPixelColor(ledIndex, neoPixelStrip->Color(value, 0, 0));
        neoPixelStrip->show();
    }
}

void TrafficLightManager::setYellow(int module, uint8_t value) {
    if (module < 0 || module >= 4) return;
    
    if (lightType == TRAFFIC_LIGHT_PWM) {
        setYellowPWM(module, value);
    } else if (neoPixelStrip != nullptr) {
        // LED jaune = deuxième LED de chaque module (1, 4, 7, 10)
        // Jaune = Rouge + Vert (ratio ~70% vert pour un jaune naturel)
        int ledIndex = module * 3 + 1;
        uint8_t yellowR = value;
        uint8_t yellowG = (value * 180) / 255;
        neoPixelStrip->setPixelColor(ledIndex, neoPixelStrip->Color(yellowR, yellowG, 0));
        neoPixelStrip->show();
    }
}

void TrafficLightManager::setGreen(int module, uint8_t value) {
    if (module < 0 || module >= 4) return;
    
    if (lightType == TRAFFIC_LIGHT_PWM) {
        setGreenPWM(module, value);
    } else if (neoPixelStrip != nullptr) {
        // LED verte = troisième LED de chaque module (2, 5, 8, 11)
        int ledIndex = module * 3 + 2;
        neoPixelStrip->setPixelColor(ledIndex, neoPixelStrip->Color(0, value, 0));
        neoPixelStrip->show();
    }
}

void TrafficLightManager::setRGB(int module, bool r, bool y, uint8_t g) {
    if (module < 0 || module >= 4) return;
    
    if (lightType == TRAFFIC_LIGHT_PWM) {
        setRedPWM(module, r ? 255 : 0);
        setYellowPWM(module, y ? 255 : 0);
        setGreenPWM(module, g);
    } else if (neoPixelStrip != nullptr) {
        setRed(module, r ? 255 : 0);
        setYellow(module, y ? 255 : 0);
        setGreen(module, g);
    }
}

void TrafficLightManager::clearModule(int module) {
    if (module < 0 || module >= 4) return;
    
    if (lightType == TRAFFIC_LIGHT_PWM) {
        setRedPWM(module, 0);
        setYellowPWM(module, 0);
        setGreenPWM(module, 0);
    } else if (neoPixelStrip != nullptr) {
        // Éteindre les 3 LEDs du module
        int baseIndex = module * 3;
        neoPixelStrip->setPixelColor(baseIndex, 0);
        neoPixelStrip->setPixelColor(baseIndex + 1, 0);
        neoPixelStrip->setPixelColor(baseIndex + 2, 0);
        neoPixelStrip->show();
    }
}

void TrafficLightManager::clearAll() {
    for (int i = 0; i < 4; i++) {
        clearModule(i);
    }
}

// Implémentations PWM
void TrafficLightManager::setRedPWM(int module, uint8_t value) {
    ledcWrite(RED_CH[module], value);
}

void TrafficLightManager::setYellowPWM(int module, uint8_t value) {
    ledcWrite(YELLOW_CH[module], value);
}

void TrafficLightManager::setGreenPWM(int module, uint8_t value) {
    ledcWrite(GREEN_CH[module], value);
}
