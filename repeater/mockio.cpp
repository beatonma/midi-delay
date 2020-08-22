#include "mockio.h"

#include "io.h"
#include "midi.h"
#include "types.h"

const byte MOCK_MIDI[] = {
    NOTE_ON | MIDI_OUTPUT_CHANNEL,  60, 70,

    NOTE_ON | MIDI_OUTPUT_CHANNEL,  31, 91,

    NOTE_OFF | MIDI_OUTPUT_CHANNEL, 60, 70,

    NOTE_OFF | MIDI_OUTPUT_CHANNEL, 31, 91,
};
const int MIDI_LENGTH = 12;

class MockIO : public IO {
 private:
  byte _value;
  int midiPosition = 0;

 public:
  MockIO() {}

  byte nextByte() {
    _value = MOCK_MIDI[midiPosition];
    midiPosition = (midiPosition + 1) % MIDI_LENGTH;
    return _value;
  }

  byte awaitNextByte() { return 0; }

  void writeByte(byte b) {}
};

IO* initIO() {
    return new MockIO;
}

// byte nextByte() {
//     _value = MOCK_MIDI[midiPosition];
//     midiPosition = (midiPosition + 1) % MIDI_LENGTH;
//     return _value;
// }

// byte awaitNextByte() {
//     return 0;
// }

// void writeByte(byte b) {

// }
