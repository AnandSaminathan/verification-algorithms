#pragma once

#include <string>
#include "trace.hpp"
#include "z3-solver.hpp"

class Verifier {
  public:

    virtual bool check(std::string) = 0;
    virtual inline int getLength(){
      return stoppedAt;    
    };
    virtual inline Trace getTrace(){
      if(result) throw std::logic_error("No Trace. Last result was SAT");
      return trace;
    };

  protected:

    Trace trace;

    bool result;
    int stoppedAt;
};
