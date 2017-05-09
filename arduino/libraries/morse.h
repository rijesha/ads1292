#ifndef MORSE_h
#define MORSE_h

#include "Arduino.h"

class Morse
{
public:
  Morse(LEDList[]);
  //Morse(int LEDList[]);
  virtual ~Morse();
  void sendMorse(char hi );
};


#endif
