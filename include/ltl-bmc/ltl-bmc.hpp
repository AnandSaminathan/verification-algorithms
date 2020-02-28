#pragma once

#include <vector>

#include "common/verifier.hpp"
#include "common/z3-solver.hpp"
#include "common/symbol.hpp"
#include "formula-tree/formula-tree.h"

class ltlBmc : Verifier {
  public:

    ltlBmc(std::vector<Symbol> symbols, std::string I, std::string T) : I(ctx),
      T(ctx),
      x(ctx),
      next_x(ctx),
      trace(ctx) {

        varsPerState = (int) symbols.size();
        this->I = stringToZ3(I);
        this->T = stringToZ3(T);
        this->symbols = symbols;
        this->bound = 1000000;
    }

    virtual bool check(std::string) override;

    inline z3::expr getI() { return I; }
    inline z3::expr getT() { return T; }

    inline int  getLength() { return stoppedAt; }
    inline z3::model getTrace() { assert(result == false); return trace; }

    inline void setBound(int bound) { this->bound = bound;  }
    inline int getBound() { return bound; }

  private:

    void declare();

    inline z3::expr transition(expr from, expr to) { return T.substitute(x, from).substitute(next_x, to); }
    inline void includeGlobalState(int k) { if(globalStates.size() == k) { globalStates.push_back(globalStateAt(k)); } }

    z3::expr_vector globalStateAt(int);
    z3::expr translationWithoutLoop(FormulaNode, int, int);
    z3::expr translationWithLoop(FormulaNode, int, int, int);

    z3::expr I, T;
    z3::expr_vector x, next_x;

    z3::model trace;

    std::vector<Symbol> symbols;

    int varsPerState;
    int stoppedAt;
    int bound;
    bool result;
    std::vector<z3::expr_vector> globalStates;
}