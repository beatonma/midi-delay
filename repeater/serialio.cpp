#include "io.h"

#include <Arduino.h>

const int BAUD_RATE = 31250;

class SerialIO : public IO {
 public:
  SerialIO() {}

  byte nextByte() { return Serial.read(); }

  byte awaitNextByte() {
    while (!Serial.available()) {
    };
    return Serial.read();
  }

  void writeByte(byte b) { Serial.write(b); }
};

IO* initIO() {
    return new SerialIO;
}
