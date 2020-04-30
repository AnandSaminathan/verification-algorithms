#include <iostream>
#include <string>
#include "verification-algorithms/common/cnf.hpp"

int main() {
  addOrGetSymbol(Symbol(bool_const, "a"));
  addOrGetSymbol(Symbol(int_const, "b"));
  addOrGetSymbol(Symbol(bool_const, "c"));
  addOrGetSymbol(Symbol(int_const, "d"));
  CNF cnf("a && !c && (b == 2 || !a) && (b <= 3) && (b + d < 3 || a)");
  auto clauses = cnf.getClauses();
  for(auto clause: clauses) {
    std::cout << clause << '\n';
  }
}
