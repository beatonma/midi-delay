#include "types.h"
#include "buffer.h"

const int DELAY_BUFFER_SIZE = 1024 + 512 + 128 + 4 + 2 + 1;

byte delayBuffer[DELAY_BUFFER_SIZE];
int bufferPosition = 0;

void initBuffer() {
  for (int i = 0; i < DELAY_BUFFER_SIZE; i = i + 1) {
    reset(i);
  }
}

void reset(int position) { store(position, EMPTY); }
void reset() { reset(bufferPosition); }

bool isEmpty(int position) { return retrieve(position) == EMPTY; }
bool isEmpty() { return isEmpty(bufferPosition); }

/**
 * Store a single byte in the buffer at given position.
 */
void store(int position, byte _value) {
  delayBuffer[position % DELAY_BUFFER_SIZE] = _value;
}

/**
 * Store a single byte in the buffer at bufferPosition.
 */
void store(byte _value) { store(bufferPosition, _value); }

/**
 * Store a data message in the buffer, starting at given position.
 */
void store(int position, byte _status, byte _dataOne) {
  store(position, _status);
  store(position + 1, _dataOne);
}

/**
 * Store a status message in the buffer, starting at given position.
 */
void store(int position, byte _status, byte _dataOne, byte _dataTwo) {
  store(position, _status);
  store(position + 1, _dataOne);
  store(position + 2, _dataTwo);
}

/**
 * Get the value at given position of delay buffer.
 */
byte retrieve(int position) {
  position = position % DELAY_BUFFER_SIZE;
  return delayBuffer[position];
}

/**
 * Get the value at given position of delay buffer.
 */
byte retrieve() { return retrieve(bufferPosition); }

void stepBuffer(int stepSize) {
  bufferPosition = (bufferPosition + stepSize) % DELAY_BUFFER_SIZE;
}

void stepBuffer() { stepBuffer(1); }
