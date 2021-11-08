#ifndef WIRELESSLAN_H
#define WIRELESSLAN_H

#include <WiFi.h>
#include <ServerFactory.h>
#include <AutoConnect.h>


class WirelessLanService {
public:
  WirelessLanService();
  void begin();
  void handleInputClient();
private:
  WebServer *serverPtr;
  AutoConnect *portalPtr;


};

#endif
