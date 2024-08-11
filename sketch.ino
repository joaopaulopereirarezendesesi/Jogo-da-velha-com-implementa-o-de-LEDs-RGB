#include "ligarLed.h"

PosicaoControl posCtrl;

/*
  posCtrl.setPosicao(Number of LED you want to light up, color you want);

  colors:
  1 = Red;
  2 = Blue;
  3 = Pink;
  4 = All leds blues;
  5 = All leds reds;
  6 = All leds pinks;
  7 = not one led.

  LED numbering:
  Led 1, Led 2, Led 3
  Led 4, Led 5, Led 6
  Led 7, Led 8, Led 9.
*/

int selectFunction = 0;
int jogador = 2;

void loading(){
   Serial.print("Carregando: ");
  
  for (int i = 0; i <= 10; i++) {
    Serial.print("=");
    delay(500); 
  }
  
  Serial.println(" Completo!");
  delay(2000); 
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  Serial.println("Digite o que você quer fazer com o display:");
  Serial.println("1 = Jogo da Velha;");
  Serial.println("2 = Animação Random."); 

  while (selectFunction == 0) {
    if (Serial.available() > 0) {
      selectFunction = Serial.parseInt();
      switch (selectFunction) {
        case 1:
          Serial.println("Iniciando o Jogo da Velha...");
          loading();
          break;
        case 2:
          Serial.println("Iniciando Animação Random...");
          loading();
          break;
        default:
          Serial.println("Número inválido. Digite 1 ou 2.");
          selectFunction = 0;
          break;
      }
      delay(1000);
    }
  }
}

void loop() {
  if (selectFunction == 1) {
  } else if (selectFunction == 2) {
    int numrandom6 = random(6);
    int numrandom9 = random(9);
    int numrandom500 = random(500);
    posCtrl.setPosicao(numrandom9, numrandom6, numrandom500);
  }
}
