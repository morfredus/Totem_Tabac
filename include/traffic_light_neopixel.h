#ifndef TRAFFIC_LIGHT_NEOPIXEL_H
#define TRAFFIC_LIGHT_NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

/**
 * @brief Classe représentant un feu tricolore utilisant 3 LEDs NeoPixel
 * 
 * Cette classe gère un module NeoPixel de 3 LEDs pour simuler un feu tricolore :
 * - LED 0 : Rouge
 * - LED 1 : Jaune
 * - LED 2 : Vert
 * 
 * Elle fournit une interface identique aux feux PWM classiques pour faciliter
 * l'interopérabilité et permettre la transition sans casser le code existant.
 */
class TrafficLightNeoPixel {
public:
    /**
     * @brief Constructeur du feu tricolore NeoPixel
     * @param pin Pin GPIO connectée à la ligne DATA du module NeoPixel
     * @param brightness Luminosité globale (0-255, défaut 255)
     */
    TrafficLightNeoPixel(uint8_t pin, uint8_t brightness = 255);
    
    /**
     * @brief Initialise le module NeoPixel
     * Doit être appelé dans setup() avant toute utilisation
     */
    void begin();
    
    /**
     * @brief Définit l'intensité de la LED rouge
     * @param value Intensité (0-255)
     */
    void setRed(uint8_t value);
    
    /**
     * @brief Définit l'intensité de la LED jaune
     * @param value Intensité (0-255)
     */
    void setYellow(uint8_t value);
    
    /**
     * @brief Définit l'intensité de la LED verte
     * @param value Intensité (0-255)
     */
    void setGreen(uint8_t value);
    
    /**
     * @brief Définit une combinaison de couleurs RGB complète
     * @param r Activer rouge (true/false) ou valeur (0-255)
     * @param y Activer jaune (true/false) ou valeur (0-255)
     * @param g Valeur verte (0-255)
     */
    void setRGB(bool r, bool y, uint8_t g);
    
    /**
     * @brief Éteint toutes les LEDs du feu
     */
    void off();
    
    /**
     * @brief Obtient l'intensité actuelle de la LED rouge
     * @return Valeur (0-255)
     */
    uint8_t getRed() const { return redValue; }
    
    /**
     * @brief Obtient l'intensité actuelle de la LED jaune
     * @return Valeur (0-255)
     */
    uint8_t getYellow() const { return yellowValue; }
    
    /**
     * @brief Obtient l'intensité actuelle de la LED verte
     * @return Valeur (0-255)
     */
    uint8_t getGreen() const { return greenValue; }
    
    /**
     * @brief Définit la luminosité globale du module
     * @param brightness Luminosité (0-255)
     */
    void setBrightness(uint8_t brightness);
    
    /**
     * @brief Force la mise à jour immédiate des LEDs
     * Appel automatique lors des setXxx(), mais peut être utile
     * pour synchroniser plusieurs feux
     */
    void show();

private:
    Adafruit_NeoPixel strip;  ///< Instance Adafruit_NeoPixel pour ce feu
    uint8_t redValue;         ///< Valeur actuelle rouge (0-255)
    uint8_t yellowValue;      ///< Valeur actuelle jaune (0-255)
    uint8_t greenValue;       ///< Valeur actuelle verte (0-255)
    
    /**
     * @brief Met à jour l'affichage des 3 LEDs selon les valeurs internes
     */
    void updateDisplay();
};

#endif
