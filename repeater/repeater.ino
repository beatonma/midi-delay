/**
 * TODO parse messages properly - not all same length https://www.wikiaudio.org/midi-channel-messages-tutorial/#:~:text=There%20are%207%20MIDI%20channel,why%20MIDI%20has%2016%20channels.
 *
 */

const int MIDI_BAUD_RATE = 31250;
const byte MIDI_OUTPUT_CHANNEL = 0;

const byte MIDI_STATUS = B10000000;
const byte MIDI_DATA = B00000000;

const byte NOTE_ON = B10010000;
const byte NOTE_OFF = B10000000;

const byte EMPTY = NOTE_OFF | B1111;

const int DELAY_BUFFER_SIZE = 1024 + 512 + 128 + 4 + 2 + 1;

int currentByte;

byte tempPosition;

byte delayBuffer[DELAY_BUFFER_SIZE];
int bufferPosition = 0;

void setup(){
  for (int i = 0; i < DELAY_BUFFER_SIZE; i = i + 1) {
    reset(i);
  }
  Serial.begin(MIDI_BAUD_RATE);
}

void loop() {
  if (!isEmpty(bufferPosition)) {
    send(bufferPosition);
    reset(bufferPosition);
  }

  stepBuffer(1);

  currentByte = Serial.read();
  if (currentByte > 0) {
    store(bufferPosition, currentByte);
  }
  else {
    reset(bufferPosition);
  }
}

void reset(int position) {
  store(position, EMPTY);
}

bool isEmpty(int position) {
  return retrieve(position) == EMPTY;
}

/**
 * Store a single byte in the buffer at given position.
 */
void store(int position, byte _value) {
  delayBuffer[position % DELAY_BUFFER_SIZE] = _value;
}

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
  tempPosition = position % DELAY_BUFFER_SIZE;
  return delayBuffer[tempPosition];
}

/**
 * Incremement buffer position by stepSize.
 */
void stepBuffer(int stepSize) {
  bufferPosition = (bufferPosition + stepSize) % DELAY_BUFFER_SIZE;
}

void send(int position) {
  Serial.write(retrieve(bufferPosition));
}

byte nextByte() {
  return Serial.read();
}

// byte awaitNextByte() {
//   while (!Serial.available()) {};
//   return Serial.read();
// }

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
