//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_NVSSERVICE_H
#define SEQUENCEALL_NVSSERVICE_H
#include <vector>
#include <cstdint>
#include <cstring>
#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "ArduinoJson.h"
#include "IPAddress.h"
#include "RestEndpoint.h"
#include "WifiCredentials.h"
//TODO: Check how to mock static methods in GMock
class NVSService {
public:
    ~NVSService() = default;

    static bool openNameSpace(const char *nameSpace, nvs_handle *nvsHandle);

    static void closeNameSpace(const nvs_handle *nvsHandle);

    static bool deleteAllKeysInPartition(const char *NameSpace, bool forceCommit = true);

    static bool eraseByKey(const char* NameSpace, const char * key, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, int8_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, uint8_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, int16_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, uint16_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, int32_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, uint32_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, int64_t value, bool forceCommit = true);

    static bool setInt(const char* NameSpace, const char * key, uint64_t value, bool forceCommit = true);

    static bool setString(const char* NameSpace, const char * key, const char* value, bool forceCommit = true);

    static bool setBool(const char* NameSpace, const char * key, bool  value, bool forceCommit = true);

    static bool setIPAddress(const char* NameSpace, const char * key, IPAddress &value, bool forceCommit = true);

    static bool setCredentials(const char* NameSpace, WiFiCredentials *dataFromRequest, bool forceCommit = true);

    // bool setVoicePatternData(const char * key, VoicePatternData &value, bool forceCommit = true);

    static bool setBlob(const char* NameSpace, const char * key, uint8_t *blob, size_t length, bool forceCommit = true);

    static bool setBlob(const char* NameSpace, const char * key, std::vector <uint8_t> *blob, bool forceCommit = true);

    static bool getInt(const char* NameSpace, const char * key, int64_t *out_value);

    static bool getStringLength(const char* NameSpace, const char * key, size_t *length);

    static bool getString(const char* NameSpace, const char * key, char* out_value, size_t *length);

    static bool getBool(const char* NameSpace, const char *key, bool *value);

    static bool getIPAddress(const char* NameSpace, const char * key, IPAddress &value_out);

    static bool getCredentials(const char* NameSpace, WiFiCredentials *credentials, bool forceCommit = true);

    static bool getBlobSize(const char* NameSpace, const char * key, size_t *size);

    static bool getBlob(const char* NameSpace, const char * key, uint8_t *blob, size_t *length);

    static bool getBlob(const char* NameSpace, const char * key, std::vector <uint8_t> *blob,  size_t *length);

    static const esp_partition_t* _findFirstPartition();

    static esp_err_t _erasePartition(const esp_partition_t *partition);

    static esp_err_t _openNamespace(const char *newPartitionName, nvs_handle *_nvs_handle);

    static esp_err_t _initializeDefaultPartition();

    static bool _shouldForceCommit(const nvs_handle *nvsHandle, bool forceCommit);
};


#endif //SEQUENCEALL_NVSSERVICE_H
