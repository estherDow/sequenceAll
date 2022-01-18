//
// Created by Kenneth Dow on 8/1/22.
//

#include "AsyncJsonHandler.h"

/*

void AsyncJsonHandler::handleRequest(AsyncWebServerRequest *request) {

    DynamicJsonDocument jsonBuffer(maxJsonBufferSize);
    DeserializationError error = deserializeJson(jsonBuffer, (uint8_t *) (request->_tempObject));
    if (!error) {
        endpoint.requestBody = jsonBuffer.as<JsonVariant>();
        _onRequest(nvsNameSpace, &endpoint);
    }
}

bool AsyncJsonHandler::canHandle(AsyncWebServerRequest *request) {

    if (!(endpoint.method & request->method())) {
        return false;
    }

    size_t uriLength = strlen(endpoint.uri);
    std::string endPointUri str(endpoint.uri) ;
    endPointUri += "/";
    if (uriLength &&
        !(endpoint.uri = request->url() && request->url().startsWith(endPointUri))
            ) {
        return false;
    }


    if (!request->contentType().equalsIgnoreCase(JSON_MIMETYPE))
        return false;

    request->addInterestingHeader("ANY");
    return true;

}

*/
