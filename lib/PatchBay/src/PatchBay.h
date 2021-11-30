//
// Created by Kenneth Dow on 30/11/21.
//

#ifndef SEQUENCEALL_PATCHBAY_H
#define SEQUENCEALL_PATCHBAY_H

typedef std::unordered_map<char*, > PatchableObjects;

class PatchBay {
public:
    PatchBay(){_patchableObjects = new PatchableObjects;};
    void add();
    static void routeInputs(void *context, OscMsgChild &message, uint8_t initialOffset = 0);
    static void routeOutputs(OscMsgChild &message, uint8_t initialOffset = 0);
    //TODO: Inject all modules here and do reinterpret casts.
private:
    PatchableObjects *_patchableObjects;
};


#endif //SEQUENCEALL_PATCHBAY_H
