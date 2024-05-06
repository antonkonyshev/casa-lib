#pragma once

#include <ESPAsyncWebServer.h>

#include "journal.h"

void serializeSettings(char* buffer);
void saveSettings(AsyncWebServerRequest* request);
void serviceInfoResponsePayload(char* buffer);

void handleServiceInfoRequest(AsyncWebServerRequest* request);
void handleSettingsReadRequest(AsyncWebServerRequest* request);
void handleSettingsEditRequest(AsyncWebServerRequest* request);
void handleJournalRequest(AsyncWebServerRequest* request);