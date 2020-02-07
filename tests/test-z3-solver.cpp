#include <string>
#include <iostream>
#include "common/symbol.hpp"
#include "common/z3-solver.hpp"


int main() {
  addOrGetSymbol(Symbol(bool_const, "x"));
  addOrGetSymbol(Symbol(bool_const, "y"));
  addOrGetSymbol(Symbol(bool_const, "z"));

  std::cout << "Three bit ring counter formulas in z3: \n";

  std::string I = "x && !y && !z";
  std::cout << "I: " << (stringToZ3(I)) << '\n';

  addOrGetSymbol(Symbol(bool_const, "txx"));
  addOrGetSymbol(Symbol(bool_const, "tyx"));
  addOrGetSymbol(Symbol(bool_const, "tzx"));
  addOrGetSymbol(Symbol(bool_const, "txy"));
  addOrGetSymbol(Symbol(bool_const, "tyy"));
  addOrGetSymbol(Symbol(bool_const, "tzy"));

  std::string T = "(txy == tzx && tyy == txx && tzy == tyx)";
  std::cout << "T: " << (stringToZ3(T)) << '\n';

  std::string oneHigh = "((txx && !tyx && !tzx) || (!txx && tyx && !tzx) || (!txx && !tyx && tzx))";
  std::cout << "P: " << (stringToZ3(oneHigh)) << '\n';
}
