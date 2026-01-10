#include "traffic_light_neopixel.h"

TrafficLightNeoPixel::TrafficLightNeoPixel(uint8_t pin, uint8_t brightness)
    : strip(3, pin, NEO_GRB + NEO_KHZ800),
      redValue(0),
      yellowValue(0),
      greenValue(0)
{
    strip.setBrightness(brightness);
}

void TrafficLightNeoPixel::begin() {
    strip.begin();
    strip.clear();
    strip.show();
}

void TrafficLightNeoPixel::setRed(uint8_t value) {
    redValue = value;
    updateDisplay();
}

void TrafficLightNeoPixel::setYellow(uint8_t value) {
    yellowValue = value;
    updateDisplay();
}

void TrafficLightNeoPixel::setGreen(uint8_t value) {
    greenValue = value;
    updateDisplay();
}

void TrafficLightNeoPixel::setRGB(bool r, bool y, uint8_t g) {
    redValue = r ? 255 : 0;
    yellowValue = y ? 255 : 0;
    greenValue = g;
    updateDisplay();
}

void TrafficLightNeoPixel::off() {
    redValue = 0;
    yellowValue = 0;
    greenValue = 0;
    updateDisplay();
}

void TrafficLightNeoPixel::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
    strip.show();
}

void TrafficLightNeoPixel::show() {
    strip.show();
}

void TrafficLightNeoPixel::updateDisplay() {
    // LED 0 : Rouge
    strip.setPixelColor(0, strip.Color(redValue, 0, 0));
    
    // LED 1 : Jaune (Rouge + Vert en RGB)
    // On utilise un ratio pour obtenir un jaune proche de la réalité
    uint8_t yellowR = yellowValue;
    uint8_t yellowG = (yellowValue * 180) / 255;  // Jaune = R255 + G180 environ
    strip.setPixelColor(1, strip.Color(yellowR, yellowG, 0));
    
    // LED 2 : Vert
    strip.setPixelColor(2, strip.Color(0, greenValue, 0));
    
    strip.show();
}
