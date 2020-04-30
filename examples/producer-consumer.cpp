#include <iostream>
#include "verification-algorithms/k-induction/k-induction.hpp"

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
  t[1] = "((p1 >= 1) && (next_p1 == p1 - 1 && next_p2 == p2 + 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 && next_p6 == p6))";
  t[2] = "((p2 >= 1 && p6 >= 1) && (next_p1 == p1 + 1 && next_p2 == p2 - 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 + 1 && next_p6 == p6 - 1))";
  t[3] = "((p5 >= 1 && p3 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 - 1 && next_p4 == p4 + 1 && next_p5 == p5 - 1 && next_p6 == p6 + 1))";
  t[4] = "((p4 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 + 1 && next_p4 == p4 - 1 && next_p5 == p5 && next_p6 == p6))";

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

  std::string allNonNegative = "(p1 >= 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
  std::string atleastOnePositive = "(p1 > 0 || p2 > 0 || p3 > 0 || p4 > 0 || p5 > 0 || p6 > 0)";
  std::string p1Negative = "(p1 < 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
  std::string allPositive = "(p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0 && p5 > 0 && p6 > 0)";
  std::string alwaysI = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)";
  std::string p1Positive = "(p1 > 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";

  kInduction k(symbols, I, T);

  assert(k.check(allNonNegative) == true);
  assert(k.check(atleastOnePositive) == true);
  assert(k.check(p1Negative) == false);
  assert(k.check(allPositive) == false);
  assert(k.check(p1Positive) == false);
  assert(k.check(alwaysI) == false);
}

