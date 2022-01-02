//
// Created by Kenneth Dow on 1/1/22.
//

#include "NVSService.h"

/**
 * @brief      Open NameSpace
 *
 * This Function creates a new Partition identified by its handle saved in field _nvs_handle.
 * To free the resources you may call deletePartition()
 *
 * @param[in]  const char * newPartitionName
 *
 * @return bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::openNameSpace(const char *nameSpace) {

    esp_err_t error = _initializeDefaultPartition();
    if (error != ESP_OK) {
        if (error != ESP_ERR_NVS_NO_FREE_PAGES)
            return false;

        const esp_partition_t *firstNvsPartition = _findFirstPartition();
        //const esp_partition_t* firstNvsPartition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);

        if (firstNvsPartition == nullptr)
            return false;

        error = _erasePartition(firstNvsPartition);

        esp_err_t err = _initializeDefaultPartition();
        if (err)
            return false;
    }

    error = _openNamespace(nameSpace);
    if (error != ESP_OK)
        return false;

    return true;
}
//---------------------------------------------------------------------------------------------------------------------

esp_err_t NVSService::_initializeDefaultPartition() const { return nvs_flash_init(); }

const esp_partition_t *NVSService::_findFirstPartition() {
    return esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
}

esp_err_t NVSService::_erasePartition(const esp_partition_t *partition) {
    return esp_partition_erase_range(partition, 0, partition->size);
}

esp_err_t NVSService::_openNamespace(const char *newNameSpace) {
    return nvs_open(newNameSpace, NVS_READWRITE, &_nvs_handle);
}

/**
 * @brief      close NamesSpace by handle.
 *
 * This Function frees the resources of a NameSpace identified by its handle saved in field _nvs_handle.
 * Sets field _nvs_handle = 0 to avoid reuse.
 *
 */
void NVSService::closeNameSpace() {
    nvs_close(_nvs_handle);
    _nvs_handle = 0;
}

/**
 * @brief      Deletes all Keys in NameSpace created or accessed with this object
 *
 *
 * @param[in]  bool forceCommit \n true - Immediately write changes to storage, \n false - wait for explicit commit() call

 *
 * @return[in] bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::deleteAllKeysInPartition(bool forceCommit) {
    esp_err_t error = nvs_erase_all(_nvs_handle);
    if (error != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

/**
 * @brief      Deletes a Key-Value Pair by a given Key in NameSpace created or accessed with this object
 *
 *
 * @param [in]  const char  *key - Name of key which should be deleted.
 * @param[in]  bool forceCommit \n true - Immediately write changes to storage, \n false - wait for explicit commit() call
 *
 * @return bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::eraseByKey(const char *key, bool forceCommit) {
    esp_err_t err = nvs_erase_key(_nvs_handle, key);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

/**
 * @brief      Writes changes to storage
 *
 * @return bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::commit() {
    esp_err_t err = nvs_commit(_nvs_handle);
    if (err != ESP_OK)
        return false;

    return true;
}

/**@{*/
/**
 * @brief     Sets an integer Type identified by a Key in NameSpace created or accessed with this object
 *
 * @param [in]  const char  *key - Name of key which should be set.
 * @param [in]  integerType  value - Name of value which should be set.
 * @param[in]  bool forceCommit \n true - Immediately write changes to storage, \n false - wait for explicit commit() call
 *
 * @return bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::setInt(const char *key, int8_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i8(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, uint8_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u8(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, int16_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i16(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, uint16_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u16(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, int32_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i32(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, uint32_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u32(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, int64_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i64(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setInt(const char *key, uint64_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u64(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

/**@}*/

bool NVSService::setString(const char *key, const char *value, bool forceCommit) {
    esp_err_t err = nvs_set_str(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setBool(const char *key, bool *value, bool forceCommit) {
    esp_err_t err = nvs_set_u8(_nvs_handle, key, uint8_t(value));
    if (err != ESP_OK)
        return false;

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setIPAddress(const char *key, IPAddress &value, bool forceCommit) {
    uint8_t ipAddress[4];
    for (uint8_t n = 0; n < sizeof ipAddress; n++) {
        ipAddress[n] = value[n];
    }
    esp_err_t error = nvs_set_blob(_nvs_handle, key, ipAddress, sizeof(ipAddress));
    if (error != ESP_OK) {
        return false;
    }

    return _shouldForceCommit(forceCommit);
}


bool NVSService::setBlob(const char *key, uint8_t *blob, size_t length, bool forceCommit) {
    esp_err_t error = nvs_set_blob(_nvs_handle, key, blob, length);
    if (error != ESP_OK) {
        return false;
    }

    return _shouldForceCommit(forceCommit);
}

bool NVSService::setBlob(const char *key, std::vector<uint8_t> *blob, bool forceCommit) {
    esp_err_t error = nvs_set_blob(_nvs_handle, key, blob, blob->size());
    if (error != ESP_OK) {
        return false;
    }

    return _shouldForceCommit(forceCommit);
}


bool NVSService::getBool(const char *key, bool *value) {
    return false;
}

bool NVSService::getIPAddress(const char *key, IPAddress &value_out) {
    uint * requiredSize = 0;
    esp_err_t error = nvs_get_blob(_nvs_handle, key, NULL, requiredSize);
    if (error != ESP_OK) {
        return false;
    }
    uint8_t ipAddress[*requiredSize];
    error = nvs_get_blob(_nvs_handle, key, ipAddress, requiredSize);
    value_out = ipAddress;

    return true;
}

bool NVSService::getStringLength(const char *key, size_t *length) {
    esp_err_t error = nvs_get_str(_nvs_handle, key, NULL, length);
    if (error != ESP_OK) {
        return false;
    }

    return true;
}

bool NVSService::getString(const char *key, char *out_value, size_t *length) {
    esp_err_t error = nvs_get_str(_nvs_handle, key, out_value, length);
    if (error != ESP_OK) {
        return false;
    }
    return true;
}

bool NVSService::getInt(const char *key, int64_t *out_value) {
    int8_t v_i8;
    uint8_t v_u8;
    int16_t v_i16;
    uint16_t v_u16;
    int32_t v_i32;
    uint32_t v_u32;
    int64_t v_i64;
    uint64_t v_u64;

    esp_err_t err;
    err = nvs_get_i8(_nvs_handle, key, &v_i8);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u8;
        return true;
    }

    err = nvs_get_u8(_nvs_handle, key, &v_u8);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u8;
        return true;
    }

    err = nvs_get_i16(_nvs_handle, key, &v_i16);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i16;
        return true;
    }

    err = nvs_get_u16(_nvs_handle, key, &v_u16);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u16;
        return true;
    }

    err = nvs_get_i32(_nvs_handle, key, &v_i32);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i32;
        return true;
    }

    err = nvs_get_u32(_nvs_handle, key, &v_u32);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u32;
        return true;
    }

    err = nvs_get_i64(_nvs_handle, key, &v_i64);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i64;
        return true;
    }

    err = nvs_get_u64(_nvs_handle, key, &v_u64);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u64;
        return true;
    }

    return false;
}

bool NVSService::getBlobSize(const char *key, size_t *size) {
    esp_err_t error = nvs_get_blob(_nvs_handle, key, NULL, size);
    if (error != ESP_OK) {
        return false;
    }

    return true;
}

bool NVSService::getBlob(const char *key, uint8_t *blob, size_t *length) {
    esp_err_t error = nvs_get_blob(_nvs_handle, key, blob, length);
    if (error != ESP_OK) {
        return false;
    }

    return true;
}

bool NVSService::getBlob(const char *key, std::vector<uint8_t> *blob, size_t *length) {
    esp_err_t error = nvs_get_blob(_nvs_handle, key, blob, length);
    if (error != ESP_OK) {
        return false;
    }

    return true;
}

bool NVSService::_shouldForceCommit(bool forceCommit) {
    if (forceCommit) {
        return commit();
    }
    return true;
}






