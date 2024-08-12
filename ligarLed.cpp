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

void PosicaoControl::setPosicao(int num, int color, int lay) {
  _numposicao = num;
  _cor = color;
  _dlay = lay;
  ShiftRegister74HC595<numRegisters> sr(dataPin, clockPin, latchPin);

  uint8_t pinValues1[3] = { B00000000, B00000000, B00000000 };

  if (_cor == 1) {
    switch (_numposicao) {
      case 1: pinValues1[0] = B00000001; break;
      case 2: pinValues1[0] = B00000010; break;
      case 3: pinValues1[0] = B00000100; break;
      case 4: pinValues1[0] = B00001000; break;
      case 5: pinValues1[0] = B00010000; break;
      case 6: pinValues1[0] = B00100000; break;
      case 7: pinValues1[0] = B01000000; break;
      case 8: pinValues1[0] = B10000000; break;
      case 9: pinValues1[1] = B00000001; break;
    }
  } else if (_cor == 2) {
    switch (_numposicao) {
      case 1: pinValues1[1] = B00000010; break;
      case 2: pinValues1[1] = B00000100; break;
      case 3: pinValues1[1] = B00001000; break;
      case 4: pinValues1[1] = B00010000; break;
      case 5: pinValues1[1] = B00100000; break;
      case 6: pinValues1[1] = B01000000; break;
      case 7: pinValues1[1] = B10000000; break;
      case 8: pinValues1[2] = B00000001; break;
      case 9: pinValues1[2] = B00000010; break;
    }
  } else if (_cor == 3) {
    switch (_numposicao) {
      case 1: pinValues1[0] = B00000001; pinValues1[1] = B00000010; break;
      case 2: pinValues1[0] = B00000010; pinValues1[1] = B00000100; break;
      case 3: pinValues1[0] = B00000100; pinValues1[1] = B00001000; break;
      case 4: pinValues1[0] = B00001000; pinValues1[1] = B00010000; break;
      case 5: pinValues1[0] = B00010000; pinValues1[1] = B00100000; break;
      case 6: pinValues1[0] = B00100000; pinValues1[1] = B01000000; break;
      case 7: pinValues1[0] = B01000000; pinValues1[1] = B10000000; break;
      case 8: pinValues1[0] = B10000000; pinValues1[2] = B00000001; break;
      case 9: pinValues1[1] = B00000001; pinValues1[2] = B00000010; break;
    }
  } else if (_cor == 4) {
    pinValues1[1] = B11111110;
    pinValues1[2] = B00000011;
  } else if (_cor == 5) {
    pinValues1[0] = B11111111;
    pinValues1[1] = B00000001;
  } else if (_cor == 6) {
    pinValues1[0] = B11111111;
    pinValues1[1] = B11111111;
    pinValues1[2] = B00000011;
  } else if (_cor == 7) {
    pinValues1[0] = B00000000;
    pinValues1[1] = B00000000;
    pinValues1[2] = B00000000;
  }

  sr.setAll(pinValues1);
  delay(_dlay);
}
