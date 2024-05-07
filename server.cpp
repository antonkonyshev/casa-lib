#include "server.h"

void handleJournalRequest(AsyncWebServerRequest* request) {
    digitalWrite(LED_BUILTIN, HIGH);
    journal_t* journal = getJournal();
    if (!journal->first) {
        request->send(200, "application/json", "[]");
        return;
    }
    record_t* record = journal->first;
    AsyncResponseStream* response = request->beginResponseStream("application/json");
    response->print("[");
    while (record) {
        if (record != journal->first) {
            response->print(",");
        }
        response->print(record->message);
        record = record->next;
    }
    response->print("]");
    request->send(response);
    digitalWrite(LED_BUILTIN, LOW);
}

void handleSettingsEditRequest(AsyncWebServerRequest* request) {
    digitalWrite(LED_BUILTIN, HIGH);
    saveSettings(request);
    request->send(200);
    digitalWrite(LED_BUILTIN, LOW);
}

void handleSettingsReadRequest(AsyncWebServerRequest* request) {
    digitalWrite(LED_BUILTIN, HIGH);
    char payload[512] = {0};
    serializeSettings(payload);
    request->send(200, "application/json", payload);
    digitalWrite(LED_BUILTIN, LOW);
}

void handleServiceInfoRequest(AsyncWebServerRequest* request) {
    digitalWrite(LED_BUILTIN, HIGH);
    char buffer[512];
    serviceInfoResponsePayload(buffer);
    request->send(200, "application/json", buffer);
    digitalWrite(LED_BUILTIN, LOW);
}