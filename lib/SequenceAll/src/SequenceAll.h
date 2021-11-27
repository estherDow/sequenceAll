//
// Created by Kenneth Dow on 26/11/21.
//

#ifndef SEQUENCEALL_SEQUENCEALL_H
#define SEQUENCEALL_SEQUENCEALL_H

#include <WiFiUdp.h>
#include <ArduinoNvs.h>

#include <Clock.h>
#include <Voice.h>
#include <SignalTypes.h>
#include <macros.h>
#include <WiFiService.h>
#include <OscService.h>
#include <VoiceContainer.h>

class SequenceAll {
public:
    //SequenceAll();

    void begin();

    void run();

    void save();

    void reset();

private:
    void _setVoices();

    Clock *_clock;
    WiFiService *_wifiService;
    OscService *_oscService;
    WiFiUDP *_udp;
    VoiceContainer *_voiceContainer;
};

extern SequenceAll sequenceAll;
#endif //SEQUENCEALL_SEQUENCEALL_H