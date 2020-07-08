#include "verification-algorithms/common/cnf.hpp"

namespace verifier {
  void CNF::constructCNF(FormulaNode cur) {
    std::string content = cur.getContent();
    if(content == "&&") {
      constructCNF(cur.getChild(0));
      constructCNF(cur.getChild(1));
    } else if(content == "()") {
      constructCNF(cur.getChild(0));
    } else {
      z3::expr clause = construct(cur);
      addClause(clause);
    }
  }
}

