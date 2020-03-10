#include <iostream>
#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"

int main() {
  std::vector<Symbol> symbols;

  for(int i = 0; i <= 2; ++i) {
    std::string name = "x" + std::to_string(i);
    symbols.emplace_back(Symbol(bool_const, name));
  }

  std::string I = "(x0 == false && x1 == false && x2 == false)";
  std::string T = "(next_x0 == x1 && next_x1 == x2 && next_x2 == true)";

  ltlBmc l(symbols, I, T);

  l.setBound(3);

  std::string alwaysZero = "G(x0 == false && x1 == false && x2 == false)";
  std::string eventuallyAllTrue = "F(x0 == true && x1 == true && x2 == true)";
  std::string correctNextStep = "X(x0 == false && x1 == false && x2 == true)";
  std::string wrongNextStep = "X!(x0 == false && x1 == false && x2 == true)";
  std::string untilAllTrue = "!(x0 && x1 && x2) U (x0 && x1 && x2)";
  std::string releaseAllTrue = "(x0 && x1 && x2) R !(x0 && x1 && x2)";

  assert(l.check(alwaysZero) == false);
  assert(l.check(eventuallyAllTrue) == true);
  assert(l.check(correctNextStep) == true);
  assert(l.check(wrongNextStep) == false);
  assert(l.check(untilAllTrue) == true);
  assert(l.check(releaseAllTrue) == true);
}