#ifndef IOUTPUTS_H
#define IOUTPUTS_H


enum OutPut {osc,midi,cv};


class IOutPuts {
  //virtual IOutput();
  virtual ~IOutPuts();
  virtual void dispatchSignal(uint8_t value) = 0;

};
#endif
