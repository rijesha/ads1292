#include <Arduino.h>
#include "morse.h"

int dotLen = 100;     // length of the morse code 'dot'
int dashLen = dotLen * 3;    // length of the morse code 'dash'
int elemPause = dotLen;  // length of the pause between elements of a character
int Spaces = dotLen * 3;     // length of the spaces between characters
int wordPause = dotLen * 7;  // length of the pause between words


  // Create variable to define the output pins
  private int LEDList[];
//
Morse::Morse(LEDList[]) {}
Morse::~Morse() {}

  //Morse::Morse(int LEDList[]) : LEDList(LEDList) {
  //}

  void Morse::sendMorse(char stringToMorseCode) {
    for (int i = 0; i < sizeof(stringToMorseCode) - 1; i++)
    {
      // Get the character in the current position
    char tmpChar = stringToMorseCode[i];
    // Set the case to lower case
    tmpChar = toLowerCase(tmpChar);
    // Call the subroutine to get the morse code equivalent for this character
    GetChar(tmpChar);
    }

    // At the end of the string long pause before looping and starting again
    LightsOff(2000);
    LightsOn();
  }
  // DOT
  void Morse::MorseDot()
  {
    digitalWriteList(led12, HIGH);  	// turn the LED on
    digitalWriteList(led6, HIGH);
    delay(dotLen);             	// hold in this position
  }

  // DASH
  void Morse::MorseDash()
  {
    digitalWriteList(led12, HIGH);  	// turn the LED on
    digitalWriteList(led6, HIGH);
    delay(dashLen);               // hold in this position
  }

  // Turn On
  void Morse::LightsOn()
  {
    digitalWriteList(led12, HIGH);    	// turn the LED on
    digitalWriteList(led6, HIGH);
  }

  // Turn Off
  void Morse::LightsOff(int delayTime)
  {
    digitalWrite(led12, LOW);    	// turn the LED off
    digitalWriteList(led6, LOW);
    delay(delayTime);            	// hold in this position
  }

  // *** Characters to Morse Code Conversion *** //
  void Morse::GetChar(char tmpChar)
  {
  	// Take the passed character and use a switch case to find the morse code for that character
  	switch (tmpChar) {
  	  case 'a':
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'b':
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'c':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'd':
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'e':
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'f':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'g':
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'h':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'i':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'j':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
        case 'k':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'l':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
        case 'm':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'n':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'o':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'p':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 'q':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'r':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 's':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  case 't':
  	    MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'u':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'v':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'w':
  	    MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'x':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'y':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		break;
  	  case 'z':
  	    MorseDash();
  		LightsOff(elemPause);
  		MorseDash();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		MorseDot();
  		LightsOff(elemPause);
  		break;
  	  default:
  		// If a matching character was not found it will default to a blank space
  		LightsOff(Spaces);
  	}
  }
