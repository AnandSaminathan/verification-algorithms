#include <iostream>
#include "verification-algorithms/ic3/ic3.hpp"

int main() {
  std::vector<Symbol> symbols;

  int nbits = 100;

  for(int i = 0; i < nbits; ++i) {
    std::string name = "x" + std::to_string(i);
    Symbol xi(bool_const, name);
    symbols.push_back(xi);
  }

  std::string I = "(x0";
  for(int i = 1; i < nbits; ++i) {
    I += " && !x" + std::to_string(i);
  }
  I += ")";

  std::string T = "(";
  for(int i = 0; i < nbits; ++i) {
    std::string nxt = "next_";
    nxt += "x";
    nxt += std::to_string(i);
    int who = (i - 1);
    if(i - 1 < 0) who += nbits;
    std::string pre = "x" + std::to_string(who);
    if(i) T += " && ";
    T += "(" + nxt + " == " + pre + ")";
  }
  T += ")";

  std::string oneHigh = "";
  for(int i = 0; i < nbits; ++i) {
    std::string clause = "(x" + std::to_string(i);
    for(int j = 0; j < i; ++j) {
      if(i != j) {
        clause += " && !x" + std::to_string(j);
      }
    }
    clause += ")";
    if(i) oneHigh += " || ";
    oneHigh += clause;
  }

  IC3 i(symbols, I, T);
  assert(i.check(oneHigh) == true);
}
