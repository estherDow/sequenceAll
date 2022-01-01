//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_NVSSERVICEINTERFACE_H
#define SEQUENCEALL_NVSSERVICEINTERFACE_H
#include <vector>
#include <cstdint>

class IPAddress;

class NVSServiceInterface {
public:
    virtual ~NVSServiceInterface() = default;

    virtual bool openNameSpace(const char *partitionName) = 0;

    virtual void closeNameSpace() = 0;

    virtual bool deleteAllKeysInPartition(bool forceCommit) = 0;

    virtual bool eraseByKey(const char * key, bool forceCommit) = 0;

    virtual bool setInt(const char * key, int8_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, uint8_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, int16_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, uint16_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, int32_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, uint32_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, int64_t value, bool forceCommit) = 0;

    virtual bool setInt(const char * key, uint64_t value, bool forceCommit) = 0;

    virtual bool setString(const char * key, const char* value, bool forceCommit) = 0;

    virtual bool setIPAddress(const char * key, IPAddress value, bool forceCommit) = 0;

    virtual bool setBlob(const char * key, uint8_t *blob, size_t length, bool forceCommit) = 0;

    virtual bool setBlob(const char * key, std::vector <uint8_t> &blob, bool forceCommit) = 0;

    virtual int64_t getInt(const char * key, int64_t default_value = 0) = 0;  // In case of error, default_value will be returned

    virtual bool getString(const char * key, char* &res) = 0;

    virtual size_t getBlobSize(const char * key) = 0;

    virtual bool getBlob(const char * key, uint8_t *blob, size_t length) = 0;

    virtual bool getBlob(const char * key, std::vector <uint8_t> &blob) = 0;

    virtual bool commit() = 0;
};

#endif //SEQUENCEALL_NVSSERVICEINTERFACE_H
