#include <iostream>
#include "verification-algorithms/k-induction/k-induction.hpp"
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
  std::string firstOrSecondHigh = "((a && !b && !c) || (!a && b && !c))";

  kInduction k(symbols, I, T);
  assert(k.check(firstOrSecondHigh) == false);
  
  Trace t = k.getTrace();
  auto states = t.getStates();
  std::vector<std::string> expected[3];
  expected[0] = {"true", "false", "false"};
  expected[1] = {"false", "true", "false"};
  expected[2] = {"false", "false", "true"};
  assert(states.size() == 3);
  for(int i = 0; i < 3; ++i) {
    auto state = states[i];
    assert(state.size() == 3);
    assert(state == expected[i]);
  }
}
