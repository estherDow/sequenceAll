#sequence all.

current state:

clock sends out pulses at 48 PULSES_PER_QUARTER_NOTE, defined in macros, if you'd like to change that.

voice handles clock division and trigger conditioning if:
a)current clock pulse and subDivisions line up
b)a step is set to not 0 in the vector.


Wifi implemented, advertizes services under sequenceall.local, currently not working under android.

Who suppots mDNS?

sta / ap modes may be set via post requests:

curl -XPOST -H "Content-type: application/json" -d '{"ssid" : "mySSID" , "password" : "myPassword"}' 'sequenceall.local/set_sta'

curl -XPOST -H "Content-type: application/json" -d '{"ssid" : "myApSSID" , "password" : "myApPassword"}' 'sequenceall.local/set_ap'

Currently lamda methods store ssid and pwd as key value pairs in nvm

###needed:

inputFactory
and implementation of various inputs keypad, midi, osc

outputfactory
and implementation of various outputs keypad, midi, osc

save state of all voices to nvm, so that info is available after you shut down :)
to be done by implementing setGlob()


successful use of async webserver could enable a super simple js gui, which sends ajax requests to keep itself updated.
webapp needs to be served only once and could be ground for a lot of explorative testing.

I need to rewrite the message distribution system in order to send messages only to the modules required.
If I have multiple voice classes, how may I call set step only on one voice. etc.

I can store all voice objects in an unordered map, which I can now use to distribute messages to the individual voices and operate upon them. 

