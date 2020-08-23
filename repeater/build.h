#ifndef BUILD_H
#define BUILD_H

// #define DEBUG

#ifdef DEBUG
#define PRINT(x) Serial.print(x)
#define PRINTLN(x) Serial.println(x)

#else // DEBUG
#define PRINT(x)
#define PRINTLN(x)

#endif // DEBUG

#endif // BUILD_H
