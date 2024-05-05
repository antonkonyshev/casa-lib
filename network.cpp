#include "network.h"

#ifdef ESP32_DEVICE
WiFiMulti wifiMulti;
#endif
#ifdef ESP8266_DEVICE
ESP8266WiFiMulti wifiMulti;
#endif
bool wifiApMode = false;

void indicateSOS() {
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
    delay(600);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(600);
        digitalWrite(LED_PIN, LOW);
        delay(600);
    }
    delay(600);
    for (uint8_t idx = 0; idx < 3; idx++) {
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        delay(200);
    }
    delay(1000);
}

void wifiKeepAlive() {
    if (wifiApMode) {
        indicateSOS();
        return;
    }
    uint8_t ledState = LOW;
    uint8_t retries = 0;
    while (wifiMulti.run(WIFI_CONNECTION_TIMEOUT * 1000) != WL_CONNECTED) {
        ledState = ledState == LOW ? HIGH : LOW;
        digitalWrite(LED_PIN, ledState);
        delay(1000);
        retries += 1;
        if (retries > WIFI_STA_CONNECT_RETRIES) {
            #ifdef ESP32_DEVICE
            WiFi.mode(WIFI_MODE_AP);
            #endif
            #ifdef ESP8266_DEVICE
            WiFi.mode(WIFI_AP);
            #endif

            String ssid = "Casa-" + String(DEVICE_ID);
            WiFi.softAP(ssid);

            #ifdef ESP32_DEVICE
            ESP_LOGW("network", "Couldn't connect to any available WiFi network. Fallback to access point mode with ssid '%s'. Please, connect to configure the device. After the configuration a reboot will be necessary.", ssid.c_str());
            #endif
            #ifdef ESP8266_DEVICE
            Serial.printf("Couldn't connect to any available WiFi network. Fallback to access point mode with ssid '%s'. Please, connect to configure the device. After the configuration a reboot will be necessary.\n", ssid.c_str());
            #endif

            wifiApMode = true;
            indicateSOS();
            break;
        }
    }
    digitalWrite(LED_PIN, LOW);
}

bool setupWifi() {
    #ifdef ESP32_DEVICE
    WiFi.mode(WIFI_MODE_STA);
    #endif
    #ifdef ESP8266_DEVICE
    WiFi.mode(WIFI_STA);
    #endif

    wifi_credentials_t* credentials = loadWiFiCredentials();
    while (credentials) {
        wifiMulti.addAP(credentials->ssid, credentials->password);
        credentials = credentials->next;
    }
    cleanWiFiCredentials();
    wifiKeepAlive();
    digitalWrite(LED_PIN, LOW);
    return true;
}
