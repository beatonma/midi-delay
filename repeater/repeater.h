#ifndef REPEATER_H
#define REPEATER_H

#include "input/input-potentiometer.cpp"

void setupInputHandlers(void);
void updateInputHandlers(void);

class DelayPotHandler: public AbstractPotentiometerHandler {
  public:
  DelayPotHandler(byte pin): AbstractPotentiometerHandler(pin) {}
  void onValueChanged(int value);
//   void onValueChangedNoModifier(int value);       ///< Called when the pot is turned with no other inputs
//   void onValueChangedWithModeButton(int value);   ///< Called when the pot is turned while the Mode button is held down
//   void onValueChangedWithOptionButton(int value); ///< Called when the pot is turned while the Option button is held down
};

#endif // REPEATER_H
