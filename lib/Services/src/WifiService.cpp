//
// Created by Kenneth Dow on 29/11/21.
//
#include "WiFiService.h"

WiFiService::WiFiService(
) {
    //TODO: Move this into constructor of WifiService.
    mdns = new ESPmDNSAdapter();
    udp = new AsyncUDP();
    server = new AsyncWebServer(80);
}


WifiErrorCode WiFiService::begin(const char *ssid, const char *password, WifiMode mode) {
    WifiErrorCode STAError = INIT_STA_ERROR;
    WiFiCredentialsChar defaultCredentials;
    strcpy(defaultCredentials.ssid, ssid);
    strcpy(defaultCredentials.pwd, password);
    if (mode == MODE_STA) {
        STAError = _initSTA(defaultCredentials);
    }
    if (mode == MODE_AP || STAError != INIT_STA_SUCCESS) {
        _initAP(defaultCredentials);
        Serial.println("Mode set to AP or no Wifi Credentials Stored");
    }

    Serial.println(localIp);

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

WifiErrorCode WiFiService::_initSTA(WiFiCredentialsChar &defaultCredentials) {
    WiFiCredentialsChar credentials;
    strcpy(credentials.uri, "/set_sta");
    if (NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetSTA(credentials)) return INIT_STA_SUCCESS;
        Serial.println("sta started with stored credentials");
    }
    else {
        if (_doSetSTA(defaultCredentials)) return INIT_STA_SUCCESS;
        Serial.println("sta started with default credentials");
    }

    return INIT_STA_ERROR;
}

WifiErrorCode WiFiService::_initAP(WiFiCredentialsChar defaultCredentials) {

    WiFiCredentialsChar credentials;
    strcpy(credentials.uri, "/set_ap");
    if (NVSService::getCredentials(nvsNameSpace, &credentials)) {
        if (_doSetAP(credentials)) return INIT_AP_NO_CREDENTIALS_STORED;
    }
    else {
        if (_doSetAP(defaultCredentials)) return INIT_AP_NO_CREDENTIALS_STORED;
    }

    return INIT_AP_ERROR;
}

bool WiFiService::_doSetAP(WiFiCredentialsChar &credentials) {
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(credentials.ssid, credentials.pwd)) {
        localIp = WiFi.softAPIP();
        Serial.println("wifiAP started");
        return true;
    }
    return false;
}

bool WiFiService::_doSetSTA(WiFiCredentialsChar &credentials) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(credentials.ssid, credentials.pwd);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED) {
        unsigned long currentTime = millis();

        if (currentTime > startTime + 6000 ) {
            return false;
        }
    }
    Serial.println("connected to wifi.");
    localIp = WiFi.localIP();
    Serial.println(WiFi.localIP());
    return true;
}

AsyncUDP *WiFiService::getUDP() {
    return udp;
}

