#include "midi.h"

bool isStatusByte(byte b) {
  return (b & MIDI_STATUS) == MIDI_STATUS;
}

bool isDataByte(byte b) {
  return (b & MIDI_DATA) == MIDI_DATA;
}

bool isNoteOn(byte b) {
  return (b & NOTE_ON) == NOTE_ON;
}

bool isNoteOff(byte b) {
  return (b & NOTE_OFF) == NOTE_OFF;
}
