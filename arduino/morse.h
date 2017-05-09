#ifndef MORSE_h
#define MORSE_h

#include "Arduino.h"

#define dotLen 100     // length of the morse code 'dot'
#define dashLen dotLen * 3    // length of the morse code 'dash'
#define elemPause dotLen  // length of the pause between elements of a character
#define Spaces dotLen * 3     // length of the spaces between characters
#define wordPause dotLen * 7  // length of the pause between words



class Morse
{
public:
  Morse(int LEDList[], int list_length);
  //Morse(int LEDList[]);
  virtual ~Morse();
  void sendMorse(char msg[] ,int length);
private:
  int * LEDs;
  int numOFLEDs;
  void LightsOff(int);
  void LightsOn();
  void digitalWriteList(uint8_t);
  void MorseDot();
  void MorseDash();
  void GetChar(char);
};


#endif
