#include <Arduino.h>
#include <ShiftRegister74HC595.h>
#include "ligarLed.h"

const int dataPin = 4;
const int latchPin = 3;
const int clockPin = 2;
const int numRegisters = 3;

/*
  LED bit positioning in the vector:
  { B00000000, B00000000, B00000000 };
  { Brrrrrrrr, Bbbbbbbbr, B------bb}
  r = Red;
  b = Blue.
  1 = connected;
  0 = off.
*/

void PosicaoControl::setPosicao(int num, int color, int lay) {
  _numposicao = num;
  _cor = color;
  _dlay = lay;
  ShiftRegister74HC595<numRegisters> sr(dataPin, clockPin, latchPin);

  if (_cor == 1) {
    if (_numposicao == 1) {
      uint8_t pinValues1[] = { B00000001, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 2) {
      uint8_t pinValues1[] = { B00000010, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 3) {
      uint8_t pinValues1[] = { B00000100, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 4) {
      uint8_t pinValues1[] = { B00001000, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 5) {
      uint8_t pinValues1[] = { B00010000, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 6) {
      uint8_t pinValues1[] = { B00100000, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 7) {
      uint8_t pinValues1[] = { B01000000, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 8) {
      uint8_t pinValues1[] = { B10000000, B00000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 9) {
      uint8_t pinValues1[] = { B00000000, B00000001, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    }
  } else if (_cor == 2) {
    if (_numposicao == 1) {
      uint8_t pinValues1[] = { B00000000, B00000010, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 2) {
      uint8_t pinValues1[] = { B00000000, B00000100, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 3) {
      uint8_t pinValues1[] = { B00000000, B00001000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 4) {
      uint8_t pinValues1[] = { B00000000, B00010000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 5) {
      uint8_t pinValues1[] = { B00000000, B00100000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 6) {
      uint8_t pinValues1[] = { B00000000, B01000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 7) {
      uint8_t pinValues1[] = { B00000000, B10000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 8) {
      uint8_t pinValues1[] = { B00000000, B00000000, B00000001 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 9) {
      uint8_t pinValues1[] = { B00000000, B00000000, B00000010 };
      sr.setAll(pinValues1);
      delay(_dlay);
    }
  } else if (_cor == 3) {
    if (_numposicao == 1) {
      uint8_t pinValues1[] = { B00000001, B00000010, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 2) {
      uint8_t pinValues1[] = { B00000010, B00000100, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 3) {
      uint8_t pinValues1[] = { B00000100, B00001000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 4) {
      uint8_t pinValues1[] = { B00001000, B00010000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 5) {
      uint8_t pinValues1[] = { B00010000, B00100000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 6) {
      uint8_t pinValues1[] = { B00100000, B01000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 7) {
      uint8_t pinValues1[] = { B01000000, B10000000, B00000000 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 8) {
      uint8_t pinValues1[] = { B10000000, B00000000, B00000001 };
      sr.setAll(pinValues1);
      delay(_dlay);
    } else if (_numposicao == 9) {
      uint8_t pinValues1[] = { B00000000, B00000001, B00000010 };
      sr.setAll(pinValues1);
      delay(_dlay);
    }
  } else if (_cor == 4) {
    uint8_t pinValues1[] = { B00000000, B11111110, B00000011 };
    sr.setAll(pinValues1);
    delay(_dlay);
  } else if (_cor == 5) {
    uint8_t pinValues1[] = { B11111111, B00000001, B00000000 };
    sr.setAll(pinValues1);
    delay(_dlay);
  } else if (_cor == 6) {
    uint8_t pinValues1[] = { B11111111, B11111111, B00000011 };
    sr.setAll(pinValues1);
    delay(_dlay);
  } else if (_cor == 7) {
    uint8_t pinValues1[] = { B00000000, B00000000, B00000000 };
    sr.setAll(pinValues1);
    delay(_dlay);
  }
}
