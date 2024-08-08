# Jogo da velha com implementação de LEDs RGB

O objetivo desses codigo é fazer um jogo da velha com LEDs RGB, para fazer isso eu utilizei de um Shiftregister, mais expecificamente o 74HC595 e de praxe a biblioteca dele a "ShiftRegister74HC595.h".

## Programação base 

A programação base se trata de como eu iria fazer os LEDs acenderem, e foi "simplismente" usar a biblioteca, para começar eu tinha que definir qual a condiguração de bits que controla as cores LED, a configuração que 
eu cheguei foi a seguinte:

```c++
 { B00000000, B00000000, B00000000 };
 { Brrrrrrrr, Bbbbbbbbr, B------bb };
  r = Red;
  b = Blue.
  1 = connected;
  0 = off.
```

