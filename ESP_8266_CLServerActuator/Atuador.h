#ifndef Atuador_H
#define Atuador_H

#include "Cronometro.h"
#include "Arduino.h"
/**
    classe para controlar o acionamento de atuadores.
  **/
class Atuador {

  private:
    int _pinAtuador;
    bool _acionar = false;

    Cronometro _timerDuracao;

  public:
    Atuador(int pinNum) ;

    void init() ;

    void prepararLigar(int duracaoSeg) ;

    void prepararLigarMillis(int duracaoSegMillis);

    void ligar();

    void desligar() ;

    int getPin();
    
    bool IsDesligar() ;
    bool IsLigar() ;

};

#endif
