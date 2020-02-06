#pragma once

#include <string>

class KripkeStructure {
  public:
    Kripke(std::string I, std::string T) : I(I), T(T) {}

    inline std::string getI() const { return I; }
    inline std::string getT() const { return T; }

  private:
    const std::string I;
    const std::string T;
};
