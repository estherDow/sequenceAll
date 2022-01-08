//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(WiFiUDP &udp, AsyncWebServer &server, ESPmDNSInterface &mdns,
                         NVSServiceInterface &nvs) : udp(udp), mdns(mdns), nvs(nvs), server(server) {

//    this->udp = udp;
//    this->mdns = mdns;
//    this->server = server;


}


bool WiFiService::begin() {
    if(!nvs.openNameSpace("credentials")) {
        return false;
    }

    if (!this->_initSTA()) {
        if (!_initAP()) {
            Serial.println("WiFi init failed");
            return false;
        }
    }
    udp.begin(WiFi.localIP(), 8000);
    server = AsyncWebServer(80);

    if (!mdns.begin("sequenceall")) {
        Serial.println("Error, could not set hostname");
        return false;
    }
    if (!mdns.addService("http", "tcp", 80)) {
        return false;
    }
    if (!mdns.addService("osc", "udp", LOCAL_UDP_PORT)) {
        return false;
    }
    hostName = getHostname();
    if (hostName == nullptr) {
        return false;
    }
    remoteIp = mdns.queryHost(hostName, 2000);
    if (!_initWebServer()) {
        return false;
    }
    return true;
}

bool WiFiService::_initAP() {
    WiFi.mode(WIFI_AP);
    size_t length;
    if (!nvs.getStringLength("APssid", &length)) {
        return false;
    }
    char *ssid[length];
    if (!nvs.getString("APssid", *ssid, &length)) {
        return false;
    }
    length = 0;
    if (!nvs.getStringLength("APpassword", &length)) {
        return false;
    }
    char *password[length];
    if (!nvs.getString("APpassword", *password, &length)) {
        return false;
    }
    if (length == 0) {
        if (_doSetAP((char *) "sequenceX", (char *) "transLiberationNow")) {
            return true;
        }
        return false;
    } else {
        if (_doSetAP(*ssid, *password)) {
            return true;
        }
        return false;
    }
}

bool WiFiService::_initSTA() {
    WiFi.mode(WIFI_STA);
    uint8_t numberNetworks = WiFi.scanNetworks();
    size_t length = 0;
    if (!nvs.getStringLength("STAssid", &length)) {
        return false;
    }

    char *ssid[length];
    if (!nvs.getString("STAssid", *ssid, &length)) {
        return false;
    }

    length = 0;
    if (!nvs.getStringLength("STApassword", &length)) {
        return false;
    }

    char *password[length];
    if (!nvs.getString("STApassword", *password, &length)) {
        return false;
    }

    if (length == 0) {
        return false;
    }
    for (uint8_t i = 0; i < numberNetworks; i++) {
        if ((char *) WiFi.SSID(i).c_str() == *ssid) {
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
    return remoteIp;
}


bool WiFiService::_doSetSTA(char *newSSID, char *newPassword) {
    WiFi.begin(newSSID, newPassword);
    while (WiFi.status() != WL_CONNECTED) {}
    Serial.println("connected to wifi...");
    Serial.println(WiFi.localIP());
    return true;
}

bool WiFiService::_doSetAP(char *ssid, char *password) {
    if (WiFi.softAP(ssid, password)) {
        return true;
    }
    return false;
}

void WiFiService::_doHandleWifiMode() {
    bool isSetIp = false;
    nvs.getBool("SetIP", &isSetIp);
    if (isSetIp) {
        remoteIp = getRemoteIP();
        nvs.setBool(
                "SetIP",
                false,
                true
        );
    }
    bool isSetAp = false;
    nvs.getBool("SetAP", &isSetAp);
    if (isSetAp) {
        _initAP();
        nvs.setBool(
                "SetAP",
                false,
                true
        );
    }
    bool isSetSTA = false;
    nvs.getBool("SetSTA", &isSetSTA);
    if (isSetSTA) {
        if (!_initSTA()) {
            _initAP();
        }

        nvs.setBool(
                "SetSTA",
                false,
                true
        );
    }
}

const char *WiFiService::getHostname() {
    size_t length = 0;
    if (!nvs.getStringLength("hostname", &length)) {
        return nullptr;
    }
    if (length == 0) {
        return nullptr;
    }
    char *hostname[length];
    nvs.getString("hostname", *hostname, &length);
    return hostName;
}

WiFiUDP &WiFiService::getUDP() {
    return udp;
}

bool WiFiService::_initWebServer() {


    auto *handleSTARequest = new AsyncCallbackJsonWebHandler(
            "/set_sta",
            [&nvs](AsyncWebServerRequest *request,
                   JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();
                if (!jsonObject.isNull() && jsonObject["ssid"]) {
                    nvs.setString(
                            "STAssid",
                            jsonObject["ssid"],
                            true
                    );
                    nvs.setString(
                            "STApassword",
                            jsonObject["password"],
                            true
                    );
                }

                nvs.setInt(
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
            });
    auto *handleRemoteIPRequest = new AsyncCallbackJsonWebHandler(
            "/set_remote_ip",
            [&nvs](AsyncWebServerRequest *request,
                   JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();

                if (!jsonObject.isNull() && jsonObject["remoteIP"]) {

                    const char *ipFromJson = jsonObject["remoteIP"];
                    IPAddress ip;
                    ip.fromString(reinterpret_cast<const char *>(ipFromJson));
                    nvs.setIPAddress(
                            "remoteIP",
                            ip,
                            true
                    );

                    nvs.setBool(
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

    server.addHandler(handleSTARequest);
    server.addHandler(handleAPRequest);
    server.addHandler(handleRemoteIPRequest);
    server.begin();

    return true;
}

