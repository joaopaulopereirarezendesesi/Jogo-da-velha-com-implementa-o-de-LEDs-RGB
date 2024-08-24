#include <Arduino.h>
#include <Bounce2.h>
#include "ligarLed.h"

// Instancia o controlador de LEDs
PosicaoControl posCtrl;

// Configuração dos botões e variáveis do jogo
int selectFunction = 0;
const int buttonPins[9] = { 5, 6, 7, 8, 9, 10, 11, 12, 13 };
Bounce buttons[9];
int player = 1;
int oldGameState = 0;
int board[3][3] = { 0 };

// Função para carregar a interface
void loading() {
  Serial.print("Loading: ");
  for (int i = 0; i < 10; i++) {
    Serial.print("=");
    delay(500);
  }
  Serial.println(" Complete!");
  delay(2000);
}

// Função para reiniciar o jogo
void resetGame() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = 0;
    }
  }
  player = 1;
  Serial.println("Player 1's turn.");
}

// Função para verificar se o tabuleiro está cheio
bool isBoardFull() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

// Configuração inicial
void setup() {
  Serial.begin(115200);

  // Configura os botões
  for (int i = 0; i < 9; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttons[i].attach(buttonPins[i]);
    buttons[i].interval(20);
  }

  randomSeed(analogRead(0));

  Serial.println("Enter what you want to do with the display:");
  Serial.println("1 = Tic-Tac-Toe;");
  Serial.println("2 = Random Animation;");

  // Espera a seleção da função
  while (selectFunction == 0) {
    if (Serial.available() > 0) {
      char received = Serial.read();
      if (received >= '1' && received <= '2') {
        selectFunction = received - '0';
        loading();
        Serial.print("Selected function: ");
        Serial.println(selectFunction);
      } else {
        Serial.println("Invalid number. Enter 1 or 2.");
      }
      delay(100);
    }
  }
}

// Função principal do loop
void loop() {
  if (selectFunction == 0) {
    return;
  }

  // Verifica se a função selecionada foi alterada via Serial
  if (Serial.available() > 0) {
    char newSelection = Serial.read();
    if (newSelection >= '1' && newSelection <= '2') {
      selectFunction = newSelection - '0';
      loading();
      Serial.print("Function changed to: "); Serial.println(selectFunction);
    }
    delay(100);
  }

  switch (selectFunction) {
    case 1: // Jogo da Velha
      {
        int gameOver = 0;
        oldGameState = 0;
        resetGame();
        posCtrl.resetAllLeds();
        while (gameOver == 0 && oldGameState == 0) {
          posCtrl.players(player);  // Adicionando ponto e vírgula
          for (int i = 0; i < 9; i++) {
            buttons[i].update();
            if (buttons[i].fell()) {
              int ledPosition = 9 - i;
              if (board[(ledPosition - 1) / 3][(ledPosition - 1) % 3] == 0) {
                board[(ledPosition - 1) / 3][(ledPosition - 1) % 3] = player;
                int result = posCtrl.setPosicaoTicTacToe(ledPosition, player, 1000);
                if (result == 1) {
                  Serial.print("The winner is player "); Serial.print(player); Serial.println("!");
                  gameOver = 1;
                  if (player == 1) {
                    posCtrl.setPosicao(0, 5, 1000);
                    posCtrl.resetAllLeds();
                  } else {
                    posCtrl.setPosicao(0, 4, 1000);
                    posCtrl.resetAllLeds();
                  }
                  delay(2000);
                  resetGame();
                } else if (isBoardFull()) {
                  oldGameState = 1;
                  Serial.println("It's a tie!");
                  posCtrl.setPosicao(0, 6, 500); 
                  posCtrl.setPosicao(0, 7, 500); 
                  posCtrl.setPosicao(0, 6, 500);
                  posCtrl.resetAllLeds();
                  delay(2000);
                  resetGame();
                } else {
                  player = (player == 1) ? 2 : 1;
                }
              }
            }
          }
        }
      }
      break;

    case 2: // Animação Aleatória
      int randomLed = random(1, 10);
      int randomColor = random(1, 7);
      int randomTime = random(500);
      posCtrl.setPosicao(randomLed, randomColor, randomTime);
      delay(1000);
      posCtrl.resetAllLeds();
      break;

    default:
      Serial.println("Invalid selection. Please choose 1 or 2.");
      break;
  }
}
