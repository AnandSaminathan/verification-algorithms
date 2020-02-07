#pragma once

#include <vector>

#include "common/verifier.hpp"
#include "common/z3-solver.hpp"
#include "common/symbol.hpp"

class kInduction : Verifier {
  public:

    kInduction(std::vector<Symbol> symbols, std::string I, std::string T) : I(stringToZ3(I)), 
        T(stringToZ3(T)),
        P(ctx),
        loopFree(ctx),
        x(ctx),
        y(ctx) {

      varsPerState = (int) symbols.size();
      this->declare(symbols);
      

    }
    
    virtual bool check(std::string property) override;
    
    inline z3::expr getI() { return I; }
    inline z3::expr getT() { return T; }

  private:

    void declare(std::vector<Symbol> symbols);
    
    z3::expr_vector globalStateAt(int);
    z3::expr transitionAt(int);
    z3::expr propertyAt(int);
    z3::expr loopFreeAt(int);

    z3::expr I, T;
    z3::expr P;
    z3::expr loopFree;
    z3::expr_vector x, y;

    int varsPerState;
    std::vector<z3::expr_vector> globalStates;
};

