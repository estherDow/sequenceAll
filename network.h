#ifndef WLAN_H
#define WLAN_H

#include <Arduino.h>
#include <WiFi.h>
//UDP OSC
#include <WiFiUdp.h>
#include <OSCMessage.h>


class wlan {
public:
  void begin();
  void sendOsc(uint8_t on, const char* Voice, uint8_t param);
};



#endif
