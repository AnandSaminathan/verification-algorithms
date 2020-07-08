#pragma once

#include "z3-solver.hpp"

namespace verifier {
  class CNF {
    public:
  
      CNF() : formula(ctx) { 
        formula = ctx.bool_val(true); 
        clauses.emplace_back(formula);
      }
      
      CNF(std::string formula) : formula(ctx) {
        (this->formula) = ctx.bool_val(true);
        clauses.emplace_back((this->formula));
        FormulaTree tree(formula);
        constructCNF(tree.getRoot());
      }
  
      inline z3::expr operator()() { return formula; }
      
      inline void addClause(z3::expr clause) { clauses.push_back(clause); formula = (formula && clause);}
      
      inline z3::expr getCNF() { return formula; }
      inline int getClauseCount() { return (int) clauses.size();  }
      inline std::vector<z3::expr> getClauses() { return clauses; }
  
  
    private:
  
      void constructCNF(FormulaNode);
  
      std::vector<z3::expr> clauses;
      z3::expr formula;
  
  };
}

