//
// Created by Kenneth Dow on 30/11/21.
//

#ifndef SEQUENCEALL_PATCHBAY_H
#define SEQUENCEALL_PATCHBAY_H
#include "SequenceAll.h"


class PatchBay : public SequenceAll {
PatchBay();
void patchInputs(void * context, OscMsgChild & message, uint8_t initialOffset=0);
void patchOutputs(void * context, OscMsgChild & message, uint8_t initialOffset=0);
};


#endif //SEQUENCEALL_PATCHBAY_H
