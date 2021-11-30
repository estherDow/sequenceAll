//
// Created by Kenneth Dow on 30/11/21.
//

#ifndef SEQUENCEALL_PATCHBAY_H
#define SEQUENCEALL_PATCHBAY_H


class PatchBay {
PatchBay();
void patchInputs(void * context, OscMsgChild & message, uint8_t initialOffset);
void patchOutputs(void * context, OscMsgChild & message, uint8_t initialOffset);
};


#endif //SEQUENCEALL_PATCHBAY_H
