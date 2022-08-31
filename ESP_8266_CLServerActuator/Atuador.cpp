#include "Atuador.h"

/**
    classe para controlar o acionamento do atuador.
  **/
Atuador::Atuador(int pinNum) { //Construtor
  _pinAtuador = pinNum;
}

void Atuador::init() {
  /**
     inicia o pino do atuador
   **/
  pinMode(_pinAtuador, OUTPUT);
}


void Atuador::prepararLigar(int duracaoSeg) {
  /**
     Prepara para ligar o atuador definidno a duracao e quanto
     tempo deve esperar para ligar novamente desde a ultima vez
   **/
  _acionar = true;
  _timerDuracao.Start(duracaoSeg);
}

void Atuador::prepararLigarMillis(int duracaoSegMillis) {
  /**
     Prepara para ligar o atuador definidno a duracao e quanto
     tempo deve esperar para ligar novamente desde a ultima vez
   **/
  _acionar = true;
  _timerDuracao.StartMillis(duracaoSegMillis);
}

void Atuador::ligar() {
  /**
     Aciona o  o atuador e reseta o tempo de duracao
     para iniciar a contagem a partir da contagem atual. a proxima
     ação é definida como a de terminar/desligar o atuador.
   **/
  digitalWrite(_pinAtuador, HIGH);
  _timerDuracao.Reset();
}

void Atuador::desligar() {
  /**
     Desliga  o atuador e reseta o tempo de espera para ligar novamente,
     a proxima ação é definida como a de esperar ficar pronto novamente.
   **/
  digitalWrite(_pinAtuador, LOW);
  _acionar = false;
}

int Atuador::getPin(){
  return _pinAtuador;
}

bool Atuador::IsDesligar() {
  // Verifica a necessidade de desligar  o atuador.
  return ((_timerDuracao.IsEncerrado()) && _acionar);
}

bool Atuador::IsLigar() {
  // Verifica a necessidade de ligar  o atuador.
  return (!_acionar);
}
