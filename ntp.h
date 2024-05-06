#pragma once

#include <Arduino.h>

#define RTC_SYNC_TIMEOUT 300  // seconds
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.google.com"
#define NTP_SERVER_3 "time.cloudflare.com"

bool setupRTC();
void syncTime();