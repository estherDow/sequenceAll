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

                    nvs->setInt(
                            "SetIP",
                            1,
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
    int length;
    nvs->getStringLength("APssid", length);
    const char *ssid;
    nvs->getString("APssid",&ssid);
    nvs->getStringLength("APpassword", length);
    const char * password;
    nvs->getString("APpassword", &password);
    if (strlen(ssid) == 0) {
        _doSetAP( DEFAULT_AP_SSID, DEFAULT_AP_PASSWORD);
    }
    else {
        _doSetAP(ssid, password);
    }
}

bool WiFiService::initSTA() {
    WiFi.mode(WIFI_STA);
    uint8_t numberNetworks = WiFi.scanNetworks();
    int length = 0;
    if (!nvs->getStringLength("STAssid", length)) {
        return false;
    }

    const char * ssid;
    if (!nvs->getString("STAssid", &ssid)) {
        return false;
    }

    length = 0;
    if (!nvs->getStringLength("STApassword", length)) {
        return false;
    }

    const char * password;
    if (!nvs->getString("STApassword", &password)) {
        return false;
    }

    if (strlen(ssid) == 0) {
        return false;
    }
    for (uint8_t i = 0; i < numberNetworks; i++) {
        if (WiFi.SSID(i) == ssid) {
            _doSetSTA(ssid, password);
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


bool WiFiService::_doSetSTA(const char * newSSID, const char *newPassword) {
    WiFi.begin( newSSID, newPassword);
    while (WiFi.status() != WL_CONNECTED) {}
    Serial.println("connected to wifi...");
    Serial.println(WiFi.localIP());
    return 1;
}

bool WiFiService::_doSetAP(const char *ssid, const char *password) {
    WiFi.softAP(ssid, password);
    return 1;
}

void WiFiService::_doHandleWifiMode() {
    int isSetIp = 0;
    nvs->getInt("SetIP", isSetIp);
    if (isSetIp != 0) {
        *Ip = getRemoteIP();
        nvs->setInt(
                "SetIP",
                0,
                true
                );
    }
    int isSetAp = 0;
    nvs->getInt("SetAP", isSetAp);
    if (isSetAp != 0) {
        initAP();
        nvs->setInt(
                "SetAP",
                0,
                true
                );
    }
    int isSetSTA = 0;
    nvs->getInt("SetSTA", isSetSTA);
    if (isSetSTA != 0) {
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
    int length;
    if (!nvs->getStringLength("hostname", length)) {
        return nullptr;
    }
    if (length == 0) {
        return nullptr;
    }
    const char * hostname[length];
    nvs->getString("hostname", hostname);
    return hostName;
}
