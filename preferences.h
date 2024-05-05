#pragma once

#ifdef ESP32_DEVICE

#include <nvs_flash.h>

#define PREFERENCES_STORAGE_NAME "storage"
#define NVS_WIFI_SSID_CREDENTIALS_KEY "wifi_ssid"
#define NVS_WIFI_PASSWORD_CREDENTIALS_KEY "wifi_password"

#endif
#ifdef ESP8266_DEVICE

#include <LittleFS.h>

#define PREFERENCES_STORAGE_FILE "preferences.bin"
#define CREDENTIALS_STORAGE_FILE "wifi_credentials.bin"

#endif

typedef struct wifi_credentials_s {
    const char* ssid;
    const char* password;
    wifi_credentials_s* next;

    wifi_credentials_s() : ssid(nullptr), password(nullptr), next(nullptr) {}
} wifi_credentials_t;

struct preferences_s;

wifi_credentials_t* loadWiFiCredentials();
void cleanWiFiCredentials();

#ifdef ESP32_DEVICE
void openPreferencesStorage();
void closePreferencesStorage();
void savePreference(const char* key, const char* value);
const char* loadPreference(const char* key);
#endif
#ifdef ESP8266_DEVICE
void savePreference(preferences_s* prefs);
void loadPreference(preferences_s* prefs);
void saveWifiCredentials(const char* ssid, const char* password);
#endif