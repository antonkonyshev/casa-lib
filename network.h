#pragma once

#ifdef ESP32_DEVICE

#include <WiFi.h>
#include <WiFiMulti.h>

#endif
#ifdef ESP8266_DEVICE

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#endif

#include "pinout.h"
#include "preferences.h"

#define WIFI_CONNECTION_TIMEOUT 60  // seconds
#define WIFI_STA_CONNECT_RETRIES 30

void wifiKeepAlive();
bool setupWifi();