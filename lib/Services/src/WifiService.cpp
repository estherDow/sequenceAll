//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(WiFiUDP &udp, AsyncWebServer &server, ESPmDNSInterface &mdns
) : udp(udp), mdns(mdns), server(server) {}


bool WiFiService::begin() {

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
    char ssid[32];
    char pwd[32];
    WiFiCredentials credentials("/set_ap", ssid, pwd);

    if (!NVSService::getCredentials("WifiCredentials", &credentials)) {
        if (_doSetAP((char *) "sequenceX", (char *) "transLiberationNow")) {
            return true;
        }
        return false;
    } else if (_doSetAP(ssid, pwd)) {
        return true;
    }

    return false;
}

bool WiFiService::_initSTA() {
    WiFi.mode(WIFI_STA);
    uint8_t numberNetworks = WiFi.scanNetworks();
    char ssid[32];
    char pwd[32];
    WiFiCredentials credentials("/set_ap", ssid, pwd);

    if (!NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetAP((char *) "sequenceX", (char *) "transLiberationNow")) {
            return true;
        }
        return false;
    } else if (_doSetAP(ssid, pwd)) {
        return true;
    }

    for (uint8_t i = 0; i < numberNetworks; i++) {
        if ((char *) WiFi.SSID(i).c_str() == ssid) {
            _doSetSTA(ssid, pwd);
            return true;
        }
    }

    return false;
}

void WiFiService::handleWifiMode() {

    uint currentstate = millis();
    if (currentstate > oldState + interval) {
        _doHandleWifiMode();
        oldState += interval;
    }
}

IPAddress WiFiService::getRemoteIP() {
    return remoteIp;
}


bool WiFiService::_doSetSTA(const char *newSSID, const char *newPassword) {
    WiFi.begin(newSSID, newPassword);
    while (WiFi.status() != WL_CONNECTED) {}
    Serial.println("connected to wifi...");
    Serial.println(WiFi.localIP());
    return true;
}

bool WiFiService::_doSetAP(const char *ssid, const char *password) {
    if (WiFi.softAP(ssid, password)) {
        return true;
    }
    return false;
}

void WiFiService::_doHandleWifiMode() {
    bool isSetIp = false;

    if (!NVSService::getBool(nvsNameSpace, "SetIP", &isSetIp)) {
        return;
    }

    if (isSetIp) {
        remoteIp = getRemoteIP();
        if (!NVSService::setBool(nvsNameSpace,"SetIP", false)) {
            return;
        }
    }

    bool isSetAp = false;
    if (!NVSService::getBool(nvsNameSpace, "SetAP", &isSetAp)) {
        return;
    }

    if (isSetAp) {
        _initAP();
        if (!NVSService::setBool(nvsNameSpace,"SetAP", false)) {
            return;
        }
    }

    bool isSetSTA = false;
    if (!NVSService::getBool(nvsNameSpace, "SetAP", &isSetSTA)) {
        return;
    }

    if (isSetSTA) {
        _initSTA();
        NVSService::setBool(nvsNameSpace,"SetSTA", false);
    }
}

const char *WiFiService::getHostname() {
    size_t length = 0;
    if (!NVSService::getStringLength(nvsNameSpace,"hostname", &length)) {
        return nullptr;
    }
    if (length == 0) {
        return nullptr;
    }
    char hostname[length];
    if (!NVSService::getString(nvsNameSpace, "hostname", hostname, &length) {
        return nullptr;
    }

    return hostName;
}

WiFiUDP &WiFiService::getUDP() {
    return udp;
}

bool WiFiService::_initWebServer() {
    JsonVariant body;
    RestEndpoint restEndpoint("/set_ap", HTTP_POST, body);

    auto *handleApRequest = new AsyncJsonHandler(restEndpoint);

    handleApRequest->onRequest(NVSService::setCredentials)








    auto *handleAPRequest = new AsyncCallbackJsonWebHandler(
            "/set_ap",
            [](AsyncWebServerRequest *request,
                   JsonVariant &json) {
                const JsonObject &jsonObject = json.as<JsonObject>();


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

