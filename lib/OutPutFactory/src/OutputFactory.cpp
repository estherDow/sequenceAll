#include "OutputFactory.h"
//#include "midiOut.h"
//#include "cvOut.h"
#include <FastLEDOut.h>
#include <OscOut.h>

IOutPuts OutputFactory::make(OutPut OutPutType) {
  switch (OutPutType) {
//    case OutPutType == midi:
//      return new MidiOut midiOut;
//    case OutPutType == cv:
//      return new CvOut cvOut;
    case OutPutType == OSC:
      return OscOut oscOut;
    case OutPutType == LED;
      return FastLEDOut fastLEDOut;
}
