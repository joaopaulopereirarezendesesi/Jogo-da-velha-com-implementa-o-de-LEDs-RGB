#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include "ligarLed.h"

const int dataPin = 4;
const int latchPin = 3;
const int clockPin = 2;
const int numRegisters = 3;

/*
  LED bit positioning in the array:
  { B00000000, B00000000, B00000000 };
  { Brrrrrrrr, Bbbbbbbbr, B------bb}
  r = Red;
  b = Blue.
  1 = on;
  0 = off.
*/

/*
  ledPatterns[colors][positions] = {
  };
*/

void PosicaoControl::setPosicao(int num, int color, int lay) {
  static const uint8_t ledPatterns[3][9] = {
    { B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000, B00000000 },
    { B00000000, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000, B00000000 },
    { B00000001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }
  };

  ShiftRegister74HC595<numRegisters> sr(dataPin, clockPin, latchPin);

  uint8_t pinValues1[] = { 0, 0, 0 };

  /*
    How are we going to pass the values for the colors or positions as "1", "2", or "3" i used "[color - 1]" 
    and "[num - 1]" to translate that information to the array because if we passed the value as "color = 2 (Blue)" 
    and "num = 2", it would light up the red color and the LED in position 3 on the display, since the counting 
    starts from zero.
  */

  if (color >= 1 && color <= 3) {
    pinValues1[0] = ledPatterns[color - 1][num - 1];
  } else if (color == 4) {
    pinValues1[1] = B11111110;
    pinValues1[2] = B00000011;
  } else if (color == 5) {
    pinValues1[0] = B11111111;
    pinValues1[1] = B00000001;
  } else if (color == 6) {
    pinValues1[0] = B11111111;
    pinValues1[1] = B11111111;
    pinValues1[2] = B00000011;
  } else if (color == 7) {
  }

  sr.setAll(pinValues1);
  delay(lay);
}
