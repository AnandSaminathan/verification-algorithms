#include <iostream>
#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"

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
  std::string oneHigh = "G((a == true && b == false && c == false) || (a == false && b == true && c == false) || (a == false && b == false && c == true))";
  std::string allLow = "G(a == false && b == false && c == false)";
  std::string allHigh = "G(a == true && b == true && c == true)";
  std::string firstHigh = "G(a == true && b == false && c == false)";
  std::string firstOrSecondHigh = "G((a == true && b == false && c == false) || (a == false && b == true && c == false))";
  std::string atleastOneHigh = "G(a == true || b == true || c == true)";

  ltlBmc k(symbols, I, T); k.setBound(3);
  assert(k.check(oneHigh) == true);
  assert(k.check(allLow) == false);
  assert(k.check(allHigh) == false);
  assert(k.check(firstHigh) == false);
  assert(k.check(firstOrSecondHigh) == false);
  assert(k.check(atleastOneHigh) == true);
}
