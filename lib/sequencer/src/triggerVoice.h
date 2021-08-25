#ifndef VOICE_H
#define VOICE_H

#include <list>
#include <Arduino.h>
#include <Voice.h>
#include <IObserver.h>


class triggerVoice : public Voice public IObserver {
public:
  void update(char subjectLine, int msg);

};
#endif
