//
// Created by Kenneth Dow on 8/1/22.
//

#ifndef SEQUENCEALL_ASYNCJSONHANDLER_H
#define SEQUENCEALL_ASYNCJSONHANDLER_H
#include "ESPAsyncWebServer.h"
#include "NVSServiceInterface.h"
class AsyncJsonHandler : public AsyncWebHandler {
    explicit AsyncJsonHandler(const char * restPath,NVSServiceInterface &NVS) : nvs(NVS), uri(restPath){};

    ~AsyncJsonHandler() override = default;

    bool canHandle(AsyncWebServerRequest *request) override {
        return true;
    }

    void handleRequest(AsyncWebServerRequest *request) override;

private:
    NVSServiceInterface &nvs;
    const char * uri;
};

#endif //SEQUENCEALL_ASYNCJSONHANDLER_H