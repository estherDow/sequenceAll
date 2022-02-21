//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(WiFiUDP *udp, AsyncWebServer *server, ESPmDNSInterface *mdns
) : udp(udp), mdns(mdns), server(server) {}


WifiErrorCode WiFiService::begin() {
    WifiErrorCode APError;

    APError = _initAP();
    if (APError != INIT_AP_SUCCESS) {
        if (APError == INIT_AP_NO_CREDENTIALS_STORED) {
            Serial.println("no Wifi Credentials Stored, ");
        }
    }
    Serial.println(localIp);
    udp->begin( 8000);
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

    return INIT_WIFI_SERVICE_SUCCESS;
}

WifiErrorCode WiFiService::_initAP() {

    WiFiCredentialsChar credentials;
    strcpy(credentials.uri, "/set_ap");
    if (!NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetAP("sequenceX", "transLiberationNow")) {
            return INIT_AP_NO_CREDENTIALS_STORED;
        }
        return INIT_AP_ERROR;
    }

    if (_doSetAP(credentials.ssid, credentials.pwd)) {
        Serial.println("ap started with stored credentials");
        return INIT_AP_SUCCESS;
    }

    return INIT_AP_ERROR;
}

bool WiFiService::_doSetAP(const char *ssid, const char *password) {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(ssid, password)) {
        localIp = WiFi.softAPIP();
        Serial.println("wifiAP started");
        return true;
    }
    return false;
}

WiFiUDP *WiFiService::getUDP() {
    return udp;
}

