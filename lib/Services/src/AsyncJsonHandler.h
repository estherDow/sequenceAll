//
// Created by Kenneth Dow on 8/1/22.
//

#ifndef SEQUENCEALL_ASYNCJSONHANDLER_H
#define SEQUENCEALL_ASYNCJSONHANDLER_H
#include "ESPAsyncWebServer.h"
#include "NVSServiceInterface.h"
class AsyncJsonHandler : public AsyncWebHandler {
    explicit AsyncJsonHandler(NVSServiceInterface &NVS) : nvs(NVS){};

    ~AsyncJsonHandler() override = default;

    bool canHandle(AsyncWebServerRequest *request) override;

    void handleRequest(AsyncWebServerRequest *request) override;

private:
    NVSServiceInterface &nvs;

    const char * setAccessPoint = "/set_ap";
    const char * setSTA = "/set_sta";
    const char * setRemoteIP = "set_remote_ip";

    bool _handlePostRequestByUrl(AsyncWebServerRequest *request);
    bool _storeAccessPointCredentials(AsyncWebServerRequest *request);
};

#endif //SEQUENCEALL_ASYNCJSONHANDLER_H