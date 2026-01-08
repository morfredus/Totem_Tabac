#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

bool connectToKnownWiFi();
String getCurrentIP();
bool getLocalHour(int &hour);

#endif
