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

esp_partition_t *NVSService::_findFirstPartition() {
    return esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
}

esp_err_t NVSService::_erasePartition(esp_partition_t *partition) {
    return esp_partition_erase_range(partition, 0, partition->size);
}

esp_err_t NVSService::_openNamespace(const char *newNameSpace) {
    nvs_open(newNameSpace, NVS_READWRITE, &_nvs_handle)
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
    return esp_err_t err = nvs_erase_all(_nvs_handle);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
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
    if (forceCommit) {
        return commit();
    }
    return true;
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
bool NVSService::setInt( const char *key, int8_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i8(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, uint8_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u8(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, int16_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i16(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, uint16_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u16(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, int32_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i32(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, uint32_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u32(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, int64_t value, bool forceCommit) {
    esp_err_t err = nvs_set_i64(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}

bool NVSService::setInt( const char *key, uint64_t value, bool forceCommit) {
    esp_err_t err = nvs_set_u64(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}
/**@}*/

bool NVSService::setString(const char *key, const char *value, bool forceCommit) {
    esp_err_t err = nvs_set_str(_nvs_handle, key, value);
    if (err != ESP_OK)
        return false;
    if (forceCommit) {
        return commit();
    }
    return true;
}





