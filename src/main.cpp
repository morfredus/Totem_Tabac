#include <Arduino.h>
#include <WebServer.h>

#include "wifi_manager.h"
#include "light_helpers.h"
#include "modes.h"
#include "web_page.h"
#include "board_config.h"
#include "submode.h"

WebServer server(80);

// Anti-rebond boutons
bool lastButtonState = HIGH;
unsigned long lastButtonChange = 0;

bool lastButton2State = HIGH;
unsigned long lastButton2Change = 0;

void ajaxOK() {
    server.send(200, "text/plain", "OK");
}

void handleButton1() {
    bool state = digitalRead(BUTTON_PIN);
    unsigned long now = millis();
    if (state != lastButtonState && (now - lastButtonChange) > 50) {
        lastButtonChange = now;
        lastButtonState = state;
        if (state == LOW) nextMode();
    }
}

void handleButton2() {
    bool state = digitalRead(BUTTON2_PIN);
    unsigned long now = millis();
    if (state != lastButton2State && (now - lastButton2Change) > 50) {
        lastButton2Change = now;
        lastButton2State = state;
        if (state == LOW) nextSubMode();
    }
}

void setup() {
                // Route AJAX pour humeur du patron (couleur)
                server.on("/humeur", [](){
                    if (server.hasArg("value")) {
                        humeurColor = server.arg("value").toInt();
                        setMode(MODE_HUMEUR_PATRON);
                    }
                    ajaxOK();
                });
        // Endpoint universel pour changer de mode par numéro (pour l'UI web moderne)
        server.on("/mode", [](){
            if (server.hasArg("value")) {
                int m = server.arg("value").toInt();
                    setMode((Mode)m);
            }
            ajaxOK();
        });
    // Route pour changer le type d'affichage (matrice/modules)
    server.on("/display", [](){
        int t = -1;
        if (server.hasArg("value")) t = server.arg("value").toInt();
        else if (server.hasArg("t")) t = server.arg("t").toInt();
        if (t != -1) setDisplayType(t == 1 ? DISPLAY_MATRIX : DISPLAY_PWM);
        ajaxOK();
    });

    // Route pour régler la luminosité de la matrice
    server.on("/brightness", [](){
        int b = -1;
        if (server.hasArg("value")) b = server.arg("value").toInt();
        else if (server.hasArg("b")) b = server.arg("b").toInt();
        if (b != -1) {
            if (b < 10) b = 10;
            if (b > 255) b = 255;
            setMatrixBrightness((uint8_t)b);
        }
        ajaxOK();
    });

    Serial.begin(115200);

    // Restaure le choix d'affichage (PWM ou matrice) depuis la mémoire NVS
    loadDisplayTypeFromNVS();
    // Restaure la luminosité matrice
    loadMatrixBrightnessFromNVS();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    initLights();
    clearAll();

    connectToKnownWiFi();
    Serial.println("IP: " + getCurrentIP());

    server.on("/", [](){
        server.send(200, "text/html", renderWebPage());
    });

    // Modes doux
    server.on("/mode/zen", [](){ setMode(MODE_ZEN); ajaxOK(); });
    server.on("/mode/ambiance", [](){ setMode(MODE_AMBIANCE_DOUCE); ajaxOK(); });
    server.on("/mode/vague", [](){ setMode(MODE_VAGUE); ajaxOK(); });
    server.on("/mode/arc", [](){ setMode(MODE_ARC_EN_CIEL); ajaxOK(); });
    server.on("/mode/arc_turbo", [](){ setMode(MODE_ARC_EN_CIEL_TURBO); ajaxOK(); });
    server.on("/mode/pulse_vert", [](){ setMode(MODE_PULSE_VERT); ajaxOK(); });
    server.on("/mode/pulse_jaune", [](){ setMode(MODE_PULSE_JAUNE); ajaxOK(); });
    server.on("/mode/pulse_rouge", [](){ setMode(MODE_PULSE_ROUGE); ajaxOK(); });

    // Modes dynamiques
    server.on("/mode/rush", [](){ setMode(MODE_RUSH); ajaxOK(); });
    server.on("/mode/k2000", [](){ setMode(MODE_K2000); ajaxOK(); });
    server.on("/mode/disco", [](){ setMode(MODE_DISCO); ajaxOK(); });
    server.on("/mode/jackpot", [](){ setMode(MODE_JACKPOT); ajaxOK(); });
    server.on("/mode/fdj", [](){ setMode(MODE_FDJ_WINNER); ajaxOK(); });
    server.on("/mode/client_gagnant", [](){ setMode(MODE_CLIENT_GAGNANT); ajaxOK(); });
    server.on("/mode/client_perdant", [](){ setMode(MODE_CLIENT_PERDANT); ajaxOK(); });

    // Utilitaires
    server.on("/mode/ouverture", [](){ setMode(MODE_OUVERTURE); ajaxOK(); });
    server.on("/mode/fermeture", [](){ setMode(MODE_FERMETURE); ajaxOK(); });
    server.on("/mode/pause", [](){ setMode(MODE_PAUSE_CAFE); ajaxOK(); });
    server.on("/mode/maintenance", [](){ setMode(MODE_MAINTENANCE); ajaxOK(); });

    // Humeur du patron
    server.on("/mode/humeur", [](){
        if (server.hasArg("c")) {
            humeurColor = server.arg("c").toInt();
            if (humeurColor < 0) humeurColor = 0;
            if (humeurColor > 5) humeurColor = 5;
        }
        setMode(MODE_HUMEUR_PATRON);
        ajaxOK();
    });

    // Sous-modes
    server.on("/sub", [](){
        if (server.hasArg("v")) subMode = server.arg("v").toInt();
        ajaxOK();
    });

    // Status AJAX
    server.on("/status", [](){
        String json = "{";
        json += "\"mode\":" + String(currentMode) + ",";
        json += "\"sub\":" + String(subMode) + ",";
        json += "\"humeur\":" + String(humeurColor) + ",";
        json += "\"displayType\":" + String((int)getDisplayType()) + ",";
        json += "\"brightness\":" + String(getMatrixBrightness());
        json += "}";
        server.send(200, "application/json", json);
    });

    server.begin();
    Serial.println("Serveur HTTP démarré");
}

void loop() {
    server.handleClient();
    handleButton1();
    handleButton2();
    updateMode();
}
