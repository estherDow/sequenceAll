//
// Created by Kenneth Dow on 26/11/21.
//

#ifndef SEQUENCEALL_SEQUENCEALL_H
#define SEQUENCEALL_SEQUENCEALL_H


#include <Clock.h>
#include "../../Voice/src/Voice.h"
#include <SignalTypes.h>
#include <macros.h>
#include <WiFiService.h>
#include "../../Services/src/OscService.h"
#include "OscMessageAdapter.h"
#include "ESPmDNSAdapter.h"
#include "NVSService.h"
#include "../../Voice/src/VoiceContainer.h"


class SequenceAll {
public:
    //SequenceAll();

    void begin();

    void run() const;

    void save();

    static void reset();


    Clock *cClock;
    WiFiService *wiFiService;
    OscService *oscService;
    VoiceContainer *voiceContainer;

private:
    void _setVoices() const;

    static void _oscMessageReceiveDebug(OSCMessageInterface &msg) ;
};

extern SequenceAll sequenceAll;
#endif //SEQUENCEALL_SEQUENCEALL_H
