#include "wifi_manager.h"
#include <time.h>

bool connectToKnownWiFi() {
    Serial.println("Connexion aux réseaux WiFi connus...");

    for (size_t i = 0; i < sizeof(WIFI_NETWORKS) / sizeof(WIFI_NETWORKS[0]); i++) {
        const char* ssid = WIFI_NETWORKS[i][0];
        const char* pass = WIFI_NETWORKS[i][1];

        Serial.printf("Tentative sur %s...\n", ssid);
        WiFi.begin(ssid, pass);

        unsigned long start = millis();
        while (millis() - start < 8000) {
            if (WiFi.status() == WL_CONNECTED) {
                Serial.printf("Connecté à %s\n", ssid);
                configTime(0, 0, "pool.ntp.org", "time.nist.gov");
                return true;
            }
            delay(200);
        }
        Serial.println("Échec.");
    }

    Serial.println("Aucun réseau disponible.");
    return false;
}

String getCurrentIP() {
    if (WiFi.status() == WL_CONNECTED)
        return WiFi.localIP().toString();
    return "Non connecté";
}

bool getLocalHour(int &hour) {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return false;
    }
    hour = timeinfo.tm_hour;
    return true;
}
