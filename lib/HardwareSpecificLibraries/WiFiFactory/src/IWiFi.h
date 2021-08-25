#ifndef IWIFI_H
#define IWIFI_H

/*
This interface provides minimal abstraction to different
Hardware specific Implementations of Wifi Functionalities
In Arduino. It assumes all expose a Unified API.
https://www.arduino.cc/en/Reference/WiFi
*/

enum WiFiHardWare {esp32};
class IWiFi {
  virtual ~IWiFi(){};
}
#endif
