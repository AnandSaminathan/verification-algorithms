#include <iostream>
#include "verification-algorithms/k-induction/k-induction.hpp"

int main() {
  std::vector<Symbol> symbols;
  for(int i = 1; i <= 5; ++i) {
    char ic = (i + '0');
    std::string var = "p";
    var += ic;
    Symbol pi(int_const, var);
    symbols.push_back(pi);
  }

  std::string I = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 1 && p5 == 0)";

  std::string t[5];
  t[1] = "((p1 >= 1 && p3 >= 1) && (next_p1 == p1 - 1 && next_p2 == p2 + 1 && next_p3 == p3 - 1 && next_p4 == p4 && next_p5 == p5))";
  t[2] = "((p2 >= 1) && (next_p1 == p1 + 1 && next_p2 == p2 - 1 && next_p3 == p3 + 1  && next_p4 == p4 && next_p5 == p5))";
  t[3] = "((p4 >= 1 && p3 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 - 1 && next_p4 == p4 - 1 && next_p5 == p5 + 1))";
  t[4] = "((p5 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 + 1 && next_p4 == p4 + 1 && next_p5 == p5 - 1))";

  std::string T = "";
  for(int i = 1; i <= 4; ++i) {
    if(i != 4) { T = T + t[i] + " + ";  }
    else { T = T + t[i] + " ==  1";  }
  }

  std::string mutex = "(!(p2 > 0 && p5 > 0))";
  std::string badMutex = "(p2 > 0 && p5 > 0)";
  std::string alwaysInCS = "(p2 > 0 || p5 > 0)";
  std::string tokenUnused = "((p3 > 0) -> (p2 == 0 && p5 == 0))";
  std::string tokenUsed = "((p3 == 0) -> (p2 == 1 || p5 == 1))";
  std::string badTokenUsed = "((p3 == 0) -> (p2 == 1 && p5 == 1))";

  kInduction k(symbols, I, T);

  assert(k.check(mutex) == true);
  assert(k.check(badMutex) == false);
  assert(k.check(alwaysInCS) == false);
  assert(k.check(tokenUnused) == true);
  assert(k.check(tokenUsed) == true);
  assert(k.check(badTokenUsed) == false);
}
