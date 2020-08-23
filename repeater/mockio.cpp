#include <Arduino.h>
#include "build.h"
#include "mockio.h"

#include "io.h"
#include "midi.h"
#include "types.h"

const int BAUD_RATE = 19200;

const int MIDI_LENGTH = 12;
const byte MOCK_MIDI[] = {
    NOTE_ON | MIDI_OUTPUT_CHANNEL,  60, 70,

    NOTE_ON | MIDI_OUTPUT_CHANNEL,  31, 91,

    NOTE_OFF | MIDI_OUTPUT_CHANNEL, 60, 70,

    NOTE_OFF | MIDI_OUTPUT_CHANNEL, 31, 91,
};

class MockIO : public IO {
 private:
  byte _value;
  int midiPosition = 0;

 public:
  MockIO() {}

  byte nextByte() {
      if (isFinished()) {
        return 0;
    }

    _value = MOCK_MIDI[midiPosition % MIDI_LENGTH];
    print(F("nextByte ["));
    print(midiPosition);
    print(F("]: "));
    println(_value);

    midiPosition = (midiPosition + 1);

    return _value;
  }

  byte awaitNextByte() { return 0; }

  void writeByte(byte b) {
    print(F("writeByte: "));
    println(b);
  }

  bool isFinished() {
    return midiPosition > (MIDI_LENGTH * 2);
  }
};

IO* initIO() { return new MockIO; }
