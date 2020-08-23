#include "build.h"
#include "buffer.h"
#include "midi.h"

#ifdef DEBUG
#include "mockio.cpp"
MockIO io;
#else
#include "serialio.cpp"
SerialIO io;
#endif

int valueFromIO = 0;
int valueFromBuffer = 0;
Buffer buffer;

void setup() {
  Serial.begin(BAUD_RATE);
  buffer.initBuffer();
}

void loop() {
  valueFromIO = io.nextByte();
  valueFromBuffer = buffer.retrieve();

  if (valueFromIO > 0) {
    buffer.store(valueFromIO);
  }

  io.writeByte(valueFromBuffer);

  buffer.stepBuffer();
}
