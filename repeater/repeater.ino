const int MIDI_BAUD_RATE = 31250;
const int DELAY_BUFFER_SIZE = 3 * 128; // ~500 bytes - multiple of 3 for command, note, velocity


byte command = 144;
byte velocity = 100;
byte note = 50;

byte delayBuffer[DELAY_BUFFER_SIZE];
int bufferPosition = 0;

void setup(){
  Serial.begin(MIDI_BAUD_RATE);
}

void storeCommand(int position, byte _command) {
  delayBuffer[position] = _command;
}

void storeNote(int position, byte _note) {
  delayBuffer[position + 1] = _note;
}

void storeVelocity(int position, byte _velocity) {
  delayBuffer[position + 2] = _velocity;
}


byte retrieveCommand(int position) {
  return delayBuffer[(position) % DELAY_BUFFER_SIZE];
}

byte retrieveNote(int position) {
  return delayBuffer[(position + 1) % DELAY_BUFFER_SIZE];
}

byte retrieveVelocity(int position) {
  return delayBuffer[(position + 2) % DELAY_BUFFER_SIZE];
}


void writeMidi(byte command, byte note, byte velocity) {
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}

void checkMIDI(){
  do {
    if (Serial.available()){

      command = Serial.read();
      note = Serial.read();
      velocity = Serial.read();

      storeCommand(bufferPosition, command);
      storeVelocity(bufferPosition, velocity);
      storeNote(bufferPosition, note);

      bufferPosition = (bufferPosition + 3) % DELAY_BUFFER_SIZE;

      writeMidi(
        retrieveCommand(bufferPosition),
        retrieveVelocity(bufferPosition),
        retrieveNote(bufferPosition)
      );
    }
  }
  while (Serial.available() > 2);
}


void loop(){
  checkMIDI();
}
