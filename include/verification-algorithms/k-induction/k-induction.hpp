#pragma once

#include <vector>

#include "verification-algorithms/common/verifier.hpp"
#include "verification-algorithms/common/symbol.hpp"

class kInduction : public Verifier {
  public:

    kInduction(std::vector<Symbol> symbols, std::string I, std::string T) : I(ctx), 
        T(ctx),
        P(ctx),
        x(ctx),
        next_x(ctx) {

      varsPerState = (int) symbols.size();
      this->symbols = symbols;
      this->declare();
      this->I = stringToZ3(I);
      this->T = stringToZ3(T);

    }
    
    bool check(std::string) override;
    
    inline z3::expr getI() { return I; }
    inline z3::expr getT() { return T; }
    inline z3::expr getP() { return P; }

    inline int  getLength() override { return stoppedAt; }
    inline Trace getTrace() override { assert(result == false); return trace; }

    inline void setBound(int bound) { this->bound = bound;  }
    inline int getBound() { return bound; }

  private:

    void declare();

    inline z3::expr transitionAt(int k) { return (T.substitute(x, globalStates[k - 1])).substitute(next_x, globalStates[k]);  }
    inline z3::expr propertyAt(int k) { return (P.substitute(x, globalStates[k]));  }
    inline z3::expr initialState() { return (I.substitute(x, globalStates[0])); }
    inline void includeGlobalState(int k) { if(globalStates.size() == k) { globalStates.push_back(globalStateAt(k)); } }
    
    z3::expr_vector globalStateAt(int);
    void updateAt(int, z3::expr&, z3::expr&);
    void generateTrace(z3::model&);

    z3::expr I, T;
    z3::expr P;
    z3::expr_vector x, next_x;

    Trace trace;

    int stoppedAt;
    int varsPerState;
    int bound{INT_MAX};
    bool result;
    std::vector<Symbol> symbols;
    std::vector<z3::expr_vector> globalStates;

};


