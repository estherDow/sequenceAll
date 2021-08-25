#include "OutputFactory.h"
//#include "midiOut.h"
//#include "cvOut.h"
#include "OscOut.h"

IOutPuts OutputFactory::make(OutPut OutPutType) {
  switch (OutPutType) {
//    case OutPutType == midi:
//      return new MidiOut midiOut;
//    case OutPutType == cv:
//      return new CvOut cvOut;
    case OutPutType == osc:
      return OscOut oscOut;
}
