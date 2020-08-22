#ifndef MIDI_H
#define MIDI_H

#include "types.h"

const int MIDI_BAUD_RATE = 31250;

const byte MIDI_OUTPUT_CHANNEL = 0b0;
const byte DUMP_CHANNEL = 0b1111;  // Channel we can use when we need to send something but don't want it to have any effect

const byte MIDI_STATUS = 0b10000000;
const byte MIDI_DATA = 0b00000000;

const byte NOTE_ON = 0b10010000;
const byte NOTE_OFF = 0b10000000;

const byte EMPTY = NOTE_OFF | DUMP_CHANNEL;

bool isStatusByte(byte b);
bool isDataByte(byte b);

bool isNoteOn(byte b);
bool isNoteOff(byte b);

#endif
