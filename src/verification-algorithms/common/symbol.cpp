#include "verification-algorithms/common/symbol.hpp"

std::vector<std::string> getSymbolNames(std::vector<Symbol> symbols) {
  std::vector<std::string> ret;
  for(auto symbol: symbols) {
    ret.emplace_back(symbol.getName());
  }
  return ret;
}
