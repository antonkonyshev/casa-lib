#include "preferences.h"

wifi_credentials_t* credentials;
#ifdef ESP32_DEVICE
nvs_handle_t storage;
#endif

void addToCredentials(const char* ssid, const char* password) {
    wifi_credentials_t* additional = new wifi_credentials_t;
    additional->ssid = ssid;
    additional->password = password;
    if (credentials) {
        additional->next = credentials;
    }
    credentials = additional;
}

void addToCredentials(wifi_credentials_t* creds) {
    if (credentials) {
        creds->next = credentials;
    }
    credentials = creds;
}

wifi_credentials_t* loadWiFiCredentials() {
    if (credentials) {
        return credentials;
    }

    #ifdef DEFAULT_WIFI_SSID_3
    addToCredentials(DEFAULT_WIFI_SSID_3, DEFAULT_WIFI_PASSWORD_3);
    #endif
    #ifdef DEFAULT_WIFI_SSID_2
    addToCredentials(DEFAULT_WIFI_SSID_2, DEFAULT_WIFI_PASSWORD_2);
    #endif
    #ifdef DEFAULT_WIFI_SSID_1
    addToCredentials(DEFAULT_WIFI_SSID_1, DEFAULT_WIFI_PASSWORD_1);
    #endif

    #ifdef ESP32_DEVICE

    nvs_handle_t storage;
    size_t value_size;
    nvs_open(PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);

    nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, NULL, &value_size);
    if (value_size && value_size < 512) {
        char ssid[value_size] = {0};
        nvs_get_str(storage, NVS_WIFI_SSID_CREDENTIALS_KEY, ssid, &value_size);
        nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, NULL, &value_size);
        if (value_size && value_size < 512) {
            char pwd[value_size] = {0};
            nvs_get_str(storage, NVS_WIFI_PASSWORD_CREDENTIALS_KEY, pwd, &value_size);
            addToCredentials(ssid, pwd);
        } else {
            addToCredentials(ssid, "");
        }
    }

    nvs_close(storage);

    #endif
    #ifdef ESP8266_DEVICE

    File storage = LittleFS.open(CREDENTIALS_STORAGE_FILE, "rb");
    if (storage) {
        wifi_credentials_t* creds = new wifi_credentials_t;
        storage.read((byte *) &creds, sizeof(creds));
        storage.close();
        addToCredentials(creds);
    }

    #endif

    return credentials;
}

void cleanWiFiCredentials() {
    while(credentials) {
        wifi_credentials_t* current = credentials;
        credentials = credentials->next;
        delete current;
    }
}

#ifdef ESP32_DEVICE
void openPreferencesStorage() {
    nvs_open(PREFERENCES_STORAGE_NAME, NVS_READWRITE, &storage);
}

void closePreferencesStorage() {
    nvs_close(storage);
}

void savePreference(const char* key, const char* value) {
    if (key != nullptr && value != nullptr) {
        nvs_set_str(storage, key, value);
    }
}

const char* loadPreference(const char* key) {
    size_t value_size;
    nvs_get_str(storage, key, NULL, &value_size);
    if (value_size && value_size < 512) {
        char buffer[value_size] = {0};
        nvs_get_str(storage, key, buffer, &value_size);
        return buffer;
    }
    return nullptr;
}
#endif

#ifdef ESP8266_DEVICE
void savePreference(preferences_s* prefs) {
    File fStorage = LittleFS.open(PREFERENCES_STORAGE_FILE, "wb");
    if (!fStorage) {
        Serial.println("Cannot open preferences file for writting.");
        return;
    }

    int writtenBytes = fStorage.write((byte*) &prefs, sizeof(prefs));
    if (writtenBytes == 0) {
        Serial.println("Preferences weren't dumped to a file.");
    }
    fStorage.close();
}

void loadPreference(preferences_s* prefs) {
    File fStorage = LittleFS.open(PREFERENCES_STORAGE_FILE, "rb");
    if (!fStorage) {
        Serial.println("Preferences file is not available for reading.");
        return;
    }

    int redBytes = fStorage.read((byte *) &prefs, sizeof(prefs));
    if (redBytes == 0) {
        Serial.println("Preferences weren't loaded from a file.");
    }
    fStorage.close();
}

void saveWifiCredentials(const char* ssid, const char* password) {
    File fStorage = LittleFS.open(CREDENTIALS_STORAGE_FILE, "wb");
    if (!fStorage) {
        Serial.println("Credentials file is not available for writing.");
        return;
    }

    wifi_credentials_t* creds = new wifi_credentials_t;
    creds->ssid = ssid;
    creds->password = password;

    int writtenBytes = fStorage.write((byte*) &creds, sizeof(creds));
    if (writtenBytes == 0) {
        Serial.println("Credentials weren't dumped to a file.");
    }
    fStorage.close();
}
#endif