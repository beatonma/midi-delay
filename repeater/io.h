#ifndef IO_H
#define IO_H

#include "types.h"

class IO {
 public:
  IO() {}

  virtual byte nextByte() = 0;
  virtual byte awaitNextByte() = 0;

  virtual void writeByte(byte b) = 0;
};

inline IO* initIO();

#endif
