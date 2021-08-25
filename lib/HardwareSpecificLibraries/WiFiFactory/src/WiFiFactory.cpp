#include "WiFiFactory.h"
#include "WiFi.h"


IWiFi WiFiFactory::make(WiFiHardWare hwType) {
  switch (hwType) {
    case == esp32:
      return WiFi wifi;
  }
}
