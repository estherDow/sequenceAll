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
bool NVSService::openNameSpace(const char *nameSpace, nvs_handle *nvs_handle) {

    esp_err_t error = _initializeDefaultPartition();
    if (error != ESP_OK) {
        if (error != ESP_ERR_NVS_NO_FREE_PAGES)
            return false;

        const esp_partition_t *firstNvsPartition = _findFirstPartition();
        //const esp_partition_t* firstNvsPartition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);

        if (firstNvsPartition == nullptr)
            return false;

        error = _erasePartition(firstNvsPartition);
        if (error != ESP_OK) {
            return false;
        }
        esp_err_t err = _initializeDefaultPartition();
        if (err)
            return false;
    }

    error = _openNamespace(nameSpace, nvs_handle);
    if (error != ESP_OK)
        return false;

    return true;
}
//---------------------------------------------------------------------------------------------------------------------

esp_err_t NVSService::_initializeDefaultPartition() { return nvs_flash_init(); }

const esp_partition_t *NVSService::_findFirstPartition() {
    return esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);
}

esp_err_t NVSService::_erasePartition(const esp_partition_t *partition) {
    return esp_partition_erase_range(partition, 0, partition->size);
}

esp_err_t NVSService::_openNamespace(const char *newNameSpace, nvs_handle *_nvs_handle) {
    return nvs_open(newNameSpace, NVS_READWRITE, _nvs_handle);
}

/**
 * @brief      close NamesSpace by handle.
 *
 * This Function frees the resources of a NameSpace identified by its handle saved in field _nvs_handle.
 * Sets field _nvs_handle = 0 to avoid reuse.
 *
 */
void NVSService::closeNameSpace(const nvs_handle *nvsHandle) {
    nvs_close(*nvsHandle);
    nvs_commit(*nvsHandle);
}

/**
 * @brief      Deletes all Keys in NameSpace created or accessed with this object
 *
 *
 * @param[in]  bool forceCommit \n true - Immediately write changes to storage, \n false - wait for explicit commit() call

 *
 * @return[in] bool true if successful, false if anything goes wrong on the way.
 */
bool NVSService::deleteAllKeysInPartition(const char *NameSpace, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_erase_all(nvsHandle);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }

    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
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
bool NVSService::eraseByKey(const char *NameSpace, const char *key, bool forceCommit) {
    nvs_handle nvsHandle;
    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_erase_key(nvsHandle, key);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
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
bool NVSService::setInt(const char *NameSpace, const char *key, int8_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_i8(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, uint8_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_u8(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, int16_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_i16(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, uint16_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_u16(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, int32_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_i32(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, uint32_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_u32(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, int64_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_i64(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setInt(const char *NameSpace, const char *key, uint64_t value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_u64(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

/**@}*/

bool NVSService::setString(const char *NameSpace, const char *key, const char *value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err = nvs_set_str(nvsHandle, key, value);
    if (err != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setBool(const char *NameSpace, const char *key, bool value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_set_u8(nvsHandle, key, uint8_t(value));
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setIPAddress(const char *NameSpace, const char *key, IPAddress &value, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);

    uint8_t ipAddress[4];
    for (int n = 0; n < sizeof(ipAddress); n++) {
        ipAddress[n] = value[n];
    }
    esp_err_t error = nvs_set_blob(nvsHandle, key, ipAddress, sizeof(ipAddress));
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);
        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setCredentials(const char *NameSpace, WiFiCredentialsChar *dataFromRequest, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);;
    if (strlen(dataFromRequest->ssid) != 0) {
        strcat(dataFromRequest->uri,"ssid");


        if (!setString(NameSpace, dataFromRequest->uri, dataFromRequest->ssid)) {
            closeNameSpace(&nvsHandle);
            return false;
        }
    }

    if (strlen(dataFromRequest->pwd) != 0) {
        strcat(dataFromRequest->uri,"pwd");

        if (!setString(NameSpace, dataFromRequest->uri, dataFromRequest->pwd)) {
            closeNameSpace(&nvsHandle);
            return false;
        }
    }
    closeNameSpace(&nvsHandle);
    return true;
}

bool NVSService::setBlob(const char *NameSpace, const char *key, uint8_t *blob, size_t length, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_set_blob(nvsHandle, key, blob, length);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}

bool NVSService::setBlob(const char *NameSpace, const char *key, std::vector<uint8_t> *blob, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_set_blob(nvsHandle, key, blob, blob->size());
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return _shouldForceCommit(&nvsHandle, forceCommit);
}


bool NVSService::getBool(const char *NameSpace, const char *key, bool *value) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    uint8_t valueFromNVS = 0;
    esp_err_t error = nvs_get_u8(nvsHandle, key, &valueFromNVS);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    *value = valueFromNVS;
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getIPAddress(const char *NameSpace, const char *key, IPAddress &value_out) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    uint requiredSize = 0;
    esp_err_t error = nvs_get_blob(nvsHandle, key, NULL, &requiredSize);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    uint8_t ipAddress[requiredSize];
    error = nvs_get_blob(nvsHandle, key, ipAddress, &requiredSize);
    value_out = ipAddress;
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getCredentials(const char *NameSpace, WiFiCredentialsChar *credentials, bool forceCommit) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    size_t ssidLength;
    strcat(credentials->uri, "ssid");

    if (!getStringLength(NameSpace, credentials->uri, &ssidLength)) {
        closeNameSpace(&nvsHandle);
        Serial.print("could not get stringlength ssid ");

        return false;
    }

    char ssid[ssidLength];
    if (!getString(NameSpace, credentials->uri, ssid, &ssidLength)) {
        closeNameSpace(&nvsHandle);
        Serial.print("could not get string ssid ");

        return false;
    }
    strcpy(credentials->ssid, ssid);

    size_t pwdLength;
    strcat(credentials->uri, "pwd");
    if (!getStringLength(NameSpace, credentials->uri, &pwdLength)) {
        closeNameSpace(&nvsHandle);
        Serial.println("could not get stringlength pwd ");

        return false;
    }

    char pwd[pwdLength];
    if (!getString(NameSpace, credentials->uri, pwd, &pwdLength)) {
        closeNameSpace(&nvsHandle);
        Serial.print("could not get string pwd ");

        return false;
    }
    Serial.printf("this is ssid: %s and this is pwd: %s \n", ssid, pwd);
    strcpy(credentials->pwd, pwd);


    return true;
}

bool NVSService::getStringLength(const char *NameSpace, const char *key, size_t *length) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_get_str(nvsHandle, key, NULL, length);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getString(const char *NameSpace, const char *key, char *out_value, size_t *length) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_get_str(nvsHandle, key, out_value, length);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getInt(const char *NameSpace, const char *key, int64_t *out_value) {
    int8_t v_i8;
    uint8_t v_u8;
    int16_t v_i16;
    uint16_t v_u16;
    int32_t v_i32;
    uint32_t v_u32;
    int64_t v_i64;
    uint64_t v_u64;

    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t err;
    err = nvs_get_i8(nvsHandle, key, &v_i8);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u8;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_u8(nvsHandle, key, &v_u8);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u8;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_i16(nvsHandle, key, &v_i16);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i16;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_u16(nvsHandle, key, &v_u16);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u16;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_i32(nvsHandle, key, &v_i32);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i32;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_u32(nvsHandle, key, &v_u32);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u32;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_i64(nvsHandle, key, &v_i64);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_i64;
        closeNameSpace(&nvsHandle);

        return true;
    }

    err = nvs_get_u64(nvsHandle, key, &v_u64);
    if (err == ESP_OK) {
        *out_value = (int64_t) v_u64;
        closeNameSpace(&nvsHandle);

        return true;
    }
    closeNameSpace(&nvsHandle);

    return false;
}

bool NVSService::getBlobSize(const char *NameSpace, const char *key, size_t *size) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_get_blob(nvsHandle, key, NULL, size);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getBlob(const char *NameSpace, const char *key, uint8_t *blob, size_t *length) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_get_blob(nvsHandle, key, blob, length);
    if (error != ESP_OK) {
        closeNameSpace(&nvsHandle);

        return false;
    }
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::getBlob(const char *NameSpace, const char *key, std::vector<uint8_t> *blob, size_t *length) {
    nvs_handle nvsHandle;

    openNameSpace(NameSpace, &nvsHandle);
    esp_err_t error = nvs_get_blob(nvsHandle, key, blob, length);
    if (error != ESP_OK) {
        return false;
        closeNameSpace(&nvsHandle);
    }
    closeNameSpace(&nvsHandle);

    return true;
}

bool NVSService::_shouldForceCommit(const nvs_handle *nvsHandle, bool forceCommit) {
    if (forceCommit) {
        return nvs_commit(*nvsHandle);
    }
    return true;
}







