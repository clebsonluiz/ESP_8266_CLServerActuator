#include "CLServerActuator.h"


void CLServerActuator::init(char const *code_key, char const *server_host) {
  _server_host = server_host;
  _project_code_key = code_key;
}


void CLServerActuator::checkAtuador(Atuador* actuator, int cardId) {

  String request = String(_server_host) + "/code_key/" + _project_code_key + "/card_id/" + String(cardId);

  WiFiClient client;
  HTTPClient http;

  http.begin(client, request); //Only accept HTTP, Not HTTPS

  http.addHeader("Content-Type", "application/json"); //Request Headers

  int httpCode = http.GET();

  // If not negative then as made request
  if (httpCode > 0) {

    // if 200 then the response has a payload to read
    if (httpCode == HTTP_CODE_OK) {

      const String payload = http.getString();

      StaticJsonDocument<512> json; // ArduinoJson Library

      deserializeJson(json, payload);

      String key = json["key"];
      //      String codeKey = json["code_key"];
      String type = json["type"];
      //      int cardId = json["card_id"].as<int>();

      //      long startDatetimeMillis = json["start_datetime_millis"].as<long>();
      //      long endDatetimeMillis = json["end_datetime_millis"].as<long>();
      boolean valueStatus = json["value_status"].as<boolean>();

      if (type.indexOf("on_off") >= 0)
      {
        //                Serial.print("Atuador: Card_id: ");
        //                Serial.print(cardId);
        //                Serial.print(" , Porta: ");
        //                Serial.print(actuator->getPin());
        //                Serial.print(" , Value: ");
        //                Serial.print(valueStatus);
        //                Serial.println();

        if (valueStatus == true)
        {
          actuator->ligar();
        }
        else {
          actuator->desligar();
        }
      }
      else if (type.indexOf("timer") >= 0)
      {
        //                Serial.print("Atuador: Card_id: ");
        //                Serial.print(cardId);
        //                Serial.print(" , Porta: ");
        //                Serial.print(actuator->getPin());
        //                Serial.print(" , Value: ");
        //                Serial.print(valueStatus);
        //                Serial.println();

        if (actuator->IsDesligar()) // Se for pra desligar tem que enviar um request
        {
          String new_request = String(_server_host) + "/key/" + key;
          String response;
          response.reserve(512);

          json["value_status"] = false;

          serializeJson(json, response);

          WiFiClient client2;
          HTTPClient http2;

          http2.begin(client2, new_request); //Only HTTP, Not HTTPS

          //Request Headers
          http2.addHeader("Content-Type", "application/json");

          // Send Post Request and receive Response http code
          int httpCode2 = http2.PUT(response);

          if (httpCode2 > 0) {
            actuator->desligar();
          }

          http2.end();
        }
        else if (actuator->IsLigar() && !actuator->IsDesligar())
        {

          if (valueStatus != NULL)
          {
            if (valueStatus)
            {
              unsigned long long startDatetimeMillis = json["start_datetime_millis"].as<unsigned long long>(); // Value 0 if dont use unsigned long long
              unsigned long long endDatetimeMillis = json["end_datetime_millis"].as<unsigned long long>(); // Value 0 if dont use unsigned long long

              long timerDuration = endDatetimeMillis - startDatetimeMillis; // Timer duration in milliseconds

              //                            Serial.println();
              //                            Serial.println(startDatetimeMillis);
              //                            Serial.println(endDatetimeMillis);
              //                            Serial.println(timerDuration);
              //                            Serial.println();

              actuator->prepararLigarMillis(timerDuration);

              actuator->ligar();
            }
            else {
              actuator->desligar();
            }
          }
        }
      }
    }
    else {
      //      ESP.restart();
    }
  } else {
    delay(100);
  }
  http.end(); // Aw
}
