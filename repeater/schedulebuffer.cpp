#include <Arduino.h>
#include "build.h"
#include "types.h"
#include "schedulebuffer.h"

timestamp now;
ScheduledByte _scheduled;

bool ScheduledByte::isEmpty() {
    return triggerTime == 0;
}

void ScheduleBuffer::initBuffer() {

}

void ScheduleBuffer::schedule(byte _value, int delayTime) {

  PRINT(F("scheduling: "));
  PRINT(_value);
  PRINT(" at ");
  PRINTLN(millis() + delayTime);
    push(_value, millis() + delayTime);
}

void ScheduleBuffer::schedule(byte _value) {
    schedule(_value, DELAY_LENGTH);
}

byte ScheduleBuffer::retrieve(timestamp time) {
    _scheduled = peek();
    if (_scheduled.triggerTime <= time) {
        pop();
        return _scheduled.value;
    }
    return 0;
}

byte ScheduleBuffer::retrieve() {
    return retrieve(millis());
}


ScheduledByte ScheduleBuffer::peek() {
    return delayBuffer[0];
}

ScheduledByte ScheduleBuffer::pop() {
    _scheduled = delayBuffer[0];

    for (int i = 0; i < SCHEDULE_BUFFER_SIZE - 1; i++) {
        delayBuffer[i] = delayBuffer[i+1];
    }

    return _scheduled;
}

void ScheduleBuffer::push(byte _value, timestamp triggerTime) {
    for (int i = 0; i < SCHEDULE_BUFFER_SIZE; i++) {
        if (delayBuffer[i].isEmpty()) {
            delayBuffer[i].value = _value;
            delayBuffer[i].triggerTime = triggerTime;
            break;
        }
    }
}
