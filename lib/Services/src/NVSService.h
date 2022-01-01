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

    bool commit() override;

private:
    nvs_handle _nvs_handle;

    bool _findFirstPartition();

    esp_err_t _erasePartition(esp_partition_t *partition);

    esp_err_t _openNamespace(const char *newPartitionName);

    esp_err_t _initializeDefaultPartition() const;
};


#endif //SEQUENCEALL_NVSSERVICE_H
