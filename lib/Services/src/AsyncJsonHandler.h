//
// Created by Kenneth Dow on 8/1/22.
//

#ifndef SEQUENCEALL_ASYNCJSONHANDLER_H
#define SEQUENCEALL_ASYNCJSONHANDLER_H
#include <cstdint>
#include <utility>
#include "ESPAsyncWebServer.h"
#include "ArduinoJson.h"
#include "NVSServiceInterface.h"
#include "RestEndpoint.h"

class AsyncJsonHandler : public AsyncWebHandler {
public:
    explicit AsyncJsonHandler(RestEndpoint restEndpoint) :  endpoint(restEndpoint) {};

    ~AsyncJsonHandler() override = default;

    bool canHandle(AsyncWebServerRequest *request) override;
    void onRequest(ArJsonRequestHandlerFunction fn){ _onRequest = std::move(fn); }
    void handleRequest(AsyncWebServerRequest *request) override;

private:
    RestEndpoint endpoint;
    ArJsonRequestHandlerFunction _onRequest;
    uint16_t maxJsonBufferSize = 1024;

};

#endif //SEQUENCEALL_ASYNCJSONHANDLER_H