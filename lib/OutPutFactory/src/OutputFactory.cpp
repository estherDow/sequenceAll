#include "OutputFactory.h"

IOutPuts* OutputFactory::make(OutPut OutPutType) {
  switch (OutPutType) {
//    case OutPutType == midi:
//      return new MidiOut midiOut;
//    case OutPutType == cv:
//      return new CvOut cvOut;
    case OSC:
    {
      OscOut *oscOut;
      OscOut osc;
      oscOut = & osc;
      return oscOut;
    }


    case LED:
    {
      OscOut *oscOut;
      OscOut osc;
      oscOut = & osc;
      return oscOut;
    }
    default:
    {
      OscOut *oscOut;
      OscOut osc;
      oscOut = & osc;
      return oscOut;
    }
}
}
