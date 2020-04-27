#pragma once

#include <string>
#include "trace.hpp"
#include "z3-solver.hpp"

class Verifier {
  public:

    virtual bool check(std::string) = 0;
    virtual int getLength() = 0;
    virtual Trace getTrace() = 0;
};
