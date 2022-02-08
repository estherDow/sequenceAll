#include <utility>

//
// Created by Kenneth Dow on 16/1/22.
//

#ifndef SEQUENCEALL_WIFICREDENTIALS_H
#define SEQUENCEALL_WIFICREDENTIALS_H

typedef struct WiFiCredentials {
    std::string uri;
    std::string ssid;
    std::string pwd;

    WiFiCredentials(std::string uri,
                    std::string ssid,
                    std::string pwd)
            : uri(std::move(uri)), ssid(std::move(ssid)), pwd(std::move(pwd)) {}

    WiFiCredentials() = default;
} WiFiCredentials;

typedef struct WiFiCredentialsChar {
    char uri[32];
    char ssid[32];
    char pwd[32];

    WiFiCredentialsChar(const char *Uri,
                    const char *Ssid,
                    const char *Pwd) {
        strcpy(uri, Uri);
        strcpy(ssid, Ssid);
        strcpy(pwd, Pwd);
    }

    WiFiCredentialsChar() = default;
} WiFiCredentialsChar;


#endif //SEQUENCEALL_WIFICREDENTIALS_H
