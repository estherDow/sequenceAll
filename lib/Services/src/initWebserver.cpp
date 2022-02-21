//
// Created by Kenneth Dow on 7/2/22.
//
#include "WiFiService.h"

bool WiFiService::_initWebServer() {

    AsyncCallbackJsonWebHandler *handleAPRequest = _setAPCredentialsEndpoint();

    AsyncCallbackJsonWebHandler *handlePrintDebugRequest = _setPrintDebugEndpoint();

    server->addHandler(handleAPRequest);

    server->addHandler(handlePrintDebugRequest);
    server->begin();

    return true;
}

AsyncCallbackJsonWebHandler *WiFiService::_setAPCredentialsEndpoint() {

    auto *handleAPRequest = new AsyncCallbackJsonWebHandler(
            "/set_ap",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["ssid"]) {
                    JsonVariant apRequestBody;

                    WiFiCredentials apCredentials(
                            "/set_ap",
                            jsonObject["ssid"],
                            jsonObject["password"]
                    );

                    if (!NVSService::setCredentials("Wifi", &apCredentials)) {
                        request->send(
                                500,
                                "application/json",
                                {}
                        );
                    }
                    if (!NVSService::setBool("Wifi", "SetAP", true)) {
                        request->send(
                                500,
                                "application/json",
                                {}
                        );
                    }
                } else {
                    request->send(
                            401,
                            "application/json",
                            {}
                    );
                }
                request->send(
                        200,
                        "application/json",
                        {}
                );
                return true;
            });
    return handleAPRequest;
}

AsyncCallbackJsonWebHandler *WiFiService::_setPrintDebugEndpoint() {

    auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/print_debug",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();
                Serial.print("\n\n\n\n\n\n\n\n\n\n\n");
                Serial.println("endpoint worked");
                request->send(
                        200,
                        "application/json",
                        {}
                );
            });
    return handleSTARequest;
}