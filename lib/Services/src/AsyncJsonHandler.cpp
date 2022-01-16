//
// Created by Kenneth Dow on 8/1/22.
//

#include "AsyncJsonHandler.h"


void AsyncJsonHandler::handleRequest(AsyncWebServerRequest *request) {

        DynamicJsonDocument jsonBuffer(maxJsonBufferSize);
        DeserializationError error = deserializeJson(jsonBuffer, (uint8_t *) (request->_tempObject));
        if (!error) {
            endpoint.requestBody = jsonBuffer.as<JsonVariant>();
            endpoint.callback(endpoint.class_context, nvs, json);
        }


}

bool AsyncJsonHandler::canHandle(AsyncWebServerRequest *request) {

    if (!(endpoint.method & request->method())) {
        return false;
    }


    if (endpoint.uri.length() &&
        !(endpoint.uri = request->url() && request->url().startsWith(endpoint.uri + "/"))
        ){
        return false;
    }


    if ( !request->contentType().equalsIgnoreCase(JSON_MIMETYPE) )
        return false;

    request->addInterestingHeader("ANY");
    return true;

}


