#include "ltl-bmc/ltl-bmc.hpp"

z3::expr_vector ltlBmc::globalStateAt(int k) {
  z3::expr_vector globalState(ctx);
  std::string curState = std::to_string(k);

  for(auto symbol: symbols) {
    std::string name = symbol.getName();
    name += curState;
    Symbol temp(symbol.getType(), name, symbol.getValue());
    globalState.push_back(addOrGetSymbol(temp));
  }
  
  return globalState;
}

z3::expr ltlBmc::translationWithoutLoop(FormulaNode root, int i, int k) {
  if(root.isLeaf()) {
    
  }
}