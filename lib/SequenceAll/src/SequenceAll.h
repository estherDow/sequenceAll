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
#include "NVSService.h"
#include "../../Voice/src/VoiceContainer.h"
#include "SequenceAllProperties.h"


class SequenceAll {
public:
    //SequenceAll();
    explicit SequenceAll(SequenceAllProperties properties) : properties(properties) {};

    void connectOutputToInput(ModuleInterface *output, ModuleInterface *input);

    void run() const;

    void save();

    static void reset();

    SequenceAllProperties properties;
private:
    static void _oscMessageReceiveDebug(OSCMessageInterface &msg);
};

#endif //SEQUENCEALL_SEQUENCEALL_H
