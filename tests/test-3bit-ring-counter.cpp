#include <iostream>
#include "k-induction/k-induction.hpp"

int main() {
  Symbol a(bool_const, "a");
  Symbol b(bool_const, "b");
  Symbol c(bool_const, "c");

  std::vector<Symbol> symbols;
  symbols.push_back(a);
  symbols.push_back(b);
  symbols.push_back(c);

  std::string I = "(a && !b && !c)";
  std::string T = "((tya == txc) && (tyb == txa) && (tyc == txb))";
  std::string oneHigh = "((txa && !txb && !txc) || (!txa && txb && !txc) || (!txa && !txb && txc))";
  std::string allLow = "(!txa && !txb && !txc)";
  std::string allHigh = "(txa && txb && txc)";
  std::string firstHigh = "(txa && !txb && !txc)";
  std::string firstOrSecondHigh = "((txa && !txb && !txc) || (!txa && txb && !txc))";
  std::string atleastOneHigh = "(txa || txb || txc)";

  kInduction k(symbols, I, T);
  assert(k.check(oneHigh) == true);
  assert(k.check(allLow) == false);
  assert(k.check(allHigh) == false);
  assert(k.check(firstHigh) == false);
  assert(k.check(firstOrSecondHigh) == false);
  assert(k.check(atleastOneHigh) == true);
}
