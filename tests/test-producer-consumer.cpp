#include <iostream>
#include "k-induction/k-induction.hpp"

int main() {
  std::vector<Symbol> symbols;
  for(int i = 1; i <= 6; ++i) {
    char ic = (i + '0');
    std::string var = "p";
    var += ic;
    Symbol pi(int_const, var);
    symbols.push_back(pi);
  }

  std::string I = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)"; 

  std::string t[5];
  t[1] = "((txp1 >= 1) && (typ1 == txp1 - 1 && typ2 == txp2 + 1 && typ3 == txp3 && typ4 == txp4 && typ5 == txp5 && typ6 == txp6))";
  t[2] = "((txp2 >= 1 && txp6 >= 1) && (typ1 == txp1 + 1 && typ2 == txp2 - 1 && typ3 == txp3 && typ4 == txp4 && typ5 == txp5 + 1 && typ6 == txp6 - 1))";
  t[3] = "((txp5 >= 1 && txp3 >= 1) && (typ1 == txp1 && typ2 == txp2 && typ3 == txp3 - 1 && typ4 == txp4 + 1 && typ5 == txp5 - 1 && typ6 == txp6 + 1))";
  t[4] = "((txp4 >= 1) && (typ1 == txp1 && typ2 == txp2 && typ3 == txp3 + 1 && typ4 == txp4 - 1 && typ5 == txp5 && typ6 == txp6))";

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

  std::string allNonNegative = "(txp1 >= 0 && txp2 >= 0 && txp3 >= 0 && txp4 >= 0 && txp5 >= 0 && txp6 >= 0)";
  std::string p1Negative = "(txp1 < 0 && txp2 >= 0 && txp3 >= 0 && txp4 >= 0 && txp5 >= 0 && txp6 >= 0)";
  std::string allPositive = "(txp1 > 0 && txp2 > 0 && txp3 > 0 && txp4 > 0 && txp5 > 0 && txp6 > 0)";
  std::string alwaysI = "(txp1 == 1 && txp2 == 0 && txp3 == 1 && txp4 == 0 && txp5 == 0 && txp6 == 1)";
  std::string p1Positive = "(txp1 > 0 && txp2 >= 0 && txp3 >= 0 && txp4 >= 0 && txp5 >= 0 && txp6 >= 0)";

  kInduction k(symbols, I, T);

  assert(k.check(allNonNegative) == true);
  assert(k.check(p1Negative) == false);
  assert(k.check(allPositive) == false);
  assert(k.check(p1Positive) == false);
  assert(k.check(alwaysI) == false);
}

