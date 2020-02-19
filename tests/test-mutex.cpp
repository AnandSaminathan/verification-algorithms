#include <iostream>
#include "k-induction/k-induction.hpp"

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
  t[1] = "((txp1 >= 1 && txp3 >= 1) && (typ1 == txp1 - 1 && typ2 == txp2 + 1 && typ3 == txp3 - 1 && typ4 == txp4 && typ5 == txp5))";
  t[2] = "((txp2 >= 1) && (typ1 == txp1 + 1 && typ2 == txp2 - 1 && typ3 == txp3 + 1  && typ4 == txp4 && typ5 == txp5))";
  t[3] = "((txp4 >= 1 && txp3 >= 1) && (typ1 == txp1 && typ2 == txp2 && typ3 == txp3 - 1 && typ4 == txp4 - 1 && typ5 == txp5 + 1))";
  t[4] = "((txp5 >= 1) && (typ1 == txp1 && typ2 == txp2 && typ3 == txp3 + 1 && typ4 == txp4 + 1 && typ5 == txp5 - 1))";

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

  std::string mutex = "(!(txp2 > 0 && txp5 > 0))";
  std::string badMutex = "(txp2 > 0 && txp5 > 0)";
  std::string alwaysInCS = "(txp2 > 0 || txp5 > 0)";
  std::string tokenUnused = "((txp3 > 0) -> (txp2 == 0 && txp5 == 0))";
  std::string tokenUsed = "((txp3 == 0) -> (txp2 == 1 || txp5 == 1))";
  std::string badTokenUsed = "(txp3 == 0) -> (txp2 == 1 && txp5 == 1))";

  kInduction k(symbols, I, T);

  assert(k.check(mutex) == true);
  assert(k.check(badMutex) == false);
  assert(k.check(alwaysInCS) == false);
  assert(k.check(tokenUnused) == true);
  assert(k.check(tokenUsed) == true);
  assert(k.check(badTokenUsed) == false);
}