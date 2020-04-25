#include "verification-algorithms/common/cnf.hpp"

void CNF::constructCNF(FormulaNode cur) {
  if(cur.getContent() == "&&") {
    constructCNF(cur.getChild(0));
    constructCNF(cur.getChild(1));
  } else {
    z3::expr clause = construct(cur);
    clauses.push_back(clause);
  }
}

