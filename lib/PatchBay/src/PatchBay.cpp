//
// Created by Kenneth Dow on 30/11/21.
//

#include "PatchBay.h"



void PatchBay::routeInputs(void *context, OscMsgChild &message, uint8_t initialOffset) {
    msg.route(voiceContainer, "/voice", VoiceContainer::receive, 0);
    msg.route(oscService, "/osc/", OscService::send, 0); //loopback
}


//Patching Inputs to outputs matches sender not receiver in the pattern
void PatchBay::routeOutputs(OscMsgChild &message, uint8_t initialOffset) {

    msg.route(oscService, "/voice/1", OscService::send, 0);
    msg.route(oscService, "/voice/2", OscService::send, 0);
    msg.route(oscService, "/voice/3", OscService::send, 0);
    msg.route(oscService, "/voice/4", OscService::send, 0);
}