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
