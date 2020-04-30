// example from https://ece.uwaterloo.ca/~vganesh/TEACHING/W2013/SATSMT/IC3.pdf

#include <iostream>
#include "verification-algorithms/ic3/ic3.hpp"

int main() {
  Symbol a(bool_const, "a");
  Symbol b(bool_const, "b");
  Symbol c(bool_const, "c");

  std::vector<Symbol> symbols;
  symbols.push_back(a);
  symbols.push_back(b);
  symbols.push_back(c);

  std::string I = "(a && b && !c)";
  std::string T = "(next_c || !a) && (!next_c || a) && (!next_b || b) && (!next_a || !a || !b) && (next_a || a || !c) && (next_a || b || !c)";
  std::string P1 = "(!a || !b || !c)";
  std::string P2 = "(a || b || c)";
    

  IC3 i(symbols, I, T);
  assert(i.check(P1) == true);
  assert(i.check(P2) == true);
}
