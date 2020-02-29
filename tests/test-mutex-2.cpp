#include <iostream>
#include "ltl-bmc/ltl-bmc.hpp"

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
    std::string clause = "(" + t[i];
    for(int j = 1; j <= 4; ++j) {
      if(j != i) {
       clause += " && !(" + t[j] + ")";
      }
    }
    clause += ")";
    if(i == 1) T = clause;
    else T += " || " + clause;
  }

  std::string mutex = "G(!(p2 > 0 && p5 > 0))";
  std::string badMutex = "G(p2 > 0 && p5 > 0)";
  std::string alwaysInCS = "G(p2 > 0 || p5 > 0)";
  std::string tokenUnused = "G((p3 > 0) -> (p2 == 0 && p5 == 0))";
  std::string tokenUsed = "G((p3 == 0) -> (p2 == 1 || p5 == 1))";
  std::string badTokenUsed = "G((p3 == 0) -> (p2 == 1 && p5 == 1))";
  std::string eventuallyCS1 = "F(p2 > 0)";
  std::string eventuallyCS2 = "F(p5 > 0)";
  std::string eventuallyCS = "F(p2 > 0 || p5 > 0)";

  ltlBmc l(symbols, I, T); l.setBound(4);

  assert(l.check(mutex) == true);
  assert(l.check(badMutex) == false);
  assert(l.check(alwaysInCS) == false);
  assert(l.check(tokenUnused) == true);
  assert(l.check(tokenUsed) == true);
  assert(l.check(badTokenUsed) == false);
  assert(l.check(eventuallyCS1) == false);
  assert(l.check(eventuallyCS2) == false);
  assert(l.check(eventuallyCS) == true);
}