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
typedef std::function<bool(const char * nameSpace, RestEndpoint *dataFromRequest)> JsonRequestHandlerFunction;

class AsyncJsonHandler : public AsyncWebHandler {
public:
    explicit AsyncJsonHandler(RestEndpoint restEndpoint, JsonRequestHandlerFunction &onRequest)
            : endpoint(restEndpoint), _onRequest(onRequest) {};

    ~AsyncJsonHandler() override = default;

 //   bool canHandle(AsyncWebServerRequest *request) override;
 //   void onRequest(const JsonRequestHandlerFunction& fn){ _onRequest = fn; }
 //   void handleRequest(AsyncWebServerRequest *request) override;

private:
    RestEndpoint endpoint;
    JsonRequestHandlerFunction& _onRequest;
    uint16_t maxJsonBufferSize = 1024;
    const char * nvsNameSpace = "Wifi";

};

#endif //SEQUENCEALL_ASYNCJSONHANDLER_H