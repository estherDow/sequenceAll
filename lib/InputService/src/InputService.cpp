#include "InputService.h"


InputService::InputService() {
  serverPtr = ServerFactory::make();

  AutoConnect portal(*serverPtr);
  portalPtr = &portal;

  portalPtr->begin();
}

void InputService::handleInputClient() {
  portalPtr->handleClient();
}
