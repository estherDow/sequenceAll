//
// Created by Kenneth Dow on 26/11/21.
//

#ifndef SEQUENCEALL_SEQUENCEALL_H
#define SEQUENCEALL_SEQUENCEALL_H

#include <WiFiUdp.h>

#include <Clock.h>
#include <Voice.h>
#include <SignalTypes.h>
#include <macros.h>
#include <WiFiService.h>
#include <OscService.h>
#include <VoiceContainer.h>

class SequenceAll {
public:
    SequenceAll();

    void run();

    void save();

private:
    void _setVoices();

    Clock *_clock;
    WiFiService *_wifiService;
    OscService *_oscService;
    WiFiUDP *_udp;
    VoiceContainer *_voiceContainer;
};


#endif //SEQUENCEALL_SEQUENCEALL_H
