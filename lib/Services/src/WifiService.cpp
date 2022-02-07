//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(WiFiUDP *udp, AsyncWebServer *server, ESPmDNSInterface *mdns
) : udp(udp), mdns(mdns), server(server) {}


WifiErrorCode WiFiService::begin() {
    WifiErrorCode STAError;

    STAError = _initSTA();
    if (STAError != INIT_STA_SUCESS) {
        if (STAError == INIT_STA_NO_CREDENTIALS_STORED) {
            //TODO: create a Object in Heap Memory to store stuff for frontend.
            Serial.println("no Wifi Credentials Stored, ");
        }
    }
    Serial.println(localIp);
    udp->begin(localIp, 8000);
    if (!_initWebServer()) {
        return INIT_WEBSERVER_ERROR;
    }

    if (!mdns->begin("sequenceall")) {
        Serial.println("Error, could not set hostname");
        return COULD_NOT_SET_LOCAL_HOSTNAME;
    }
    if (!mdns->addService("http", "tcp", 80)) {
        Serial.println("Error, could not set mdns tcp");
        return MDNS_COULD_NOT_ADD_SERVICE;
    }
    if (!mdns->addService("osc", "udp", LOCAL_UDP_PORT)) {
        Serial.println("Error, could not set mdns udp");
        return MDNS_COULD_NOT_ADD_SERVICE;
    }

    WifiErrorCode RemoteHostError = getRemoteHostInfo();
    if (RemoteHostError == COULD_NOT_QUERY_REMOTE_IP || RemoteHostError == NO_REMOTE_HOSTNAME) {
        Serial.println("Error, could not find information about remote host.");
        return RemoteHostError;
    }
    return INIT_WIFI_SERVICE_SUCCESS;
}

WifiErrorCode WiFiService::_initAP() {
    char uri[8] = "/set_ap";
    char ssid[32];
    char pwd[32];
    WiFiCredentials credentials(uri, ssid, pwd);

    if (!NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetAP((char *) "sequenceX", (char *) "transLiberationNow")) {
            return INIT_AP_NO_CREDENTIALS_STORED;
        }
        return INIT_AP_ERROR;
    } else if (_doSetAP(ssid, pwd)) {
        return INIT_AP_SUCCESS;
    }

    return INIT_AP_ERROR;
}

WifiErrorCode WiFiService::_initSTA() {
    uint8_t numberNetworks = WiFi.scanNetworks();
    char uri[9] = "/set_sta";
    char ssid[32];
    char pwd[32];
    WiFiCredentials credentials(uri, ssid, pwd);

    if (!NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetAP((char *) "sequenceX", (char *) "transLiberationNow")) {
            return INIT_STA_NO_CREDENTIALS_STORED;
        }
        Serial.println("unable to initiate wifi sta or ap - dying :/");
        return INIT_WIFI_GENERIC_ERROR;
    }

    for (uint8_t i = 0; i < numberNetworks; i++) {
        if ((char *) WiFi.SSID(i).c_str() == ssid) {
            _doSetSTA(ssid, pwd);
            return INIT_STA_SUCESS;
        }
    }
    return INIT_WIFI_GENERIC_ERROR;
}

void WiFiService::handleWifiMode() {

    uint currentstate = millis();
    if (currentstate > oldState + interval) {
        _doHandleWifiMode();
        oldState += interval;
    }
}

bool WiFiService::getRemoteIP(IPAddress ip) {
    if (remoteIp[0] == 0) {
        return false;
    }
    ip = remoteIp;
    return true;
}


bool WiFiService::_doSetSTA(const char *newSSID, const char *newPassword) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(newSSID, newPassword);
    while (WiFi.status() != WL_CONNECTED) {}
    Serial.println("connected to wifi...");
    localIp = WiFi.localIP();
    Serial.println(WiFi.localIP());
    return true;
}

bool WiFiService::_doSetAP(const char *ssid, const char *password) {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(ssid, password)) {
        localIp = WiFi.softAPIP();
        return true;
    }
    return false;
}

void WiFiService::_doHandleWifiMode() {

    bool isSetAp = false;
    if (!NVSService::getBool(nvsNameSpace, "SetAP", &isSetAp)) {
        Serial.println("unable to get setAP Flag from NVS");
    }

    if (isSetAp) {
        _initAP();
        if (!NVSService::setBool(nvsNameSpace,"SetAP", false)) {
            Serial.println("unable to set setAP Flag in NVS");
        }
    }

    bool isSetSTA = false;
    if (!NVSService::getBool(nvsNameSpace, "SetSTA", &isSetSTA)) {
        Serial.println("unable to get setSTA Flag from NVS");
    }

    if (isSetSTA) {
        _initSTA();
        NVSService::setBool(nvsNameSpace,"SetSTA", false);
    }
}

bool WiFiService::getRemoteHostname() {
    size_t length = 0;

    if (!NVSService::getString(nvsNameSpace, "hostname", remoteHostName, &length)) {
        return false;
    }

    return true;
}

WiFiUDP* WiFiService::getUDP() {
    return udp;
}



WifiErrorCode WiFiService::getRemoteHostInfo() {

    if (!getRemoteHostname()) {
        Serial.println("Error, could not get hostname");
        return NO_REMOTE_HOSTNAME;
    }
    remoteIp = mdns->queryHost(remoteHostName, 2000);
    if (remoteIp[0] == 0) {
        return COULD_NOT_QUERY_REMOTE_IP;
    }
    return REMOTE_HOST_QUERY_SUCCESSFUL;
}

