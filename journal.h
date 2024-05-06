#pragma once

#include <Arduino.h>

#define DEFAULT_JOURNAL_LENGTH 15

typedef struct record_s {
    uint32_t timestamp;
    uint8_t priority;
    const char* message;

    record_s* next;

    record_s(): timestamp(millis()), priority(1), message(nullptr), next(nullptr) {}
} record_t;

typedef struct journal_s {
    record_t* first;
    record_t* last;
    size_t length;

    journal_s(): first(nullptr), last(nullptr), length(0) {}
} journal_t;

record_t* appendJournalRecord(const char* message, uint32_t timestamp, uint8_t priority, uint16_t maxLength);
journal_t* getJournal();
void cleanJournal();