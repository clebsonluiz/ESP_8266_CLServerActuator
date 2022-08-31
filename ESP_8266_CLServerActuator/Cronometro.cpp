#include "Cronometro.h"

/*
   Classe cronometro para controlar o timer sem congelar o programa o tempo todo.
 **/

Cronometro::Cronometro(long duracao) { // Construtor
  tempoAnterior = 0;
  Start(duracao);
}

Cronometro::Cronometro() { // Construtor
  tempoAnterior = 0;
  Cronometro(0);
}

void Cronometro::Start(long duracaoSeg) {
  /**
     Define o tempo de duracao do cronometro.
   **/
  tempoDuracao = duracaoSeg * 1000;
}

void Cronometro::StartMillis(long duracaoSegMillis) {
  /**
     Define o tempo de duracao do cronometro.
   **/
  tempoDuracao = duracaoSegMillis;
}

void Cronometro::Reset() {
  /**
     reseta o tempo anterior para iniciar uma nova contagem.
   **/
  tempoAnterior = millis();
}

long Cronometro::getDuration() {
  /**
     @return tempo de duracao do cronometro em millisegundos
   **/
  return tempoDuracao;
}

bool Cronometro::IsEncerrado() {
  /**
     Verifica se o tempo definido foi encerrado
   **/
  unsigned long currentTime = millis();
  if (tempoAnterior <= 0) tempoAnterior = currentTime;
  return ((currentTime - tempoAnterior) > tempoDuracao);
}
