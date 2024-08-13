#include <Arduino.h>
#include <Bounce2.h>
#include "ligarLed.h"

PosicaoControl posCtrl;

int selectFunction = 0; 
const int buttonPins[9] = { 5, 6, 7, 8, 9, 10, 11, 12, 13 };
Bounce buttons[9];
int player = 1;
int old = 0;
int board[3][3] = { 0 };

void loading() {
  Serial.print("Loading: ");
  for (int i = 0; i < 10; i++) {
    Serial.print("=");
    delay(500);
  }
  Serial.println(" Complete!");
  delay(2000);
}

void resetGame() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = 0;
    }
  }
  player = 1;
  Serial.println("Game has been reset. Player 1's turn.");
}

bool isBoardFull(int board[3][3]) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 9; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttons[i].attach(buttonPins[i]);
    buttons[i].interval(20);
  }

  randomSeed(analogRead(0));

  Serial.println("Enter what you want to do with the display:");
  Serial.println("1 = Tic-Tac-Toe;");
  Serial.println("2 = Random Animation;");
  Serial.println("3 = Test mode.");

  while (selectFunction == 0) {
    if (Serial.available() > 0) {
      int received = Serial.read();
      if (received >= '0' && received <= '9') {
        int parsedValue = received - '0';
        if (parsedValue == 1 || parsedValue == 2 || parsedValue == 3) {
          selectFunction = parsedValue;
          Serial.print("Selected function: ");
          Serial.println(selectFunction);
          switch (selectFunction) {
            case 1:
              Serial.println("Starting Tic-Tac-Toe...");
              loading();
              resetGame();
              break;
            case 2:
              Serial.println("Starting Random Animation...");
              loading();
              break;
            case 3:
              Serial.println("Starting test mode...");
              loading();
              break;
          }
        } else {
          Serial.println("Invalid number. Enter 1, 2, or 3.");
        }
      }
      delay(100);
    }
  }
}

void loop() {
  if (selectFunction == 1) {
    int thereisaWinner = 0;
    old = 0;
    do {
      for (int i = 0; i < 9; i++) {
        buttons[i].update();

        if (buttons[i].fell()) {
          int ledPosition = 9 - i;

          if (board[(ledPosition - 1) / 3][(ledPosition - 1) % 3] == 0) {
            board[(ledPosition - 1) / 3][(ledPosition - 1) % 3] = player;

            int result = posCtrl.setPosicaoTicTacToe(ledPosition, player, 1000);

            if (result == 1) {
              Serial.print("The winner is player ");
              Serial.print(player);
              Serial.println("!");
              thereisaWinner = 1;
              if (player == 1) {
                posCtrl.setPosicao(0, 5, 500);
                posCtrl.setPosicao(0, 7, 500);
                posCtrl.setPosicao(0, 5, 500);
                posCtrl.resetAllLeds();
              } else {
                posCtrl.setPosicao(0, 4, 500);
                posCtrl.setPosicao(0, 7, 500);
                posCtrl.setPosicao(0, 4, 500);
                posCtrl.resetAllLeds();
              }
              delay(2000);
              resetGame();
            } else if (isBoardFull(board)) {
              old = 1;
              Serial.println("got old");
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
    } while (thereisaWinner == 1 || old == 1);
  } else if (selectFunction == 2) {
    int numRandom6 = random(1, 7);
    int numRandom9 = random(1, 10);
    int numRandom500 = random(100, 1001);

    posCtrl.setPosicao(numRandom9, numRandom6, numRandom500);
  } else if (selectFunction == 3) {
    posCtrl.setPosicao(1, 1, 1000);
    posCtrl.setPosicao(2, 2, 1000);
    posCtrl.setPosicao(3, 3, 1000);
    posCtrl.setPosicao(4, 1, 1000);
    posCtrl.setPosicao(5, 2, 1000);
    posCtrl.setPosicao(6, 3, 1000);
    posCtrl.setPosicao(7, 1, 1000);
    posCtrl.setPosicao(8, 2, 1000);
    posCtrl.setPosicao(9, 3, 1000);
    posCtrl.setPosicao(0, 4, 1000);
    posCtrl.setPosicao(0, 5, 1000);
    posCtrl.setPosicao(0, 6, 1000);
    posCtrl.setPosicao(0, 7, 1000);
  }
}
