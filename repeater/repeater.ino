#include "midi.h"
#include "buffer.h"
#include "serialio.cpp"
// #include "mockio.cpp"

int currentByte = 0;
IO* io = initIO();

void setup() {
  initBuffer();
  Serial.begin(MIDI_BAUD_RATE);
}

void loop() {
  if (!isEmpty()) {
    io->writeByte(retrieve());
    reset();
  }

  stepBuffer();

  currentByte = io->nextByte();
  if (currentByte > 0) {
    store(currentByte);
  } else {
    reset();
  }
}
