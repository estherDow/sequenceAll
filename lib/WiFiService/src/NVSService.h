//
// Created by Kenneth Dow on 20/11/21.
//

#ifndef SEQUENCEALL_NVSSERVICE_H
#define SEQUENCEALL_NVSSERVICE_H
#include <ArduinoNvs.h>

class NVSService {
public:

//TODO: Collect ideas on how to deal with vector lenghts of multiple bytes.

    static void writeStringToNVS( String key, String value){
        NVS.begin();
        NVS.setString(key, value);
        NVS.close();
    }

    static void writeIntToNVS(String key, uint8_t value){
        NVS.begin();
        NVS.setInt(key,value);
        NVS.close();
    }

    static String readStringFromNVS(String key){
        NVS.begin();
        String value = "";
        NVS.getString(key, value);
        NVS.close();
        return value;
    }

    static uint8_t readIntFromNVS(String key){
        NVS.begin();
        int64_t value = 0;
        NVS.getInt(key);
        NVS.close();
        return value;
    }
};
#endif //SEQUENCEALL_NVSSERVICE_H
