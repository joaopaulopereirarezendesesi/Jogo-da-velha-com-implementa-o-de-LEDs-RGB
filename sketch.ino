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
  Serial.println("Player 1's turn.");
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

  while (selectFunction == 0) {
    if (Serial.available() > 0) {
      char received = Serial.read();
      if (received >= '1' && received <= '2') {
        selectFunction = received - '0';
        loading();
        Serial.print("Selected function: ");
        Serial.println(selectFunction);
      } else {
        Serial.println("Invalid number. Enter 1, 2, or 3.");
      }
      delay(100);
    }
  }
}

void loop() {
  if (selectFunction == 0) {
    return;
  }

  if (Serial.available() > 0) {
    char newSelection = Serial.read();
    if (newSelection >= '1' && newSelection <= '2') {
      selectFunction = newSelection - '0';
      loading();
      Serial.print("Function changed to: ");
      Serial.println(selectFunction);
    } 
    delay(100);
  }

  switch (selectFunction) {
    case 1:
      {
        int thereisaWinner = 0;
        old = 0;
        while (thereisaWinner == 0 && old == 0) {
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
    case 2:
      int randomLed = random(1, 9);
      int randomColor = random(1, 7);
      int randomTime = random(500, 1001);
      posCtrl.setPosicao(randomLed, randomColor, randomTime);
      delay(1000);
      posCtrl.resetAllLeds();
      break;
    default:
      Serial.println("Invalid selection. Please choose 1, 2, or 3.");
      break;
  }
}
