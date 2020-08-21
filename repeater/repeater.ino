/**
 * TODO parse messages properly - not all same length https://www.wikiaudio.org/midi-channel-messages-tutorial/#:~:text=There%20are%207%20MIDI%20channel,why%20MIDI%20has%2016%20channels.
 *
 */

const int DEBUG_BAUD_RATE = 19200;
const int MIDI_BAUD_RATE = 31250;
const int DELAY_BUFFER_SIZE = 3 * 24; // ~500 bytes - multiple of 3 for command, note, velocity

const byte MIDI_STATUS = B10000000;
const byte MIDI_DATA = B00000000;

const byte NOTE_ON = B10010000;
const byte NOTE_OFF = B10000000;

const byte FAKE_MIDI[] = {
  NOTE_ON,
  100,
  60,

  NOTE_ON,
  50,
  80,

  NOTE_OFF,
  100,
  60,

  NOTE_OFF,
  50,
  80
};

const byte fakeMidiSize = 12;
byte fakePosition = 0;

byte command = NOTE_OFF;
byte velocity = 100;
byte note = 50;

byte currentByte;
byte status;
byte dataOne;
byte dataTwo;

byte tempPosition;
byte tempValue;

byte delayBuffer[DELAY_BUFFER_SIZE];
int bufferPosition = 0;

void setup(){
  Serial.begin(DEBUG_BAUD_RATE);
}

void loop() {
  currentByte = nextByte();

  if (currentByte == 0) {
    return;
  }

  Serial.println(fakePosition);
  Serial.println(currentByte);

  if (isStatusByte(currentByte)) {
    Serial.println("isStatusByte!");
    handleStatusMessage(currentByte);
  }
  else if (isDataByte(currentByte)) {
    Serial.println("isDataByte!");
  }
  Serial.println("-");
}


void store(int position, byte _value) {
  delayBuffer[position % DELAY_BUFFER_SIZE] = _value;
}

void store(int position, byte _status, byte _dataOne, byte _dataTwo) {
  store(position, _status);
  store(position + 1, _dataOne);
  store(position + 2, _dataTwo);
}

byte retrieve(int position) {
  tempPosition = position % DELAY_BUFFER_SIZE;
  tempValue = delayBuffer[tempPosition];

  return tempValue;
}

void stepBuffer(int stepSize) {
  bufferPosition = (bufferPosition + stepSize) % DELAY_BUFFER_SIZE;
}

bool isStatusByte(byte b) {
  // Serial.println('+');
  // Serial.println(b);
  // Serial.println(b & MIDI_STATUS);
  // Serial.println('+');
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

// void sendDelayedMidi() {
//   stepBuffer(3);
//   sendMidi(
//     retrieveCommand(bufferPosition),
//     retrieveNote(bufferPosition),
//     retrieveVelocity(bufferPosition)
//   );
// }

void sendMidi(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

byte nextByte() {
  if (fakePosition < fakeMidiSize) {
    byte value = FAKE_MIDI[fakePosition];
    fakePosition += 1;
    return value;
  }
  return 0;
  // while (!Serial.available()) {};
  // return Serial.read();
}

void handleStatusMessage(byte statusByte) {
  if (isNoteOn(statusByte)) {
    Serial.println("isNoteOn!");
  }
  else if (isNoteOff(statusByte)) {
    Serial.println("isNoteOff!");
  }
  else {
    Serial.println("UNKNOWN STATUS");
  }
}
