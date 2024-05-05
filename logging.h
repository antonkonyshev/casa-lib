#pragma once

#include <Arduino.h>
#ifdef ESP8266_DEVICE
#include <Esp.h>
#endif

#ifndef DEVICE_NAME
#define DEVICE_NAME "Casa"
#endif

void setupSerial();
void printHardwareInfo();
void printMemoryInfo();