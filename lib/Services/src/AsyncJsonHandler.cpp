//
// Created by Kenneth Dow on 8/1/22.
//

#include "AsyncJsonHandler.h"


void AsyncJsonHandler::handleRequest(AsyncWebServerRequest *request) {
    if (request->method() == HTTP_POST) {
        _handlePostRequestByUrl();
    }
    if(request->url() == setAccessPoint) {

    }
}

bool AsyncJsonHandler::_handlePostRequestByUrl(AsyncWebServerRequest *request) {
    if(request->url().c_str() == setAccessPoint) {
        if(!_storeAccessPointCredentials(request)) {
            return false;
        }

    }
    return true;
}

bool AsyncJsonHandler::_storeAccessPointCredentials(AsyncWebServerRequest *request) {
    const JsonObject &jsonObject = json.as<JsonObject>();

    if (!jsonObject.isNull() && jsonObject["ssid"]) {
        nvs.setString(
                "APssid",
                jsonObject["ssid"],
                true
        );
        nvs.setString(
                "APpassword",
                jsonObject["password"],
                true);
    }

    nvs.setInt(
            "SetAP",
            1,
            true
    );

    request->send(
            200,
            "application/json",
            {}
    );
    return true;
}

bool AsyncJsonHandler::canHandle(AsyncWebServerRequest *request) {
    virtual bool canHandle(AsyncWebServerRequest *request) override final{

//            if(!(_method & request->method()))
//            return false;
//
//            if(_uri.length() && (_uri != request->url() && !request->url().startsWith(_uri+"/")))
//            return false;

            if ( !request->contentType().equalsIgnoreCase(JSON_MIMETYPE) )
            return false;

            request->addInterestingHeader("ANY");
            return true;
    }
}
//TODO: static call with object reference to align better with current approach in sequence all, as well as esp async webserver.
void AsyncJsonHandler::onRequest() {

}


