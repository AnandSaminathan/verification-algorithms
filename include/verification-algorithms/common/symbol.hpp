#pragma once

#include <string>
#include "types.hpp"

class Symbol {
  public:
    Symbol(type symbolType, std::string name) : symbolType(symbolType), name(name), value("") {}
    Symbol(type symbolType, std::string name, std::string value) : symbolType(symbolType), name(name), value(value) {}
    Symbol() {}

    inline type getType() { return symbolType;  }
    inline std::string getName() { return name;  }
    inline std::string getValue() { return value; }

  private:
  
    type symbolType;
    std::string name, value;
};
