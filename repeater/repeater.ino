const byte NOTE_ON = 144;
const byte NOTE_OFF = 128;

byte command = NOTE_ON;
byte velocity = 100;
byte note = 50;

bool noteOn = false;

void setup(){
 Serial.begin(31250);
}

void writeMidi(byte command, byte note, byte velocity) {
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}

void checkMIDI(){
  do{
    if (Serial.available()){
      command = Serial.read();
      note = Serial.read();
      velocity = Serial.read();

      writeMidi(command, note, velocity);
    }
  }
  while (Serial.available() > 2);
}


void loop(){
  checkMIDI();
}
