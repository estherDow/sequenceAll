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
    WiFiCredentials()= default;
} WiFiCredentials;



#endif //SEQUENCEALL_WIFICREDENTIALS_H
