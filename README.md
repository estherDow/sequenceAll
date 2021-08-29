sequence all.

current state:

clock sends out pulses at 48 PULSES_PER_QUARTER_NOTE, defined in macros, if you'd like to change that.

voice handles clock division and trigger conditioning if:
a)current clock pulse and subDivisions line up
b)a step is set to not 0 in the vector.
