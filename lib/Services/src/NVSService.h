//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_NVSSERVICE_H
#define SEQUENCEALL_NVSSERVICE_H

#include <cstdint>

#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"

#include "IPAddress.h"

#include "NVSServiceInterface.h"

class NVSService : public NVSServiceInterface {
public:
    ~NVSService() override = default;

    bool openNameSpace(const char *nameSpace) override;

    void closeNameSpace() override;

    bool deleteAllKeysInPartition(bool forceCommit) override;

    bool eraseByKey(const char * key, bool forceCommit) override;

    bool setInt(const char * key, int8_t value, bool forceCommit) override;

    bool setInt(const char * key, uint8_t value, bool forceCommit) override;

    bool setInt(const char * key, int16_t value, bool forceCommit) override;

    bool setInt(const char * key, uint16_t value, bool forceCommit) override;

    bool setInt(const char * key, int32_t value, bool forceCommit) override;

    bool setInt(const char * key, uint32_t value, bool forceCommit) override;

    bool setInt(const char * key, int64_t value, bool forceCommit) override;

    bool setInt(const char * key, uint64_t value, bool forceCommit) override;

    bool setString(const char * key, const char* value, bool forceCommit) override;

    bool setBool(const char * key, bool  value, bool forceCommit) override;

    bool setIPAddress(const char * key, IPAddress &value, bool forceCommit) override;

    //bool setVoicePatternData(const char * key, VoicePatternData &value, bool forceCommit) override;

    bool setBlob(const char * key, uint8_t *blob, size_t length, bool forceCommit) override;

    bool setBlob(const char * key, std::vector <uint8_t> *blob, bool forceCommit) override;

    bool getInt(const char * key, int64_t *out_value) override;

    bool getStringLength(const char * key, size_t *length) override;

    bool getString(const char * key, char* out_value, size_t *length) override;

    bool getBool(const char *key, bool *value) override;

    bool getIPAddress(const char * key, IPAddress &value_out) override;

    bool getBlobSize(const char * key, size_t *size) override;

    bool getBlob(const char * key, uint8_t *blob, size_t *length) override;

    bool getBlob(const char * key, std::vector <uint8_t> *blob,  size_t *length) override;

    bool commit() override;

private:
    nvs_handle _nvs_handle;

    const esp_partition_t* _findFirstPartition();

    esp_err_t _erasePartition(const esp_partition_t *partition);

    esp_err_t _openNamespace(const char *newPartitionName);

    esp_err_t _initializeDefaultPartition() const;

    bool _shouldForceCommit(bool forceCommit);
};


#endif //SEQUENCEALL_NVSSERVICE_H
