#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"
#include "midi.h"

void initBuffer();

void reset(int position);
void reset();

bool isEmpty(int position);
bool isEmpty();

/**
 * Store a single byte in the buffer at given position.
 */
void store(int position, byte _value);

/**
 * Store a single byte in the buffer at bufferPosition.
 */
void store(byte _value);

/**
 * Store a data message in the buffer, starting at given position.
 */
void store(int position, byte _status, byte _dataOne);

/**
 * Store a status message in the buffer, starting at given position.
 */
void store(int position, byte _status, byte _dataOne, byte _dataTwo);

/**
 * Get the value at given position of delay buffer.
 */
byte retrieve(int position);

/**
 * Get the value at given position of delay buffer.
 */
byte retrieve();

void stepBuffer(int stepSize);

void stepBuffer();

#endif
