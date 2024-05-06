#include "journal.h"

journal_t* journal = new journal_t;

record_t* appendJournalRecord(const char* message, uint32_t timestamp = millis(), uint8_t priority = 1, uint16_t maxLength = DEFAULT_JOURNAL_LENGTH) {
    record_t* record = new record_t;
    record->timestamp = timestamp;
    record->priority = priority;
    record->message = message;
    
    if (journal->last) {
        journal->last->next = record;
        journal->last = record;
        journal->length += 1;
        if (journal->length > maxLength) {
            record_t* oldestNode = journal->first;
            journal->first = oldestNode->next;
            journal->length -= 1;
            delete oldestNode;
        }
    } else {
        journal->first = record;
        journal->last = record;
        journal->length = 1;
    }
    return record;
}

void cleanJournal() {
    if (journal->first) {
        record_t* record = journal->first;
        while (record) {
            record_t* oldRecord = record;
            record = oldRecord->next;
            delete oldRecord;
        }
        journal->first = nullptr;
    }
    journal->last = nullptr;
    journal->length = 0;
}

journal_t* getJournal() {
    return journal;
}