//
// Created by Kenneth Dow on 8/1/22.
//

#ifndef SEQUENCEALL_ASYNCJSONHANDLER_H
#define SEQUENCEALL_ASYNCJSONHANDLER_H
#include <cstdint>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "NVSServiceInterface.h"
#include "RestEndpoint.h"

class AsyncJsonHandler : public AsyncWebHandler {
    explicit AsyncJsonHandler(RestEndpoint restEndpoint, NVSServiceInterface &nvs) : nvs(nvs), endpoint(restEndpoint) {};

    ~AsyncJsonHandler() override = default;

    bool canHandle(AsyncWebServerRequest *request) override;
    void handleRequest(AsyncWebServerRequest *request) override;

private:
    NVSServiceInterface &nvs;
    RestEndpoint endpoint;
    uint16_t maxJsonBufferSize = 1024;

};

#endif //SEQUENCEALL_ASYNCJSONHANDLER_H