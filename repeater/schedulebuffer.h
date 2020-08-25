#ifndef SCHEDULE_BUFFER_H
#define SCHEDULE_BUFFER_H

#include "types.h"

const int SCHEDULE_BUFFER_SIZE = 330;
const int DELAY_LENGTH = 120;  // Default, milliseconds

class ScheduledByte {
 public:
  ScheduledByte(){};
  byte value = 0;
  timestamp triggerTime = 0;

  bool isEmpty();
};

/**
 * Byte values are stored with a timestamp at which they
 * should trigger.
 */
class ScheduleBuffer {
 private:
  ScheduledByte delayBuffer[SCHEDULE_BUFFER_SIZE];

 public:
  ScheduleBuffer(){};

  void initBuffer();

  void schedule(byte _value, int delayTime);
  void schedule(byte _value);

  byte retrieve(timestamp time);
  byte retrieve();

  void push(byte _value, timestamp triggerTime);

  ScheduledByte peek();
  ScheduledByte pop();
};

#endif  // SCHEDULE_BUFFER_H
