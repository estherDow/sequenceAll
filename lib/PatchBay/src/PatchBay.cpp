//
// Created by Kenneth Dow on 30/11/21.
//

#include "PatchBay.h"


void PatchBay::patchInputs(void *context, int &message, int initialOffset) {
    msg.route(voiceContainer, "/voice", VoiceContainer::receive, 0);
    msg.route(oscService, "/osc/", OscService::send, 0);
}
void PatchBay::patchOutputs(void *context, int &message, int initialOffset) {
    msg.route(oscService, "/osc/", OscService::send, 0);
}