//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(
        WiFiUDP * udp,
        ESPmDNSInterface * mdns,
        NVSServiceInterface * nvs
        ) {
    if (!initSTA()) {
        initAP();
    }
    this->udp = udp;
    this->mdns = mdns;
    this->nvs = nvs;
    udp->begin(LOCAL_UDP_PORT);

    server = new AsyncWebServer(80);

    if (!mdns->begin("sequenceall")) {
        return;
    }
    mdns->addService("http", "tcp", 80);
    mdns->addService("osc", "udp", LOCAL_UDP_PORT );
    hostName = getHostname();
    IPAddress ip(0,0,0,0);
    ip = mdns->queryHost(hostName,2000);
    *Ip = ip;
    auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_sta",
            [&nvs](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();
                if (!jsonObject.isNull() && jsonObject["ssid"]) {
                    nvs->setString(
                            "STAssid",
                            jsonObject["ssid"],
                            true
                            );
                    nvs->setString(
                            "STApassword",
                            jsonObject["password"],
                            true
                            );
                }

                nvs->setInt(
                        "SetSTA",
                        1,
                        true
                        );
                request->send(
                        200,
                        "application/json",
                        {}
                );
            });

    auto *handleAPRequest = new AsyncCallbackJsonWebHandler(
            "/set_ap",
            [&nvs](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["ssid"]) {
                    nvs->setString(
                            "APssid",
                            jsonObject["ssid"],
                            true
                            );
                    nvs->setString(
                            "APpassword",
                            jsonObject["password"],
                            true);
                }

                nvs->setInt(
                        "SetAP",
                        1,
                        true
                        );
                request->send(
                        200,
                        "application/json",
                        {}
                );
            });
    auto *handleRemoteIPRequest = new AsyncCallbackJsonWebHandler(
            "/set_remote_ip",
            [&nvs](AsyncWebServerRequest *request,
               JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["remoteIP"]) {

                    const char * ipFromJson = jsonObject["remoteIP"];
                    IPAddress ip;
                    ip.fromString(reinterpret_cast<const char *>(ipFromJson));
                    nvs->setIPAddress(
                            "remoteIP",
                            ip,
                            true
                            );

                    nvs->setBool(
                            "SetIP",
                            true,
                            true
                            );
                    request->send(
                            200,
                            "application/json",
                            {}
                    );
                }
            });

    server->addHandler(handleSTARequest);
    server->addHandler(handleAPRequest);
    server->addHandler(handleRemoteIPRequest);
    server->begin();

}

void WiFiService::initAP() {
    WiFi.mode(WIFI_AP);
    size_t* length;
    nvs->getStringLength("APssid", length);
    char *ssid[*length];
    nvs->getString("APssid",*ssid, length);
    *length = 0;
    nvs->getStringLength("APpassword", length);
    char * password[*length];
    nvs->getString("APpassword", *password, length);
    if (*length == 0) {
        _doSetAP( DEFAULT_AP_SSID, DEFAULT_AP_PASSWORD);
    }
    else {
        _doSetAP(*ssid, *password);
    }
}

bool WiFiService::initSTA() {
    WiFi.mode(WIFI_STA);
    uint8_t numberNetworks = WiFi.scanNetworks();
    size_t* length;
    if (!nvs->getStringLength("STAssid", length)) {
        return false;
    }

    char * ssid[*length];
    if (!nvs->getString("STAssid", *ssid, length)) {
        return false;
    }

    *length = 0;
    if (!nvs->getStringLength("STApassword", length)) {
        return false;
    }

    char * password[*length];
    if (!nvs->getString("STApassword", *password, length)) {
        return false;
    }

    if (*length == 0) {
        return false;
    }
    for (uint8_t i = 0; i < numberNetworks; i++) {
        if ((char*)WiFi.SSID(i).c_str() == *ssid) {
            _doSetSTA(*ssid, *password);
            return true;
        }
    }
    return false;
}

void WiFiService::handleWifiMode() {

    int currentstate = millis();
    if (currentstate > oldState + interval) {
        _doHandleWifiMode();
        oldState += interval;
    }
}

IPAddress WiFiService::getRemoteIP() {

}


bool WiFiService::_doSetSTA(char * newSSID, char *newPassword) {
    WiFi.begin( newSSID, newPassword);
    while (WiFi.status() != WL_CONNECTED) {}
    Serial.println("connected to wifi...");
    Serial.println(WiFi.localIP());
    return 1;
}

bool WiFiService::_doSetAP(char *ssid, char *password) {
    WiFi.softAP(ssid, password);
    return 1;
}

void WiFiService::_doHandleWifiMode() {
    bool isSetIp = false;
    nvs->getBool("SetIP", &isSetIp);
    if (isSetIp) {
        *Ip = getRemoteIP();
        nvs->setInt(
                "SetIP",
                0,
                true
                );
    }
    bool isSetAp = false;
    nvs->getBool("SetAP", &isSetAp);
    if (isSetAp) {
        initAP();
        nvs->setInt(
                "SetAP",
                0,
                true
                );
    }
    bool isSetSTA = false;
    nvs->getBool("SetSTA", &isSetSTA);
    if (isSetSTA) {
        if (!initSTA()) {
            initAP();
        }

        nvs->setInt(
                "SetSTA",
                0,
                true
                );
    }
}

const char *WiFiService::getHostname() {
    size_t * length;
    if (!nvs->getStringLength("hostname", length)) {
        return nullptr;
    }
    if (length == 0) {
        return nullptr;
    }
    char * hostname[*length];
    nvs->getString("hostname", *hostname, length);
    return hostName;
}
