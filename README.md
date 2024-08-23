# 🕹️ Jogo da Velha com LEDs e Animações 💡

Este projeto utiliza um Arduino para controlar LEDs em um jogo da velha e exibir animações aleatórias. O controle dos LEDs é feito com a ajuda de um registrador de deslocamento 74HC595.

## 📁 Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

1. **Código Principal (`Mein.ino`)**
2. **Biblioteca de Controle de LEDs (`ligarLed.h` e `ligarLed.cpp`)**

### 📜 Código Principal (`Mein.ino`)

O código principal configura botões para interagir com o jogo da velha e também permite a exibição de animações aleatórias.

#### 🚀 Funções Importantes:

- **`setup()`**: Configura a comunicação Serial, os botões e aguarda a seleção da função do display (1 para Jogo da Velha, 2 para Animação Aleatória).

- **`loop()`**: Gerencia a lógica do jogo da velha ou a exibição de animações baseadas na seleção feita pelo usuário.

  - **🕹️ Jogo da Velha**: Atualiza o tabuleiro com base nos botões pressionados e verifica padrões de vitória. Reinicia o jogo se necessário.

  - **✨ Animação Aleatória**: Acende LEDs em posições e cores aleatórias por um tempo definido.

### 💡 Biblioteca de Controle de LEDs

Esta biblioteca define a classe `PosicaoControl`, que gerencia o controle dos LEDs através do registrador 74HC595.

#### Arquivos:

- **`ligarLed.h`**: Define a interface da classe `PosicaoControl`.

  ```cpp
  #ifndef LIGARLED_H
  #define LIGARLED_H

  #include <Arduino.h>

  class PosicaoControl {
  private:
    int _dlay;          // Delay em milissegundos
    int _numposicao;    // Número da posição do LED
    int _cor;           // Cor do LED

  public:
    uint8_t* setPosicaoTicTacToe(int num, int color, int lay);
    void setPosicao(int num, int color, int lay);
    void resetAllLeds();
  };

  #endif // LIGARLED_H
  ```
  
- **`ligarLed.cpp`**: Define a lógica de `PosicaoControl`.
  
 ```cpp
 #include <Arduino.h>
 #include <ShiftRegister74HC595.h>
 #include "ligarLed.h"

 // Definições de pinos e registradores
 const int dataPin = 4;
 const int latchPin = 3;
 const int clockPin = 2;
 const int numRegisters = 3;

 ShiftRegister74HC595<numRegisters> sr(dataPin, clockPin, latchPin);

 // Estado inicial dos LEDs
 uint8_t ledState[3] = { B00000000, B00000000, B00000000 };

 // Função para verificar se o padrão de vitória está contido no estado atual dos LEDs
 bool containsPattern(const uint8_t* arr, const uint8_t* pattern, size_t length) {
     for (size_t i = 0; i < length; i++) {
         if ((arr[i] & pattern[i]) != pattern[i]) {
             return false;
         }
     }
     return true;
 }

 // Função para configurar a posição no jogo da velha
 uint8_t* PosicaoControl::setPosicaoTicTacToe(int num, int color, int lay) {
     // Atualizar o estado dos LEDs com base na cor e posição
     if (color == 1) {
         switch (num) {
             case 1: ledState[0] |= B00000001; break;
             case 2: ledState[0] |= B00000010; break;
             case 3: ledState[0] |= B00000100; break;
             case 4: ledState[0] |= B00001000; break;
             case 5: ledState[0] |= B00010000; break;
             case 6: ledState[0] |= B00100000; break;
             case 7: ledState[0] |= B01000000; break;
             case 8: ledState[0] |= B10000000; break;
             case 9: ledState[1] |= B00000001; break;
         }
     } else if (color == 2) {
         switch (num) {
             case 1: ledState[1] |= B00000010; break;
             case 2: ledState[1] |= B00000100; break;
             case 3: ledState[1] |= B00001000; break;
             case 4: ledState[1] |= B00010000; break;
             case 5: ledState[1] |= B00100000; break;
             case 6: ledState[1] |= B01000000; break;
             case 7: ledState[1] |= B10000000; break;
             case 8: ledState[2] |= B00000001; break;
             case 9: ledState[2] |= B00000010; break;
         }
     } else if (color == 3) {
         switch (num) {
             case 1: ledState[0] |= B00000001; ledState[1] |= B00000010; break;
             case 2: ledState[0] |= B00000010; ledState[1] |= B00000100; break;
             case 3: ledState[0] |= B00000100; ledState[1] |= B00001000; break;
             case 4: ledState[0] |= B00001000; ledState[1] |= B00010000; break;
             case 5: ledState[0] |= B00010000; ledState[1] |= B00100000; break;
             case 6: ledState[0] |= B00100000; ledState[1] |= B01000000; break;
             case 7: ledState[0] |= B01000000; ledState[1] |= B10000000; break;
             case 8: ledState[0] |= B10000000; ledState[2] |= B00000001; break;
             case 9: ledState[1] |= B00000001; ledState[2] |= B00000010; break;
         }
     }

     // Padrões de vitória possíveis
     uint8_t winningpatterns[16][3] = {
         { B00000111, B00000000, B00000000 }, // Linha 1 
         { B00111000, B00000000, B00000000 }, // Linha 2
         { B11000000, B00000001, B00000000 }, // Linha 3
         { B00000000, B00001110, B00000000 }, // Linha 4
         { B00000000, B01110000, B00000000 }, // Linha 5
         { B00000000, B10000000, B00000011 }, // Linha 6
         { B00010001, B00000001, B00000000 }, // Diagonal 1
         { B00000000, B00100010, B00000010 }, // Diagonal 2
         { B01010100, B00000000, B00000000 }, // Diagonal 3
         { B00000000, B10101000, B00000000 }, // Diagonal 4
         { B01001001, B00000000, B00000000 }, // Coluna 1
         { B10010010, B00000000, B00000000 }, // Coluna 2
         { B00100100, B00000001, B00000000 }, // Coluna 3
         { B00000000, B10010010, B00000000 }, // Coluna 4
         { B00000000, B00100100, B00000001 }, // Coluna 5
         { B00000000, B01001000, B00000010 }  // Coluna 6
     };

     // Verificar se há um padrão de vitória
     for (int i = 0; i < 16; i++) {
         if (containsPattern(ledState, winningpatterns[i], 3)) {
             sr.setAll(ledState);
             delay(lay);
             for (int j = 0; j < 3; j++) {
                 ledState[j] = winningpatterns[i][j];
             }
             sr.setAll(ledState);
             delay(lay);
             return 1; // Vitória
         }
     }
     sr.setAll(ledState);
     delay(lay);

     return 0; // Continuar jogo
 }

 // Função para configurar os LEDs
 void PosicaoControl::setPosicao(int num, int color, int lay) {
     _numposicao = num;
     _cor = color;
     _dlay = lay;

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
     }

     sr.setAll(pinValues1);
     delay(_dlay);
 }

 // Função para resetar todos os LEDs
 void PosicaoControl::resetAllLeds() {
     ledState[0] = B00000000;
     ledState[1] = B00000000;
     ledState[2] = B00000000;
 
     sr.setAll(ledState);
 } 
  ```
