#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// MODULE 1
#define TL1_RED     4
#define TL1_YELLOW  5
#define TL1_GREEN   12

// MODULE 2
#define TL2_RED     13
#define TL2_YELLOW  14
#define TL2_GREEN   16

// MODULE 3
#define TL3_RED     17
#define TL3_YELLOW  18
#define TL3_GREEN   19

// MODULE 4
#define TL4_RED     21
#define TL4_YELLOW  22
#define TL4_GREEN   23

// Boutons physiques
#define BUTTON_PIN   25   // change de mode
#define BUTTON2_PIN  26   // change de sous-mode

struct TrafficLightPins {
    int red;
    int yellow;
    int green;
};

static const TrafficLightPins TRAFFIC_LIGHTS[4] = {
    { TL1_RED, TL1_YELLOW, TL1_GREEN },
    { TL2_RED, TL2_YELLOW, TL2_GREEN },
    { TL3_RED, TL3_YELLOW, TL3_GREEN },
    { TL4_RED, TL4_YELLOW, TL4_GREEN }
};

#endif
