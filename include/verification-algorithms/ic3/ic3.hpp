#pragma once

#include <vector>

#include "verification-algorithms/common/verifier.hpp"
#include "verification-algorithms/common/symbol.hpp"
#include "verification-algorithms/common/cnf.hpp"

class IC3 : public Verifier {
  public:

    IC3(std::vector<Symbol> symbols, std::string I, std::string T) : T(ctx),
      P(ctx),
      x(ctx),
      next_x(ctx),
      trace(ctx) {
      this->declare();
      this->I = CNF(I);
      this->T = stringToZ3(T);
    }
    
    bool check(std::string) override;

    inline z3::expr getI() { return I(); }
    inline z3::expr getT() { return T; }
    inline z3::expr getP() { return P; }

    inline int getLength() override { return stoppedAt; }
    inline z3::model getTrace() override { assert(result == false); return trace;  }

  private:

    void declare();
    CNF getCube(z3::model&);

    CNF I;
    z3::expr T; 
    z3::expr P;
    z3::expr_vector x;
    z3::expr_vector next_x;

    z3::model trace;

    int stoppedAt;
    bool result;
    std::vector<Symbol> symbols;
    std::vector<CNF> frames;
};


