#pragma once

#include <string>

class Verifier {
  public:

    virtual bool check(std::string) = 0;
};
