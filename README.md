# 🎮 Tic-Tac-Toe com LEDs no Arduino

> Este projeto implementa um jogo da velha usando LEDs controlados por um Arduino. Além do jogo da velha, há uma função de animação aleatória para os LEDs. O projeto utiliza um registrador de deslocamento 74HC595 para controlar os LEDs e a biblioteca `Bounce2` para gerenciar os botões.

## 📝 Descrição do Projeto

O projeto é composto por três arquivos principais:

1. `main.ino` - O código principal que controla o jogo da velha e a animação aleatória.
2. `ligarLed.h` - Cabeçalho da classe `PosicaoControl`, que gerencia os LEDs.
3. `ligarLed.cpp` - Implementação da classe `PosicaoControl`, que inclui a lógica de controle dos LEDs e a verificação dos padrões de vitória.

## 📂 Estrutura dos Arquivos

- **main.cpp**: Contém a lógica do jogo da velha e a função de animação aleatória.
- **ligarLed.h**: Define a classe `PosicaoControl`, usada para controlar os LEDs.
- **ligarLed.cpp**: Implementa a lógica para acender os LEDs com base nas posições e nas cores, além de verificar os padrões de vitória.

## 🚀 Funcionalidades

1. **Jogo da Velha** 🎮:
   - Dois jogadores se alternam pressionando botões, representando células do tabuleiro.
   - LEDs são usados para indicar as jogadas de cada jogador.
   - A lógica do jogo verifica padrões de vitória e indica quando há um vencedor ou um empate.

2. **Animação Aleatória** 🎨:
   - LEDs acendem aleatoriamente em diferentes cores e posições.
   - As animações são reiniciadas após um curto período.

## 📦 Dependências

- **Hardware**:
  - Arduino
  - Registradores de deslocamento 74HC595
  - LEDs
  - Botões
  - Resistores

- **Bibliotecas**:
  - [`Bounce2`](https://github.com/thomasfredericks/Bounce2): Biblioteca para debouncing de botões.
  - [`ShiftRegister74HC595`](https://github.com/Simsso/ShiftRegister74HC595): Biblioteca para controle do registrador de deslocamento.

## ⚙️ Instalação

1. Clone o repositório:
   
   ```bash
   git clone https://github.com/joaopaulopereirarezendesesi/Jogo-da-velha-com-implementa-o-de-LEDs-RGB
   ```
3. Abra o projeto no Arduino IDE ou na sua IDE preferida.
4. Instale as bibliotecas necessárias através do Gerenciador de Bibliotecas.
5. Compile e carregue o código no seu Arduino.

> Caso queira testar com um hardware já montado entre no meu projeto do Wokwi: [Projeto de jogo da velha com LEDs RGB](https://wokwi.com/projects/400801421156964353)

## 💡 Como Usar

- **Jogo da Velha**:
    1. Após o upload do código, selecione a opção `1` no monitor serial para iniciar o jogo da velha.
    2. Pressione os botões correspondentes às células do tabuleiro para realizar suas jogadas.
    3. O jogo indicará o vencedor ou um empate após o término.

- **Animação Aleatória**:
    1. Selecione a opção `2` no monitor serial para iniciar a animação aleatória.
    2. Aproveite as animações coloridas dos LEDs!

## 🛠️ Personalização

- Modifique as cores e o tempo de delay na função `setPosicao()` no arquivo `main.ino` para personalizar as animações e as cores dos LEDs.
- Adicione novos padrões de vitória ou mude o comportamento do jogo na função `setPosicaoTicTacToe()`.

## 📜 Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo [`LICENSE`](https://github.com/joaopaulopereirarezendesesi/Jogo-da-velha-com-implementa-o-de-LEDs-RGB/blob/main/LICENSE) para mais detalhes.

## 📝 Criador

Feito com por [João Paulo Pereira Rezende](https://github.com/joaopaulopereirarezendesesi)
