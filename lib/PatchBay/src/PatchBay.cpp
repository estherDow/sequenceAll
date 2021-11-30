//
// Created by Kenneth Dow on 30/11/21.
//

#include "SequenceAll.h"




void SequenceAll::routeInputs(void *context, OscMsgChild &message, uint8_t initialOffset) {
    msg.route(voiceContainer, "/voice", VoiceContainer::receive, 0);
    msg.route(oscService, "/osc/", OscService::send, 0);
}


//Patching Inputs to outputs matches sender not receiver in the pattern
void SequenceAll::routeOutputs(void *context, OscMsgChild &message, uint8_t initialOffset) {

    msg.route(oscService, "/voice/1", OscService::send, 0);
}