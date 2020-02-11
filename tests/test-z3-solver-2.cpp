#include <string>
#include <iostream>
#include "common/symbol.hpp"
#include "common/z3-solver.hpp"


int main() {
  addOrGetSymbol(Symbol(int_const, "x"));
  addOrGetSymbol(Symbol(int_const, "y"));
  addOrGetSymbol(Symbol(int_const, "z"));
  addOrGetSymbol(Symbol(int_const, "nx"));
  addOrGetSymbol(Symbol(int_const, "ny"));
  addOrGetSymbol(Symbol(int_const, "nz"));

  std::string I = "(x == 1 && y == 0 && z == 0)";

  std::string t1 = "(x >= 1) && ((x >= 1) -> (nx == x - 1 && ny == y + 1))";
  std::string t2 = "(y >= 1) && (z >= 1) && ((y >= 1 && z >= 1) -> (nx == x + 1 && ny == y - 1 && nz == z - 1))";
  std::string T = "(" + t1 + " && " + "!(" + t2 + ")" + ")" + " || " + "( !(" + t1 + ") && " + t2 + ")";
  // std::string T = t1;
  // std::string T = t1 + " || " + t2;

  std::cout << T << '\n';

  z3::expr eI = stringToZ3(I);
  z3::expr eT = stringToZ3(T);

  std::cout << eT << '\n';
  z3::solver s(ctx);
  s.add(eI && eT);
  z3::check_result res = s.check();

  std::cout << res << "\n";
  if(res == z3::sat) {
    std::cout << s.get_model() << "\n";
  }
}
