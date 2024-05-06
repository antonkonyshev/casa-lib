#include "ntp.h"

bool setupRTC() {
    time_t now;
    configTime(0, 0, NTP_SERVER_1, NTP_SERVER_2, NTP_SERVER_3);
    time_t timeout = millis() + RTC_SYNC_TIMEOUT * 1000;
    bool result = true;
    while (now < 1687100000) {
        time(&now);
        delay(100);
        if (millis() > timeout) {
            result = false;
            break;
        }
    }
    return result;
}

void syncTime() {
    configTime(0, 0, NTP_SERVER_1, NTP_SERVER_2, NTP_SERVER_3);
}