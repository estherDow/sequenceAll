//
// Created by Kenneth Dow on 9/1/22.
//

#ifndef SEQUENCEALL_RESTENDPOINT_H
#define SEQUENCEALL_RESTENDPOINT_H

#include <ESPAsyncWebServer.h>

typedef struct RestEndpoint {
    const char *uri;
    WebRequestMethodComposite method;
    JsonVariant requestBody;

    RestEndpoint(const char *uri,
                 WebRequestMethodComposite method,
                 JsonVariant body)
            : uri(uri), method(method),requestBody(body) {}
} RestEndpoint;


#endif //SEQUENCEALL_RESTENDPOINT_H
