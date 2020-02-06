#include "kripke-structure.hpp"
#include <iostream>

int main() {
  // kripke structure for a three bit ring counter
  KripkeStructure k("(x && !y && !z)", "(tx == z && ty == x && tz == y)");
  
  std::cout << k.getI() << " " << k.getT() << '\n';
}
