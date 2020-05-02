#pragma once

#include <vector>

#include "verification-algorithms/common/verifier.hpp"
#include "verification-algorithms/common/symbol.hpp"
#include "formula-tree/formula-tree.h"

class ltlBmc : public Verifier {
  public:

    ltlBmc(std::vector<Symbol> symbols, std::string I, std::string T) : I(ctx),
      T(ctx),
      x(ctx),
      next_x(ctx) {

        varsPerState = (int) symbols.size();
        this->symbols = symbols;
        this->declare();
        this->I = stringToZ3(I);
        this->T = stringToZ3(T);
        this->bound = 1000000;
    }

    bool check(std::string) override;

    inline z3::expr getI() { return I; }
    inline z3::expr getT() { return T; }

    inline void setBound(int bound) { this->bound = bound;  }
    inline int getBound() { return bound; }

  private:

    void declare();

    inline z3::expr transition(z3::expr_vector from, z3::expr_vector to) { return T.substitute(x, from).substitute(next_x, to); }
    inline void includeGlobalState(int k) { if(globalStates.size() == k) { globalStates.push_back(globalStateAt(k)); } }
    inline z3::expr initialState() { return (I.substitute(x, globalStates[0])); }
    inline z3::expr loopCondition(int k, int l) { return transition(globalStates[k], globalStates[l]); }
    inline z3::expr loopCondition(int k) { 
      z3::expr condition(ctx); 
      for(int l = 0; l <= k; ++l) {
        z3::expr cur = loopCondition(k, l);
        if(l == 0) { condition = (cur); }
        else { condition = condition || (cur); }
      }
      return (condition);
    }

    z3::expr_vector globalStateAt(int);
    z3::expr generalTranslation(z3::expr&, FormulaNode, int);
    z3::expr translationWithoutLoop(FormulaNode, int, int);
    z3::expr translationWithLoop(FormulaNode, int, int, int);

    void generateTrace(z3::model&);

    z3::expr I, T;
    z3::expr_vector x, next_x;

    std::vector<Symbol> symbols;

    int varsPerState;
    int bound;
    std::vector<z3::expr_vector> globalStates;
};
