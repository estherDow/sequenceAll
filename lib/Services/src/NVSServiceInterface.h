//
// Created by Kenneth Dow on 1/1/22.
//

#ifndef SEQUENCEALL_NVSSERVICEINTERFACE_H
#define SEQUENCEALL_NVSSERVICEINTERFACE_H
#include <vector>
#include <cstdint>
#include "RestEndpoint.h"

class IPAddress;
class VoicePatternData;

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

    virtual bool setBool(const char * key, bool value, bool forceCommit) = 0;

    virtual bool setIPAddress(const char * key, IPAddress &value, bool forceCommit) = 0;

    //virtual bool setVoicePatternData(const char * key, VoicePatternData &value, bool forceCommit) = 0;

    virtual bool setBlob(const char * key, uint8_t *blob, size_t length, bool forceCommit) = 0;

    virtual bool setBlob(const char * key, std::vector <uint8_t> *blob, bool forceCommit) = 0;

    virtual bool getInt(const char * key, int64_t *out_value) = 0;  // In case of error, default_value will be returned

    virtual bool getStringLength(const char * key, size_t *length) = 0;

    virtual bool getString(const char * key, char* out_value, size_t *length) = 0;

    virtual bool getBool(const char *key, bool* value) = 0;

    virtual bool getIPAddress(const char * key, IPAddress &value_out) = 0;

    virtual bool getBlobSize(const char * key, size_t *size) = 0;

    virtual bool getBlob(const char * key, uint8_t *blob, size_t *length) = 0;

    virtual bool getBlob(const char * key, std::vector <uint8_t> *blob,  size_t *length) = 0;

    virtual bool commit() = 0;
};

#endif //SEQUENCEALL_NVSSERVICEINTERFACE_H
