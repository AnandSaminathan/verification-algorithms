#include "verification-algorithms/pnet-coverability/pnet-coverability.hpp"

void PnetCoverability::declare() {
  for(auto symbol: symbols) {
    x.push_back(addOrGetSymbol(symbol));
    
    type type = symbol.getType();
    std::string name = symbol.getName();
    std::string value = symbol.getValue();
    
    std::string nextName = "next_" + name;
    Symbol nextX(type, nextName, value);

    next_x.push_back(addOrGetSymbol(nextX));
  }
}

bool PnetCoverability::check(std::string property) {
  P = stringToZ3(property);
  
  z3::solver s(ctx);
  

}
