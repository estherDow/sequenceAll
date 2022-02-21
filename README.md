## sequence all.

A Software Project for the esp32 microcontroller, that aims to provide a low code entrypoint to build a sequencer out of anything imaginable.
Internal Communication and signal routing is done making heavy use of the [CNMAT/OSC](https://github.com/CNMAT/OSC) library.
Particularly, their OSCMessage class, from which I inherit to make it more suitable to operate in an OOP environment.

Future implementations will create OscMessageAdapter objects to pass them around the system.
This way, a translation layer between `cv/midi/osc` can be run concurrently to sequencing messages to either of the protocols.

This application currently runs on only one core, so the second core is entirely unused and may be leveraged for other duties with few changes to the software.


# current state:

All important values, such as Pulses per quarterNote, Number of voices and sequence length are stored in `macros.h`.

Change your values there if you want to.

The sequencer advertises its services under sequenceall.local.

Use `port 80` for the rest(?) api. following requests may be used to change credentials, as well as the status of accesspoint.
The credentials are stored in non volatile storage.
```
curl -XPOST -H "Content-type: application/json" -d '{"ssid" : "mySSID" , "password" : "myPassword"}' 'sequenceall.local/set_sta'
```

```
curl -XPOST -H "Content-type: application/json" -d '{"ssid" : "myApSSID" , "password" : "myApPassword"}' 'sequenceall.local/set_ap'
```
If you send either request with an empty payload, the sequencer simply changes to the desired mode.
If it cannot join a wifi network, it will return to AP mode automatically.

Once the connection is established, the sequencer listens on `port 8000` for incoming OSC message of the syntax:

```
/{Element In Signal Chain}/{Optional: Number Of Element}/Action/{Optional: Position}
```
Currently following messages are implemented:
```
/voice/{1-voiceCount}/set/{1-sequenceLength}  uint8_t payload
/voice/{1-voiceCount}/mute/{1-sequenceLength}  uint8_t status //Bool seems not to be well supported by CNMAT/OSC code uses implicit cast
/voice/{1-voiceCount}/delete/{1-sequenceLength}  -
```

### needed:

Short term goals:

- implement sendOsc method
- implement switch internal and external clock
- implement hardware keyboard class
- extend rest(?) api

- and implementation of various I/Os, such as keypad, midi, etc.

- save state of all voices to nvm, so that info is available after you shut down :) to be done by implementing setGlob(), i guess.



# Ignore all previous, clean slate on last time

- only ap mode is supported
- clients connected receive all messages
- Only port 8000 is supported
- clients can send messages to host name
- ap name and password may be changed via post request.
- Changes will take effect after restart


//TODO:
- Add Vector of IPAddresses
- on connect add ip to vector
- send osc to all ip connected.

- Remove STA functionality
- remove handle wifi mode method in loop