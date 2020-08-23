#include "build.h"
#include "schedulebuffer.h"
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

ScheduleBuffer buffer;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  #ifdef DEBUG
  if (io.isFinished()) {
    return;
  }
  #endif // DEBUG

  valueFromBuffer = buffer.retrieve();
  valueFromIO = io.nextByte();


  if (valueFromIO > 0) {
    buffer.schedule(valueFromIO);
  }

  if (valueFromBuffer > 0) {
    io.writeByte(valueFromBuffer);
  }

  delay(1);
}
