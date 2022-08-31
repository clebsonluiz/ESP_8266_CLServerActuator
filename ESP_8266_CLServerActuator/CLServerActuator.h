#ifndef CLServerActuator_H
#define CLServerActuator_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


#include "Arduino.h"
#include "Atuador.h"
#include "ArduinoJson.h"
/*
   Classe para controlar as requisições de atuadores no projeto.
 **/
class CLServerActuator
{
  private:
    char const *_server_host;
    char const *_project_code_key;
  public:

    void init(char const *code_key, char const *server_host);

    void checkAtuador(Atuador* actuator, int cardId);
};

#endif
