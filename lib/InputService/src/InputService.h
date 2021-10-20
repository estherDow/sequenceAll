#ifndef INPUTSERVICE_H
#define INPUTSERVICE_H

#include <WiFi.h>
#include <ServerFactory.h>
#include <AutoConnect.h>


class InputService {
public:
  InputService();
  void handleInputClient();
private:
  WebServer *serverPtr;
  AutoConnect *portalPtr;


};

#endif
