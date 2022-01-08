//
// Created by Kenneth Dow on 26/11/21.
//

#ifndef SEQUENCEALL_SEQUENCEALL_H
#define SEQUENCEALL_SEQUENCEALL_H


#include <Clock.h>
#include <../../VoiceContainer/src/Voice.h>
#include <SignalTypes.h>
#include <macros.h>
#include "../../Services/src/WiFiService.h"
#include "../../Services/src/OscService.h"
#include "OscMessageAdapter.h"
#include "ESPmDNSAdapter.h"
#include "NVSService.h"
#include "../../VoiceContainer/src/VoiceContainer.h"


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
};

extern SequenceAll sequenceAll;
#endif //SEQUENCEALL_SEQUENCEALL_H
