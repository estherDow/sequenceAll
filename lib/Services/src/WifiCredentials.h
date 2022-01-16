//
// Created by Kenneth Dow on 16/1/22.
//

#ifndef SEQUENCEALL_WIFICREDENTIALS_H
#define SEQUENCEALL_WIFICREDENTIALS_H
typedef struct WiFiCredentials {
    const char *uri;
    const char *ssid;
    const char *pwd;

    WiFiCredentials(const char *uri,
                    const char *ssid,
                    const char *pwd)
            : uri(uri), ssid(ssid), pwd(pwd) {}
} WiFiCredentials;
#endif //SEQUENCEALL_WIFICREDENTIALS_H
