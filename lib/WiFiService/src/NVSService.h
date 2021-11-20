//
// Created by Kenneth Dow on 20/11/21.
//

#ifndef SEQUENCEALL_NVSSERVICE_H
#define SEQUENCEALL_NVSSERVICE_H
#include <ArduinoNvs.h>
class NVSService {
public:


    static void writeStringToNVS(const char * ssid, const char * Password){
        NVS.begin();

        NVS.close();
    }

    static void writeIntToNVS(const char * ssid, const char * Password){
        NVS.begin();

        NVS.close();
    }

    static void readFromNVS(){
        NVS.begin();

        NVS.close();
    }
};
#endif //SEQUENCEALL_NVSSERVICE_H
