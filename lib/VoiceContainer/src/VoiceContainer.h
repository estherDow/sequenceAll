//
// Created by Kenneth Dow on 21/11/21.
//

#ifndef SEQUENCEALL_VOICECONTAINER_H
#define SEQUENCEALL_VOICECONTAINER_H
#include <unordered_map>
#include <Arduino.h>

#include <Voice.h>

typedef std::unordered_map<String, IVoice> VoiceMap;

class VoiceContainer {
    //TODO: A class, which creates new voices and appends them to a list of some sort.
    // this:https://www.cplusplus.com/reference/map/map/
public:
    VoiceContainer();
    void add(String Handle);
    void remove(String Handle);
    Voice * get(String Handle);

private:
    VoiceMap * voiceMap;

};
#endif //SEQUENCEALL_VOICECONTAINER_H
