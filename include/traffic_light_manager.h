#ifndef TRAFFIC_LIGHT_MANAGER_H
#define TRAFFIC_LIGHT_MANAGER_H

#include <Arduino.h>
#include "board_config.h"
#include <Adafruit_NeoPixel.h>

/**
 * @brief Type de système de feux utilisé
 */
enum TrafficLightType {
    TRAFFIC_LIGHT_PWM,      ///< Feux tricolores classiques avec LEDs PWM
    TRAFFIC_LIGHT_NEOPIXEL  ///< Feux tricolores avec modules NeoPixel 3 LEDs
};

/**
 * @brief Gestionnaire unifié des feux tricolores
 * 
 * Cette classe fournit une interface commune pour contrôler les 4 feux tricolores,
 * que ce soit avec le système PWM classique ou les modules NeoPixel.
 * 
 * Elle permet de basculer entre les deux systèmes sans modifier le code des animations.
 * Le type de feux est défini à la compilation via une directive de préprocesseur.
 */
class TrafficLightManager {
public:
    /**
     * @brief Constructeur du gestionnaire
     */
    TrafficLightManager();
    
    /**
     * @brief Destructeur
     */
    ~TrafficLightManager();
    
    /**
     * @brief Initialise le système de feux
     * Doit être appelé dans setup()
     */
    void begin();
    
    /**
     * @brief Définit l'intensité de la LED rouge d'un module
     * @param module Numéro du module (0-3)
     * @param value Intensité (0-255)
     */
    void setRed(int module, uint8_t value);
    
    /**
     * @brief Définit l'intensité de la LED jaune d'un module
     * @param module Numéro du module (0-3)
     * @param value Intensité (0-255)
     */
    void setYellow(int module, uint8_t value);
    
    /**
     * @brief Définit l'intensité de la LED verte d'un module
     * @param module Numéro du module (0-3)
     * @param value Intensité (0-255)
     */
    void setGreen(int module, uint8_t value);
    
    /**
     * @brief Définit une combinaison RGB complète pour un module
     * @param module Numéro du module (0-3)
     * @param r Activer rouge (true/false)
     * @param y Activer jaune (true/false)
     * @param g Valeur verte (0-255)
     */
    void setRGB(int module, bool r, bool y, uint8_t g);
    
    /**
     * @brief Éteint toutes les LEDs d'un module
     * @param module Numéro du module (0-3)
     */
    void clearModule(int module);
    
    /**
     * @brief Éteint tous les modules
     */
    void clearAll();
    
    /**
     * @brief Retourne le type de système actuellement utilisé
     * @return Type de feux (PWM ou NeoPixel)
     */
    TrafficLightType getType() const { return lightType; }
    
    /**
     * @brief Retourne le nombre de modules disponibles
     * @return Nombre de modules (4)
     */
    int getModuleCount() const { return 4; }

private:
    TrafficLightType lightType;              ///< Type de système utilisé
    Adafruit_NeoPixel* neoPixelStrip;        ///< Pointeur vers le strip NeoPixel (12 LEDs)
    
    /**
     * @brief Initialise le système PWM (feux classiques)
     */
    void initPWM();
    
    /**
     * @brief Initialise le système NeoPixel
     */
    void initNeoPixel();
    
    /**
     * @brief Implémentation PWM de setRed
     */
    void setRedPWM(int module, uint8_t value);
    
    /**
     * @brief Implémentation PWM de setYellow
     */
    void setYellowPWM(int module, uint8_t value);
    
    /**
     * @brief Implémentation PWM de setGreen
     */
    void setGreenPWM(int module, uint8_t value);
};

// Instance globale unique du gestionnaire
extern TrafficLightManager trafficLights;

#endif
