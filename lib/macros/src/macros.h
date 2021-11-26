#ifndef MACROS_H
#define MACROS_H

//
//CLOCK
//

#define DEFAULT_BEATS_PER_MINUTE 160
#define DEFAULT_SEQUENCE_LENGTH 16

//
//VOICE
//

#define PULSES_PER_QUARTER_NOTE 48
#define TOTAL_NUMBER_OF_VOICES  4


//
// OutPuts/FastLED
//

#define DATA_PIN    3

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    60
#define BRIGHTNESS  255

//
//WIRELESS SERVICES
//
#define DEFAULT_AP_SSID         "sequenceAll"
#define DEFAULT_AP_PASSWORD     "transLiberationNow"

#define LOCAL_UDP_PORT                   8000
#define DEFAULT_REMOTE_UDP_PORT          9000
#define DEFAULT_REMOTE_HOSTNAME          "remoteHost"



#endif
