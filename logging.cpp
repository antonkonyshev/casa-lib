#include "logging.h"

void setupSerial() {
    Serial.begin(115200);
    delay(100);
}

void printHardwareInfo() {
    Serial.println("");
    Serial.printf("--------------------------------- %s ---------------------------------\n", DEVICE_NAME);

    Serial.println("");
    Serial.printf("CPU frequency: %d MHz\n", ESP.getCpuFreqMHz());
    Serial.printf("Flash    size: %d bytes    |     Flash speed: %d MHz\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed() / 1000000);

    #ifdef ESP32_DEVICE
    Serial.printf("Chip    model: %s [%d cores]\n", ESP.getChipModel(), ESP.getChipCores());
    #endif

    Serial.printf("SDK version: %s\n", ESP.getSdkVersion());
}

void printMemoryInfo() {
    Serial.println("");

    #ifdef ESP32_DEVICE
    Serial.printf("Total  heap: %8d bytes     |     Free  heap: %8d bytes\n", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %8d bytes     |     Free PSRAM: %8d bytes\n", ESP.getPsramSize(), ESP.getFreePsram());
    #endif
    #ifdef ESP8266_DEVICE
    uint32_t* freeHeap = new uint32_t;
    uint32_t* maxHeap = new uint32_t;
    ESP.getHeapStats(freeHeap, maxHeap);
    Serial.printf("Total  heap: %8d bytes     |     Free  heap: %8d bytes\n", *freeHeap, *maxHeap);
    delete freeHeap;
    delete maxHeap;
    #endif

    Serial.printf("Sketch size: %8d bytes     |     Free space: %8d bytes\n", ESP.getSketchSize(), ESP.getFreeSketchSpace());
    Serial.println("");
}
