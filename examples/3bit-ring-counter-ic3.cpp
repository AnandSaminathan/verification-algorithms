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

  std::string I = "(a && !b && !c)";
  std::string T = "((next_a == c) && (next_b == a) && (next_c == b))";
  std::string oneHigh = "((a && !b && !c) || (!a && b && !c) || (!a && !b && c))";
  std::string allLow = "(!a && !b && !c)";
  std::string allHigh = "(a && b && c)";
  std::string firstHigh = "(a && !b && !c)";
  std::string firstOrSecondHigh = "((a && !b && !c) || (!a && b && !c))";
  std::string atleastOneHigh = "(a || b || c)";

  IC3 i(symbols, I, T);
  assert(i.check(oneHigh) == true);
  assert(i.check(allLow) == false);
  assert(i.check(allHigh) == false);
  assert(i.check(firstHigh) == false);
  assert(i.check(firstOrSecondHigh) == false);
  assert(i.check(atleastOneHigh) == true);
}
