#include <Arduino.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Update.h>

#include "wifi_manager.h"
#include "light_helpers.h"
#include "modes.h"
#include "web_page.h"
#include "ota_page.h"
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
                        // Endpoint AJAX pour sous-mode (UI web)
                        server.on("/submode", [](){
                            nextSubMode();
                            ajaxOK();
                        });
                    // Route AJAX pour changer de sous-mode
                    server.on("/submode", [](){
                        nextSubMode();
                        ajaxOK();
                    });
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
            if (b < 0) b = 0;
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
    // Restaure le mode et sous-mode actuel
    loadModeFromNVS();

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);

    initLights();

    connectToKnownWiFi();
    Serial.println("IP: " + getCurrentIP());

    // Configuration ArduinoOTA
    ArduinoOTA.setHostname("Totem-Tabac");
    // ArduinoOTA.setPassword("totem2026");  // Décommenter pour activer la protection par mot de passe
    
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {  // U_SPIFFS
            type = "filesystem";
        }
        Serial.println("D\u00e9marrage mise \u00e0 jour OTA: " + type);
        // Éteindre tous les LEDs pendant la mise à jour
        clearAllUniversal();
        showUniversal();
    });
    
    ArduinoOTA.onEnd([]() {
        Serial.println("\nMise \u00e0 jour OTA termin\u00e9e");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progression: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Erreur[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Erreur authentification");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Erreur d\u00e9marrage");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Erreur connexion");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Erreur r\u00e9ception");
        else if (error == OTA_END_ERROR) Serial.println("Erreur fin");
    });
    
    ArduinoOTA.begin();
    Serial.println("OTA pr\u00eat");

    // Page OTA personnalis\u00e9e
    server.on("/update", HTTP_GET, [](){
        server.send(200, "text/html", renderOTAPage());
    });
    
    // Handler POST pour l'upload OTA
    server.on("/update", HTTP_POST, [](){
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        delay(500);
        ESP.restart();
    }, [](){
        HTTPUpload& upload = server.upload();
        if (upload.status == UPLOAD_FILE_START) {
            Serial.printf("Update: %s\n", upload.filename.c_str());
            // \u00c9teindre les LEDs pendant la MAJ
            clearAllUniversal();
            showUniversal();
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) {
                Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
        }
    });
    Serial.println("Serveur OTA Web sur /update");

    server.on("/", [](){
        server.send(200, "text/html", renderWebPage());
    });

    // Modes doux
    server.on("/mode/ambiance", [](){ setMode(MODE_AMBIANCE_DOUCE); ajaxOK(); });
    server.on("/mode/vague", [](){ setMode(MODE_VAGUE); ajaxOK(); });
    server.on("/mode/arc", [](){ setMode(MODE_ARC_EN_CIEL); ajaxOK(); });
    server.on("/mode/pulse_vert", [](){ setMode(MODE_PULSE_VERT); ajaxOK(); });
    server.on("/mode/pulse_jaune", [](){ setMode(MODE_PULSE_JAUNE); ajaxOK(); });
    server.on("/mode/pulse_rouge", [](){ setMode(MODE_PULSE_ROUGE); ajaxOK(); });

    // Modes dynamiques
    server.on("/mode/rush", [](){ setMode(MODE_RUSH); ajaxOK(); });
    server.on("/mode/k2000", [](){ setMode(MODE_K2000); ajaxOK(); });
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
    ArduinoOTA.handle();
    server.handleClient();
    handleButton1();
    handleButton2();
    updateMode();
}
