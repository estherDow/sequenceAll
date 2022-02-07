//
// Created by Kenneth Dow on 7/2/22.
//
#include "WiFiService.h"

bool WiFiService::_initWebServer() {

    AsyncCallbackJsonWebHandler *handleAPRequest = _setAPCredentialsEndpoint();
    AsyncCallbackJsonWebHandler *handleSTARequest = _setSTACredentialsEndpoint();
    AsyncCallbackJsonWebHandler *handleRemoteHostRequest = _setRemoteHostNameEndpoint();
    AsyncCallbackJsonWebHandler *handlePrintDebugRequest = _setPrintDebugEndpoint();

    server->addHandler(handleAPRequest);
    server->addHandler(handleSTARequest);
    server->addHandler(handleRemoteHostRequest);
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

AsyncCallbackJsonWebHandler *WiFiService::_setSTACredentialsEndpoint() {

    auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_sta",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["ssid"]) {

                    WiFiCredentials STACredentials(
                            "/set_sta",
                            jsonObject["ssid"],
                            jsonObject["password"]
                    );
                    if (!NVSService::setCredentials("Wifi", &STACredentials)) {
                        request->send(
                                500,
                                "application/json",
                                {}
                        );
                    }
                    if (!NVSService::setBool("Wifi", "SetSTA", true)) {
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
    return handleSTARequest;
}


AsyncCallbackJsonWebHandler *WiFiService::_setRemoteHostNameEndpoint() {

    auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_remote_hostname",
            [](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["hostname"]) {

                    if (!NVSService::setString("Wifi", "hostname", jsonObject["hostname"])) {
                        request->send(
                                500,
                                "application/json",
                                {}
                        );
                    }
                }
                request->send(
                        200,
                        "application/json",
                        {}
                );
            });
    return handleSTARequest;
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