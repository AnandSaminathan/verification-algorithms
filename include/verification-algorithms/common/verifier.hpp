#pragma once

#include <string>
#include "z3-solver.hpp"

class Verifier {
  public:

    virtual bool check(std::string) = 0;
    virtual int getLength() = 0;
    virtual z3::model getTrace() = 0;
};
