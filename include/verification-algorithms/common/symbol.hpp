#pragma once

#include <string>
#include <vector>
#include "types.hpp"

namespace verifier {
  class Symbol {
    public:
      Symbol(type symbolType, std::string name) : symbolType(symbolType), name(name), value("") {}
      Symbol(type symbolType, std::string name, std::string value) : symbolType(symbolType), name(name), value(value) {}
      Symbol() {}
  
      inline type getType() { return symbolType;  }
      inline std::string getName() { return name;  }
      inline std::string getValue() { return value; }
  
      inline std::string setName(std::string name) { (this->name) = name; }
      inline void setValue(std::string value) { (this->value) = value;  }
      inline void setType(type symbolType) { (this->symbolType) = symbolType;  }
  
    private:
    
      type symbolType;
      std::string name, value;
  };
  
  extern std::vector<std::string> getSymbolNames(std::vector<Symbol>); 
}
