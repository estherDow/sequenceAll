//
// Created by Kenneth Dow on 21/11/21.
//

#ifndef SEQUENCEALL_VOICECONTAINER_H
#define SEQUENCEALL_VOICECONTAINER_H
#include <unordered_map>
#include <Arduino.h>

#include <Voice.h>
#include <SignalTypes.h>

typedef std::unordered_map<int,Voice> VoiceMap;

class VoiceContainer {
    //TODO: A class, which creates new voices and appends them to a list of some sort.
    // this:https://www.cplusplus.com/reference/map/map/
public:
    VoiceContainer();
    void add(int Handle);
    void remove(int Handle);
    Voice * get(int Handle);

private:
    VoiceMap * voiceMap;

};
#endif //SEQUENCEALL_VOICECONTAINER_H
