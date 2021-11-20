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