#include "build.h"
#include <Arduino.h>

void print(char values[]) {
    #ifdef DEBUG
    Serial.print(values);
    #endif
}

void print(char value) {
    #ifdef DEBUG
    Serial.print(value);
    #endif
}

void println(char values[]) {
    #ifdef DEBUG
    Serial.println(values);
    #endif
}

void println(char value) {
    #ifdef DEBUG
    Serial.println(value);
    #endif
}
