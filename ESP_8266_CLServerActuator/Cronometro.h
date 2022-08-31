#ifndef Cronometro_H
#define Cronometro_H

#include "Arduino.h"
/*
   Classe cronometro para controlar o timer sem congelar o programa o tempo todo.
 **/
class Cronometro
{
  private:
    unsigned long long tempoAnterior;
    unsigned long long tempoDuracao;
  public:
    Cronometro(long duracao);

    Cronometro();

    void Start(long duracaoSeg);

    void StartMillis(long duracaoSegMillis);

    void Reset();

    long getDuration() ;

    bool IsEncerrado();
};

#endif
