//
// Created by Kenneth Dow on 9/1/22.
//

#ifndef SEQUENCEALL_RESTENDPOINT_H
#define SEQUENCEALL_RESTENDPOINT_H

#include <ESPAsyncWebServer.h>
class NVSServiceInterface;

typedef struct RestEndpoint {
    void *class_context;
    const char *uri;
    WebRequestMethodComposite method;
    void (*callback)(void *class_context, NVSServiceInterface &instance, JsonVariant body);
    NVSServiceInterface &nvsInstance;
    JsonVariant requestBody;
    RestEndpoint(void *classContext, const char *AddressPattern,
                 void (*staticCallback)(void *, NVSServiceInterface &, JsonVariant), WebRequestMethodComposite method,
                 NVSServiceInterface &nvsInstance,
                 JsonVariant body)
            : class_context(classContext), uri(AddressPattern), method(method), callback(staticCallback),
              nvsInstance(nvsInstance), requestBody(body) {}
} RestEndpoint;

class RestEndPointHandler {
    static void doSetAP(){};
    static void doSetSTA(){};
    static void doSetRemoteIP(){};
};

#endif //SEQUENCEALL_RESTENDPOINT_H
