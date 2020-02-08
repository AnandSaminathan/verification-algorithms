#pragma once

#include <vector>

#include "common/verifier.hpp"
#include "common/z3-solver.hpp"
#include "common/symbol.hpp"

class kInduction : Verifier {
  public:

    kInduction(std::vector<Symbol> symbols, std::string I, std::string T) : I(ctx), 
        T(ctx),
        P(ctx),
        x(ctx),
        y(ctx) {

      varsPerState = (int) symbols.size();
      this->symbols = symbols;
      this->declare(symbols);
      this->I = stringToZ3(I);
      this->T = stringToZ3(T);

    }
    
    virtual bool check(std::string) override;
    
    inline z3::expr getI() { return I; }
    inline z3::expr getT() { return T; }
    inline z3::expr getP() { return P; }

  private:

    void declare(std::vector<Symbol> symbols);

    inline z3::expr transitionAt(int k) { return (T.substitute(x, globalStates[k - 1])).substitute(y, globalStates[k]);  }
    inline z3::expr propertyAt(int k) { return (P.substitute(x, globalStates[k]));  }
    
    z3::expr_vector globalStateAt(int);
    void updateAt(int, z3::expr&, z3::expr&);

    z3::expr I, T;
    z3::expr P;
    z3::expr_vector x, y;

    int varsPerState;
    std::vector<Symbol> symbols;
    std::vector<z3::expr_vector> globalStates;

};


