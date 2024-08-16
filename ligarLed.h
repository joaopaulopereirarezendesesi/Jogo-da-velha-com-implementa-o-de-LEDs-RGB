#ifndef LIGARLED_H
#define LIGARLED_H

#include <Arduino.h> // Inclui a biblioteca base do Arduino

// Definição da classe PosicaoControl
class PosicaoControl {
private:
  int _dlay;          // Atraso (delay) em milissegundos
  int _numposicao;    // Número da posição do LED
  int _cor;           // Cor do LED

public:
  // Define a posição no jogo da velha e retorna o estado do LED
  uint8_t* setPosicaoTicTacToe(int num, int color, int lay);
  
  // Configura a posição do LED com a cor especificada e o delay
  void setPosicao(int num, int color, int lay);
  
  // Reseta todos os LEDs para o estado apagado
  void resetAllLeds();
};

#endif // LIGARLED_H
