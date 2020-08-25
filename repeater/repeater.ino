#include "types.h"
#include "build.h"
#include "schedulebuffer.h"
#include "midi.h"
#include "repeater.h"
#include "config.h"

#ifdef DEBUG
#include "mockio.cpp"
MockIO io;
#else
#include "serialio.cpp"
SerialIO io;
#endif

int valueFromIO = 0;
int valueFromBuffer = 0;

int delayTime = DELAY_LENGTH;

ScheduleBuffer buffer;

// Input handlers
DelayPotHandler delay_pot_handler(DELAY_POT_PIN);



void setup() {
  Serial.begin(BAUD_RATE);
  setupInputHandlers();
}

void loop() {

  updateInputHandlers();

  #ifdef DEBUG
  if (io.isFinished()) {
    return;
  }
  #endif // DEBUG


  valueFromBuffer = buffer.retrieve();
  valueFromIO = io.nextByte();


  if (valueFromIO > 0) {
    buffer.schedule(valueFromIO, delayTime);
  }

  while (valueFromBuffer > 0) {
    io.writeByte(valueFromBuffer);
    valueFromBuffer = buffer.retrieve();
  }

  delay(1);
}


void setupInputHandlers(void) {
  delay_pot_handler.setup();
}

void updateInputHandlers(void) {
  delay_pot_handler.update();
}

void DelayPotHandler::onValueChanged(int value) {
  delayTime = map(value, 0, 1023, DELAY_TIME_MIN, DELAY_TIME_MAX);
}
