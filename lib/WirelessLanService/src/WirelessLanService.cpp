#include "WirelessLanService.h"
#include "ServerFactory.h"

WirelessLanService::WirelessLanService() {
  serverPtr = ServerFactory::make();

  //AutoConnect portal(*serverPtr);
  //portalPtr = &portal;

  //portalPtr->begin();
}

void WirelessLanService::handleInputClient() {
  //portalPtr->handleClient();
  return;
}
