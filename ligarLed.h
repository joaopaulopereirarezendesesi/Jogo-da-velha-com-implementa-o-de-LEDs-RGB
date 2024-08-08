#ifndef LIGARLED_H
#define LIGARLED_H

class PosicaoControl {
private:
  int _dlay;
  int _numposicao;
  int _cor;

public:
  void setPosicao(int num, int color, int lay);
};

#endif
