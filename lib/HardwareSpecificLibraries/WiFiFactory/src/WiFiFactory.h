#ifndef WIFIFACTORY_H
#define WIFIFACTORY_H
#include "IWiFi.h"
class WiFiFactory {
  IWiFi make(WiFiHardWare hwType);
};
#endif
