#include <Arduino.h>
#include "build.h"
#include "types.h"
#include "buffer.h"

void Buffer::initBuffer() {
  for (int i = 0; i < DELAY_BUFFER_SIZE; i++) {
    reset(i);
  }
}

void Buffer::reset(int position) { store(position, EMPTY); }
void Buffer::reset() { reset(bufferPosition); }

bool Buffer::isEmpty(int position) { return retrieve(position) == EMPTY; }
bool Buffer::isEmpty() { return isEmpty(bufferPosition); }

/**
 * Store a single byte in the buffer at given position.
 */
void Buffer::store(int position, byte _value) {
  delayBuffer[position % DELAY_BUFFER_SIZE] = _value;
  print(F("store["));
  print(position);
  print(F("]: "));
  println(_value);
}

/**
 * Store a single byte in the buffer at bufferPosition.
 */
void Buffer::store(byte _value) { store(bufferPosition, _value); }

/**
 * Store a data message in the buffer, starting at given position.
 */
void Buffer::store(int position, byte _status, byte _dataOne) {
  store(position, _status);
  store(position + 1, _dataOne);
}

/**
 * Store a status message in the buffer, starting at given position.
 */
void Buffer::store(int position, byte _status, byte _dataOne, byte _dataTwo) {
  store(position, _status);
  store(position + 1, _dataOne);
  store(position + 2, _dataTwo);
}

/**
 * Get the value at given position of delay buffer.
 */
byte Buffer::retrieve(int position) {
  position = position % DELAY_BUFFER_SIZE;
  print(F("retrieve["));
  print(position);
  print(F("]: "));
  println(delayBuffer[position]);
  return delayBuffer[position];
}

/**
 * Get the value at given position of delay buffer.
 */
byte Buffer::retrieve() { return retrieve(bufferPosition); }

void Buffer::stepBuffer(int stepSize) {
  bufferPosition = (bufferPosition + stepSize) % DELAY_BUFFER_SIZE;
}

void Buffer::stepBuffer() { stepBuffer(1); }
