#include "verification-algorithms/pnet-coverability/pnet-coverability.hpp"

namespace verifier {
  void PnetCoverability::declare() {
    for(int i = 0; i < symbols.size(); ++i) {
      Symbol symbol = symbols[i];
      assert(symbol.getType() == int_const);
      marking.set(0, i, addOrGetSymbol(symbol));
    }
  }
  
  void PnetCoverability::fillMatrix(matrix& mat, std::string prefix) {
    auto dimensions = mat.getDimensions();
    for(int i = 0; i < dimensions.first; ++i) {
      std::string i_str = std::to_string(i);
      for(int j = 0; j < dimensions.second; ++j) {
        std::string name = prefix + i_str + std::to_string(j);
        mat.set(i, j, ctx.int_const(name.c_str()));
      }
    }
  }
  
  z3::expr PnetCoverability::nonNegative(matrix& mat) {
    z3::expr constraint(ctx);
    auto dimensions = mat.getDimensions();
    for(int i = 0; i < dimensions.first; ++i) {
      for(int j = 0; j < dimensions.second; ++j) {
        if(i == 0 && j == 0) { constraint = (mat.get(i, j) >= 0); }
        else { constraint = constraint && (mat.get(i, j) >= 0);  }
      }
    }
    return constraint;
  }
  
  void PnetCoverability::makeMarkingConstraint() {
    fillMatrix(count, "#x");
  
    matrix rhs = m0 + count * incidence;
    marking_constraint = (marking == rhs);
    marking_constraint = marking_constraint && (nonNegative(marking));
    marking_constraint = marking_constraint && (nonNegative(count));
  }
  
  bool PnetCoverability::check(std::string property) {
    P = stringToZ3(property);
    
    z3::solver s(ctx);
    s.add(marking_constraint && !P);
    result = (s.check() == z3::unsat);
    return result;
  }
}

